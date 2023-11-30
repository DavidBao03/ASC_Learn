#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// #define CHECK(call) 
// {
//     const cudaError_t error = call;
//     if (error != cudaSuccess)
//     {
//         printf("Ereor: %s:%d, ", __FILE__, __LINE__);
//         printf("code: %d, reason: %s\n", error, cudaGetErrorString(error));
//         exit(1);
//     }
// }

void checkResult(float *hostRef, float *gpuRef, const int N) {
    double epslion = 1.0E-8;
    bool match = 1;
    for (int i = 0; i < N; i++) {
        if (abs(hostRef[i] - gpuRef[i]) > epslion) {
            match = 0;
            printf("Arrays do not match!\n");
            printf("host %5.2f gpu %5.2f at current %d\n", hostRef[i], gpuRef[i], i);
            break;
        }
    }

    if(match) printf("Arrays match.\n");
}

void sumArraysOnHost(float *A, float *B, float *C, const int N) {
    for(int idx = 0; idx < N; idx++) {
        C[idx] = A[idx] + B[idx];
    }
}

__global__ void sumArraysOnGPU(float *A, float *B, float *C) {
    int i = threadIdx.x;
    C[i] = A[i] + B[i];
}

void initialData(float *ip, int size) {
    time_t t;
    srand((unsigned int) time(&t));

    for(int i = 0; i < size; i++) { 
        ip[i] = (float) (rand() % 0xFF) / 10.0f; 
    }
}

int main(int argc, char **argv)
{
    printf("%s starting...\n", argv[0]);

    int dev = 0;
    cudaSetDevice(dev);

    int nElem = 32;
    printf("Vector size %d\n", nElem);

    size_t nBtyes = nElem * sizeof(float);
    float *h_A, *h_B, *hostRef, *gpuRef;
    h_A = (float*)malloc(nBtyes);
    h_B = (float*)malloc(nBtyes);
    hostRef = (float*)malloc(nBtyes);
    gpuRef = (float*)malloc(nBtyes);

    initialData(h_A, nElem);
    initialData(h_B, nElem);

    memset(hostRef, 0, nBtyes);
    memset(gpuRef, 0, nBtyes);

    float *d_A, *d_B, *d_C;
    cudaMalloc((void**)&d_A, nBtyes);
    cudaMalloc((void**)&d_B, nBtyes);
    cudaMalloc((void**)&d_C, nBtyes);

    cudaMemcpy(d_A, h_A, nBtyes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, nBtyes, cudaMemcpyHostToDevice);

    dim3 block(nElem);
    dim3 grid(nElem/block.x);

    sumArraysOnGPU<<<grid, block>>>(d_A, d_B, d_C);
    printf("Execution configuration <<<%d, %d>>>\n", grid.x, block.x);

    cudaMemcpy(gpuRef, d_C, nBtyes, cudaMemcpyDeviceToHost);

    sumArraysOnHost(h_A, h_B, hostRef, nElem);

    checkResult(hostRef, gpuRef, nElem);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(h_A);
    free(h_B);
    free(hostRef);
    free(gpuRef);

    return 0;
}