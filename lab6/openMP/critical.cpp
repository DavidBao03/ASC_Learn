#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
	int threads = strtol(argv[1], NULL, 10);
	int j = 0;
	#pragma omp parallel for num_threads(threads) shared(j)
	for(int i = 0; i < 10; i++){
		#pragma omp critical
		{
			j = j + 1;
			printf("thread %d of %d, i = %d, j = %d\n", omp_get_thread_num(), omp_get_num_threads(), i, j);
		}
	}
	
	j = 0;
	printf("not use:\n");
	#pragma omp parallel for num_threads(threads) shared(j)
	for(int i = 0; i < 10; i++){
		{
			j = j + 1;
			printf("thread %d of %d, i = %d, j = %d\n", omp_get_thread_num(), omp_get_num_threads(), i, j);
		}
	}
	
	return 0;
}
