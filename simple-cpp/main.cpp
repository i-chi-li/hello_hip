#include <cstdio>
#include <hip/hip_runtime.h>

int main(int argc, char *argv[]) {
    hipError_t err;
    int deviceCount;
    // デバイス数を取得する
    err = hipGetDeviceCount(&deviceCount);
    if (err != hipSuccess) {
        printf("hipGetDeviceCount failed\n");
        return -1;
    }
    if (deviceCount == 0) {
        printf("No HIP devices found\n");
        return -1;
    }
    printf("Found %d HIP devices\n", deviceCount);

    // すべてのデバイス情報を取得する
    for (int i = 0; i < deviceCount; ++i) {
        hipDeviceProp_t deviceProp;
        err = hipGetDeviceProperties(&deviceProp, i);
        if (err != hipSuccess) {
            printf("hipGetDeviceProperties failed\n");
            return -1;
        }
        printf("---------------------------------\n");
        printf("Device name: %s\n", deviceProp.name);
        printf("Device major: %d\n", deviceProp.major);
        printf("Device minor: %d\n", deviceProp.minor);
        printf("Managed Memory: %d\n", deviceProp.managedMemory);
        printf("Total Global Mem: %llu\n", deviceProp.totalGlobalMem);
        printf("Multi Processor Count: %d\n", deviceProp.multiProcessorCount);
        printf("GCN Arch Name: %s\n", deviceProp.gcnArchName);
    }
    return 0;
}
