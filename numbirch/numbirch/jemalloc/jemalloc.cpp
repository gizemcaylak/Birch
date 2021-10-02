/**
 * @file
 */
#include "numbirch/jemalloc/jemalloc.hpp"
#include "numbirch/memory.hpp"

#include <omp.h>
#include <cassert>

/*
 * Host-device shared arena and thread cache for jemalloc. Allocations in this
 * arena will migrate between host and device on demand.
 */
static thread_local unsigned shared_arena = 0;
static thread_local unsigned shared_tcache = 0;
static thread_local int shared_flags = 0;

/*
 * Device arena and thread cache for jemalloc. These use the same custom
 * allocation hooks as for shared allocations (i.e. unified shared memory),
 * and so can be accessed from the host, but by using a separate arena, we
 * expect these allocations to gravitate onto the device and stay there, even
 * when reused.
 */
static thread_local unsigned device_arena = 0;
static thread_local unsigned device_tcache = 0;
static thread_local int device_flags = 0;

/*
 * Disable retention of extents by jemalloc. This is critical as the custom
 * extent hooks for any particular backend will typically allocate physical
 * rather than virtual memory, which should not be retained.
 * 
 * This particular global variable likely has no effect, but is included here
 * for documentation. The `birch` driver program is linked to libjemalloc.so
 * in order to load it prior to any shared libraries for Birch packages, and
 * because of thread-local storage (TLS) issues when loading libjemalloc.so
 * via dlopen()---directly or indirectly (e.g. package shared library linked
 * to libnumbirch.so, linked to libjemalloc.so). Consequently, this global
 * variable is repeated in the `birch` driver program itself; that version
 * is the one that actually as an effect.
 */
const char* malloc_conf = "retain:false";

/**
 * Custom extent hooks structure.
 */
static extent_hooks_t hooks = {
  numbirch::extent_alloc,
  numbirch::extent_dalloc,
  numbirch::extent_destroy,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

/**
 * Custom extent hooks structure.
 */
static extent_hooks_t device_hooks = {
  numbirch::device_extent_alloc,
  numbirch::device_extent_dalloc,
  numbirch::device_extent_destroy,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr,
  nullptr
};

unsigned make_arena(extent_hooks_t* hooks) {
  [[maybe_unused]] int ret;
  unsigned arena = 0;
  size_t size = sizeof(arena);
  ret = mallctl("arenas.create", &arena, &size, &hooks, sizeof(hooks));
  assert(ret == 0);
  return arena;
}

unsigned make_tcache() {
  [[maybe_unused]] int ret;
  unsigned tcache = 0;
  size_t size = sizeof(tcache);
  ret = mallctl("tcache.create", &tcache, &size, nullptr, 0);
  assert(ret == 0);
  return tcache;
}

void numbirch::jemalloc_init() {
  #pragma omp parallel num_threads(omp_get_max_threads())
  {
    /* shared arena setup */
    shared_arena = make_arena(&hooks);
    shared_tcache = make_tcache();
    shared_flags = MALLOCX_ARENA(shared_arena)|MALLOCX_TCACHE(shared_tcache);

    /* device arena setup */
    device_arena = make_arena(&device_hooks);
    device_tcache = make_tcache();
    device_flags = MALLOCX_ARENA(device_arena)|MALLOCX_TCACHE(device_tcache);
  }
}

void numbirch::jemalloc_term() {
  ///@todo
}

void* numbirch::malloc(const size_t size) {
  return size == 0 ? nullptr : mallocx(size, shared_flags);
}

void* numbirch::realloc(void* ptr, const size_t size) {
  if (size > 0) {
    return rallocx(ptr, size, shared_flags);
  } else {
    free(ptr);
    return nullptr;
  }
}

void numbirch::free(void* ptr) {
  /// @todo Actually need to wait on the stream associated with the arena
  /// where this allocation was made, and only if its a different thread to
  /// this one, lest it is reused by the associated thread before this thread
  /// has finished any asynchronous work
  //wait();
  if (ptr) {
    dallocx(ptr, shared_flags);
  }
}

void* numbirch::device_malloc(const size_t size) {
  assert(device_arena > 0);
  return size == 0 ? nullptr : mallocx(size, device_flags);
}

void numbirch::device_free(void* ptr) {
  assert(device_arena > 0);
  if (ptr) {
    dallocx(ptr, device_flags);
  }
}
