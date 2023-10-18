#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argv, char ** argc)
{
	int thread_cnt = strtol(argc[1], NULL, 10);

	int j = 4;
	
#pragma omp parallel for num_threads(thread_cnt) lastprivate(j)
	for(int i = 0; i < 10; i++){
		j = 4;
		j++;
		int my_rank = omp_get_thread_num();
		int cnt = omp_get_num_threads();
		printf("thread_num = %d of %d, has j = %d\n", my_rank, cnt, j);
	}

	printf("j = %d\n", j);

	return 0;
}
