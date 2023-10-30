#include <stdio.h>

__global__ void hello_from_gpu()
{
		const int BID = blockIdx.x;
		const int TID = threadIdx.x;

		const int ID = TID + BID * blockDim.x;

		printf("Hello from block %d and thread %d, global id = %d\n", BID, TID, ID);

}

int main()
{
		hello_from_gpu<<<2,4>>>();
		cudaDeviceSynchronize();

		return 0;
}
