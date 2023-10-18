#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int main(int argv, char ** argc)
{
	int cnt = strtol(argc[1], NULL, 10);
	printf("use nowait:\n");
#	pragma omp parallel num_threads(cnt)
	{
		int my_rank = omp_get_thread_num();
		int threads = omp_get_num_threads();
		printf("hi from %d\n", my_rank);
#		pragma omp for nowait
		for(int i = 0; i < 10; i++){
			if(my_rank == 0)
				sleep(3000);
			printf("Hello from thread %d of %d i = %d.\n", my_rank, threads, i);
		}
#		pragma omp single nowait
		{
			printf("thread %d process single\n", my_rank);
			sleep(3000);
		}
		
		printf("thread %d ok\n", my_rank);
	}
	
	
	
	printf("not use nowait:\n");
#	pragma omp parallel num_threads(cnt)
	{
		int my_rank = omp_get_thread_num();
		int threads = omp_get_num_threads();
		printf("hi from %d\n", my_rank);
#		pragma omp for
		for(int i = 0; i < 10; i++){
			if(my_rank == 0)
				sleep(3000);
			printf("Hello from thread %d of %d i = %d.\n", my_rank, threads, i);
		}
#		pragma omp single
		{
			printf("thread %d process single\n", my_rank);
			sleep(3000);
		}
		
		printf("thread %d ok\n", my_rank);
	}
	
	return 0;
}
