#include <hip/hip_runtime.h>
#include <stdio.h>

__global__ void hello_world() {
  printf("Hello World from GPU!\n");
}

int main() {
  // GPUでカーネルを実行
  hipLaunchKernelGGL(hello_world, dim3(1), dim3(1), 0, 0);

  // GPUの実行が終了するのを待つ
  hipDeviceSynchronize();

  printf("Hello World from CPU!\n");
  return 0;
}
