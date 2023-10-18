#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argv, char **argc)
{
	int thread_cnt = strtol(argc[1], NULL, 10);
	
#	pragma omp parallel num_threads(thread_cnt)
	{
#		pragma omp sections
		{
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				printf("thread %d of %d\n", my_rank, cnt);
			}	
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				printf("thread %d of %d\n", my_rank, cnt);
			}	
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				printf("thread %d of %d\n", my_rank, cnt);
			}
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				printf("thread %d of %d\n", my_rank, cnt);
			}
		}
	}
	
	return 0;
}
