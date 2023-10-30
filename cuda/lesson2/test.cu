#include <stdio.h>

__global__ void hello_from_gpu()
{
		printf("Hello world from the GPU\n");
}

int main()
{
	hello_from_gpu<<<4, 4>>>();
	cudaDeviceSynchronize();

	return 0;
}
