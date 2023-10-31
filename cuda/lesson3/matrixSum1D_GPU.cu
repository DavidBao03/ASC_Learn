#include <stdio.h>
#include "../tools/common.cuh"

__global__ void addFromGPU(float *A, float *B, float *C, const int N)
{
		const int bid = blockIdx.x;
		const int tid = threadIdx.x;
		const int id = tid + bid * blockDim.x;

		C[id] = A[id] + B[id];
}

void initialData(float *addr, int element)
{
		for(int i = 0; i < element; i++)
		{
				addr[i] = (float)(rand() & 0xFF) / 10.f;
		}
}

int main()
{
		setGPU();

		int iElemCount = 51200;
		size_t stBytesCount = iElemCount * sizeof(float);

		float *fpHost_A, *fpHost_B, *fpHost_C;
		fpHost_A = (float *)malloc(stBytesCount);
		fpHost_B = (float *)malloc(stBytesCount);
		fpHost_C = (float *)malloc(stBytesCount);
		
		if(fpHost_A != NULL && fpHost_B != NULL && fpHost_C != NULL)
		{	
				memset(fpHost_A, 0, stBytesCount);
				memset(fpHost_B, 0, stBytesCount);	
				memset(fpHost_C, 0, stBytesCount);
		}
		else
		{
				printf("Fail to allocate host memory!\n");
				exit(-1);
		}

		float *fpDevice_A, *fpDevice_B, *fpDevice_C;
		cudaMalloc((float **)&fpDevice_A, stBytesCount);
		cudaMalloc((float **)&fpDevice_B, stBytesCount);
		cudaMalloc((float **)&fpDevice_C, stBytesCount);

		if(fpDevice_A != NULL && fpDevice_B != NULL && fpDevice_C != NULL)
		{
			cudaMemset(fpDevice_A, 0, stBytesCount);
			cudaMemset(fpDevice_B, 0, stBytesCount);
			cudaMemset(fpDevice_C, 0, stBytesCount);
		}
		else
		{
				printf("Fail to allocate device memory!\n");
				free(fpHost_A);
				free(fpHost_B);
				free(fpHost_C);
				exit(-1);
		}

		srand(666);
		initialData(fpHost_A, iElemCount);
		initialData(fpHost_B, iElemCount);

		cudaMemcpy(fpDevice_A, fpHost_A, stBytesCount, cudaMemcpyHostToDevice);
		cudaMemcpy(fpDevice_B, fpHost_B, stBytesCount, cudaMemcpyHostToDevice);
		
		dim3 block(320);
		dim3 grid(iElemCount / 320);

		addFromGPU<<<grid, block>>>(fpDevice_A, fpDevice_B, fpDevice_C, iElemCount);
		cudaDeviceSynchronize();

		cudaMemcpy(fpHost_C, fpDevice_C, stBytesCount, cudaMemcpyDeviceToHost);

		for(int i = 0; i < 32; i++)
		{
				for(int j = 0; j < 32; j++)
					printf("%.2f %.2f %.2f\n"
								,fpHost_A[j], fpHost_B[j], fpHost_C[j]);
		}

		free(fpHost_A);
		free(fpHost_B);
		free(fpHost_C);
		cudaFree(fpDevice_A);
		cudaFree(fpDevice_B);
		cudaFree(fpDevice_C);

		cudaDeviceReset();

		return 0;
}

