#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void hello()
{
	int my_rank = omp_get_thread_num();
	int threads_count = omp_get_num_threads();

	printf("Hello from %d of %d\n", my_rank, threads_count);
}

int main(int argc, char **argv)
{
	int threads_count = strtol(argv[1], NULL, 10);

#pragma omp parallel  num_threads(threads_count)
	{
		hello();
	}

	return 0;
}
