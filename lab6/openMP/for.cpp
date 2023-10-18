#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argv, char ** argc)
{
	int thread_cnt = strtol(argc[1], NULL, 10);

	double a[10], b[10];
	
	for(int i =0; i < 10; i++)
	{
		a[i] = i;
		b[i] = 10 - i;
	}

	double s[10];
#pragma omp parallel for num_threads(thread_cnt)
	for(int i = 0; i < 10; i++){
		s[i] = a[i] + b[i];
		printf("thread_num = %d, result = %lf\n", omp_get_thread_num(), s[i]);
	}

	return 0;
}
