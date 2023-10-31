#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addFromCPU(float *A, float *B, float *C, const int N)
{
		for(int id = 0; id < N; id++)
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

		srand(666);
		initialData(fpHost_A, iElemCount);
		initialData(fpHost_B, iElemCount);

		addFromCPU(fpHost_A, fpHost_B, fpHost_C, iElemCount);

		for(int i = 0; i < 32; i++)
		{
				for(int j = 0; j < 32; j++)
					printf("%.2f %.2f %.2f\n"
								,fpHost_A[j], fpHost_B[j], fpHost_C[j]);
		}

		free(fpHost_A);
		free(fpHost_B);
		free(fpHost_C);

		return 0;
}

