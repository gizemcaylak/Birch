/**
 * @file
 */
#pragma once

#include "libbirch/external.hpp"
#include "libbirch/internal.hpp"
#include "libbirch/assert.hpp"
#include "libbirch/memory.hpp"
#include "libbirch/Atomic.hpp"

namespace libbirch {
/**
 * Flags used for cycle collection as in @ref Bacon2001
 * "Bacon & Rajan (2001)", replacing the colors described there. The reason
 * is to ensure that both the bookkeeping required during normal execution
 * can be multithreaded, and likewise that the operations required during
 * cycle collection can be multithreaded. The basic principle to ensure this
 * is that flags can be safely set during normal execution (with atomic
 * operations), but should only be unset with careful consideration of
 * thread safety.
 *
 * Notwithstanding, the flags do map to colors in @ref Bacon2001
 * "Bacon & Rajan (2001)":
 *
 *   - *acyclic* maps to *green*,
 *   - *buffered* maps to *purple*,
 *   - *marked* maps to *gray*,
 *   - *scanned* and *reachable* together map to *black* (both on) or
 *     *white* (first on, second off),
 *   - *collected* is set once a white object has been destroyed.
 *
 * The use of these flags also resolves some thread safety issues that can
 * otherwise exist during the scan operation, when coloring an object white
 * (eligible for collection) then later recoloring it black (reachable); the
 * sequencing of this coloring can become problematic with multiple threads.
 */
enum Flag : int16_t {
  ACYCLIC = (1 << 0),
  BUFFERED = (1 << 1),
  MARKED = (1 << 2),
  SCANNED = (1 << 3),
  REACHED = (1 << 4),
  COLLECTED = (1 << 5),
  POSSIBLE_ROOT = (1 << 6),
  CLAIMED = (1 << 7)
};

/**
 * Base class providing reference counting, cycle breaking, and lazy deep
 * copy support.
 *
 * @ingroup libbirch
 * 
 * Members of Any use an underscore suffix (e.g. `n_` instead of `n`) in order
 * to avoid naming collisions with derived classes.
 */
class Any {
  friend class Marker;
  friend class Scanner;
  friend class Reacher;
  friend class Collector;
  friend class BiconnectedCollector;
  friend class Spanner;
  friend class Bridger;
  friend class Copier;
  friend class Memo;
  friend class BiconnectedCopier;
  friend class BiconnectedMemo;
public:
  using this_type_ = Any;

  /**
   * Constructor.
   */
  Any() :
      r_(0),
      a_(0),
      l_(std::numeric_limits<int>::max()),
      h_(0),
      p_(-1),
      t_(get_thread_num()),
      f_(0) {
    //
  }

  /**
   * Copy constructor.
   */
  Any(const Any& o) :
      r_(0),
      a_(0),
      l_(std::numeric_limits<int>::max()),
      h_(0),
      p_(-1),
      t_(get_thread_num()),
      f_(o.f_.load() & ACYCLIC) {
    //
  }

  /**
   * Destructor.
   */
  virtual ~Any() {
    assert(r_.load() == 0);
  }

  /**
   * New operator.
   */
  void* operator new(std::size_t size) {
    return allocate(size);
  }

  /**
   * Delete operator.
   */
  void operator delete(void* ptr) {
    assert(false);
  }

  /**
   * Assignment operator.
   */
  Any& operator=(const Any&) {
    return *this;
  }

  /**
   * Destroy.
   */
  void destroy_() {
    auto tid = this->t_;
    auto size = this->size_();
    this->~Any();
    this->t_ = tid;
    this->n_ = size;
  }

  /**
   * Deallocate.
   */
  void deallocate_() {
    libbirch::deallocate(this, this->n_, this->t_);
  }

  /**
   * Reference count.
   */
  int numShared_() const {
    return r_.load();
  }

  /**
   * Increment the shared r.
   */
  void incShared_() {
    r_.increment();
  }

