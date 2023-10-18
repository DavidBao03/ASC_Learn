#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argv, char ** argc)
{
	int cnt = strtol(argc[1], NULL, 10);
	printf("use barrier:\n");
#	pragma omp parallel num_threads(cnt)
	{
		int my_rank = omp_get_thread_num();
		int threads = omp_get_num_threads();
		printf("hi from %d\n", my_rank);
#		pragma omp barrier
		if(my_rank == 0){
			printf("%d threads say hi\n", threads);
		}
	}
	
	printf("not use barrier:\n");
#	pragma omp parallel num_threads(cnt)
	{
		int my_rank = omp_get_thread_num();
		int threads = omp_get_num_threads();
		printf("hi from %d\n", my_rank);
		if(my_rank == 0){
			printf("%d threads say hi\n", threads);
		}
	}
	
	return 0;
}
