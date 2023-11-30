#include <stdio.h>

__global__ void helloFromGPU()
{
    if(threadIdx.x == 5)
        printf("Hello World from GPU thread %d!\n", threadIdx.x);
}

int main()
{
    printf("Hello World from CPU!\n");

    helloFromGPU<<<1, 10>>>();
    // cudaDeviceReset();
    cudaDeviceSynchronize();
    return 0;
}