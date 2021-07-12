/**
 * @file
 */
#pragma once

#include "libbirch/internal.hpp"
#include "libbirch/ArrayShape.hpp"

namespace libbirch {
/**
 * Iterator over Array.
 * 
 * @ingroup libbirch
 *
 * @tparam T Value type.
 * @tparam D Number of dimensions.
 */
template<class T, int D>
class ArrayIterator {
public:
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::random_access_iterator_tag;

  ArrayIterator(T* buffer, const ArrayShape<D> shape) :
      buffer(buffer),
      shape(shape),
      pos(0) {
    //
  }

  auto& operator*() {
    return *get();
  }

  auto& operator*() const {
    return *get();
  }

  auto operator->() {
    return get();
  }

  auto operator->() const {
    return get();
  }

  bool operator==(const ArrayIterator& o) const {
    return pos == o.pos;
  }

  bool operator!=(const ArrayIterator& o) const {
    return pos != o.pos;
  }

  bool operator<=(const ArrayIterator& o) const {
    return pos <= o.pos;
  }

  bool operator<(const ArrayIterator& o) const {
    return pos < o.pos;
  }

  bool operator>=(const ArrayIterator& o) const {
    return pos >= o.pos;
  }

  bool operator>(const ArrayIterator& o) const {
    return pos > o.pos;
  }

  int64_t operator-(const ArrayIterator& o) const {
    return pos - o.pos;
  }

  ArrayIterator& operator+=(const int64_t i) {
    pos += i;
    return *this;
  }

  ArrayIterator operator+(const int64_t i) const {
    ArrayIterator result(*this);
    result += i;
    return result;
  }

  ArrayIterator operator-(const int64_t i) const {
    ArrayIterator result(*this);
    result -= i;
    return result;
  }

  ArrayIterator& operator-=(const int64_t i) {
    pos -= i;
    return *this;
  }

  ArrayIterator& operator++() {
    ++pos;
    return *this;
  }

  ArrayIterator operator++(int) {
    ArrayIterator result(*this);
    ++*this;
    return result;
  }

  ArrayIterator& operator--() {
    --pos;
    return *this;
  }

  ArrayIterator operator--(int) {
    ArrayIterator result(*this);
    --*this;
    return result;
  }

protected:
  /**
   * Raw pointer for the current position.
   */
  auto get() {
    return buffer + shape.offset(pos);
  }

  /**
   * Raw pointer for the current position.
   */
  auto get() const {
    return buffer + shape.offset(pos);
  }

  /**
   * Buffer.
   */
  T* buffer;

  /**
   * Shape.
   */
  ArrayShape<D> shape;

  /**
   * Position.
   */
  int64_t pos;
};
}
