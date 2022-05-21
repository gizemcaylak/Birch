/**
 * @file
 */
#include "numbirch/cuda/cuda.hpp"

namespace numbirch {

thread_local int device = 0;
thread_local cudaStream_t stream = 0;
thread_local unsigned max_blocks = 64;

void cuda_init() {
  #pragma omp parallel
  {
    CUDA_CHECK(cudaGetDevice(&device));

    int value = 0;
    /* check device support */
    CUDA_CHECK(cudaDeviceGetAttribute(&value,
        cudaDevAttrConcurrentKernels, device));
    assert(value && "device with concurrent kernel support required");
    CUDA_CHECK(cudaDeviceGetAttribute(&value,
        cudaDevAttrConcurrentManagedAccess, device));
    assert(value && "device with concurrent managed memory support required");

    /* determine maximum number of blocks */
    CUDA_CHECK(cudaDeviceGetAttribute(&value,
        cudaDevAttrMultiProcessorCount, device));
    max_blocks = 4*value;

    CUDA_CHECK(cudaDeviceSetCacheConfig(cudaFuncCachePreferShared));
    CUDA_CHECK(cudaStreamCreateWithFlags(&stream, cudaStreamNonBlocking));

    /* use blocking sync when synchronizing streams, i.e. when wait() called;
     * calls to wait() ought to be infrequent for good performance anyway, and
     * a thread spinning rather than blocking can prevent another thread from
     * resuming to schedule kernels that can execute concurrently; on some
     * examples shows ~10% performance improvement */
    cudaStreamAttrValue val;
    val.syncPolicy = cudaSyncPolicyBlockingSync;
    CUDA_CHECK(cudaStreamSetAttribute(stream,
        cudaStreamAttributeSynchronizationPolicy, &val));
  }
}

void cuda_term() {
  #pragma omp parallel
  {
    /* don't use CUDA_CHECK here, because it tries to use stream after
     * destruction when CUDA_SYNC is true */
    cudaError_t err = cudaStreamDestroy(stream);
    assert(err == cudaSuccess);
  }
}

}