  /**
   * Decrement the shared reference count.
   */
  void decShared_() {
    assert(numShared_() > 0);

    /* first set the BUFFERED flag so that this call is uniquely responsible
     * for registering this object as a possible root */
    auto old = f_.exchangeOr(BUFFERED|POSSIBLE_ROOT);

    if (--r_ == 0) {
      /* destroy, and as long as haven't been previously buffered, can
       * deallocate too */
      destroy_();
      if (!(old & BUFFERED) || old & ACYCLIC) {
        /* hasn't been previously buffered, or is acyclic, so can immediately
         * deallocate */
        deallocate_();
      } else {
        /* has been previously buffered, so deallocation must be deferred
         * until collection, but certainly not a possible root, as has just
         * been destroyed */
        f_.maskAnd(~POSSIBLE_ROOT);
      }
    } else if (!(old & BUFFERED) && !(old & ACYCLIC)) {
      /* not already registered as a possible root, and not acyclic */
      register_possible_root(this);
    }
  }

  /**
   * Decrement the shared count for an object that will remain reachable. The
   * caller asserts that the object will remain reachable after the operation.
   * The object will not be destroyed, and will not be registered as a
   * possible root for cycle collection.
   */
  void decSharedReachable_() {
    assert(numShared_() > 0);
    r_.decrement();
  }

  /**
   * Decrement the shared count for an object while collecting a biconnected
   * component.
   */
  int decSharedBiconnected_() {
    assert(numShared_() > 0);
    return --r_;
  }

  /**
   * Is there only one pointer (of any type) to this object?
   */
  bool isUnique_() const {
    return numShared_() == 1;
  }

  /**
   * Is this object of an acyclic class?
   */
  bool isAcyclic_() const {
    return f_.load() & ACYCLIC;
  }

  /**
   * Is this object the possible root of a cycle?
   */
  bool isPossibleRoot_() const {
    return f_.load() & POSSIBLE_ROOT;
  }

  /**
   * Set the acyclic flag.
   */
  void acyclic_() {
    f_.maskOr(ACYCLIC);
  }

  /**
   * Unset buffer flag.
   */
  void unbuffer_() {
    f_.maskAnd(~(BUFFERED|POSSIBLE_ROOT));
  }

  /**
   * Get the class name.
   */
  virtual const char* getClassName_() const {
    return "Any";
  }

  /**
   * Size of the object.
   */
  virtual int size_() const {
    return sizeof(Any);
  }

  /**
   * Shallow copy the object.
   */
  virtual Any* copy_() const = 0;

  virtual void accept_(Marker& visitor) {
    //
  }

  virtual void accept_(Scanner& visitor) {
    //
  }

  virtual void accept_(Reacher& visitor) {
    //
  }

  virtual void accept_(Collector& visitor) {
    //
  }

  virtual void accept_(BiconnectedCollector& visitor) {
    //
  }

  virtual std::tuple<int,int,int> accept_(Spanner& visitor, const int i,
      const int j) {
    return std::make_tuple(i, i, 0);
  }

  virtual std::tuple<int,int,int,int> accept_(Bridger& visitor, const int j,
      const int k) {
    return std::make_tuple(std::numeric_limits<int>::max(), 0, 0, 0);
  }

  virtual void accept_(Copier& visitor) {
    //
  }

  virtual void accept_(BiconnectedCopier& visitor) {
    //
  }

private:
  /**
   * Reference count.
   */
  Atomic<int> r_;

  /**
   * Account of references, used for bridge finding and cycle collection.
   */
  int a_;

  union {
    /**
     * Lowest reachable rank, used for bridge finding.
     */
    int l_;

    /**
     * Index base in biconnected component, used for copying.
     */
    int k_;
  };

  union {
    /**
     * Highest reachable rank, used for bridge finding.
     */
    int h_;

    /**
     * Size of biconnnected component, used for copying.
     */
    int n_;
  };

  /**
   * Id of the thread that claimed the object, used for bridge finding.
   */
  int16_t p_;

  /**
   * Id of the thread that allocated the object, used by the memory pool.
   */
  int16_t t_;

  /**
   * Bitfield containing flags, used for bridge finding and cycle collection.
   */
  Atomic<int16_t> f_;
};
}
