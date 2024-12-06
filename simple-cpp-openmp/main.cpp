#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <hip/hip_runtime.h>

#define NUM_THREADS 16
#define CHECK(cmd) \
    {\
        hipError_t error = cmd;\
        if (error != hipSuccess) {\
            fprintf(stderr, "error: '%s'(%d) at %s:%d\n", hipGetErrorString(error), error, __FILE__, __LINE__);\
            exit(EXIT_FAILURE);\
        }\
    }

__global__ void hip_helloworld(const int omp_id, int *A_d) {
    printf("Hello World... from HIP thread = %u\n", omp_id);
    A_d[omp_id] = omp_id;
}

int main(int argc, char *argv[]) {
    int *A_d;
    constexpr size_t N_bytes = NUM_THREADS * sizeof(int);

    hipDeviceProp_t props;
    CHECK(hipGetDeviceProperties(&props, 0));
    printf("info: running on device %s\n", props.name);

    auto *A_h = static_cast<int *>(malloc(N_bytes));
    CHECK(hipMalloc(&A_d, N_bytes));
    for (int i = 0; i < NUM_THREADS; i++) {
        A_h[i] = 0;
    }
    CHECK(hipMemcpy(A_d, A_h, N_bytes, hipMemcpyHostToDevice));

#pragma omp parallel num_threads(NUM_THREADS) default(none) shared(A_d)
    {
        fprintf(stderr, "Hello World... from OMP thread = %d\n", omp_get_thread_num());
        hipLaunchKernelGGL(hip_helloworld, dim3(1), dim3(1), 0, 0, omp_get_thread_num(), A_d);
    }

    CHECK(hipStreamSynchronize(nullptr));
    CHECK(hipMemcpy(A_h, A_d, N_bytes, hipMemcpyDeviceToHost));
    printf("Device Results:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("A_d[%d] = %d\n", i, A_h[i]);
    }
    printf("PASSED!\n");
    free(A_h);
    CHECK(hipFree(A_d));
    return 0;
}
