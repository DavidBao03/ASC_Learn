#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argv, char **argc)
{
	int thread_cnt = strtol(argc[1], NULL, 10);
	int j = 10;
#	pragma omp parallel num_threads(thread_cnt) reduction(+:j)
	{
#		pragma omp sections
		{
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				j = j + 10;
				printf("thread %d of section1, j = %d\n", my_rank, j);
			}	
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				j = j + 20;
				printf("thread %d of section2, j = %d\n", my_rank, j);
			}	
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				j = j + 30;
				printf("thread %d of section3, j = %d\n", my_rank, j);
			}
#			pragma omp section
			{
				int my_rank = omp_get_thread_num();
				int cnt = omp_get_num_threads();
				j = j + 40;
				printf("thread %d of section4, j = %d\n", my_rank, j);
			}
		}
	}
	
	printf("j = %d\n", j);
	
	return 0;
}
