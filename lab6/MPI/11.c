#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char **argv)
{
		int err = 0;
		double t1, t2;
		double tick;
		int i;

		MPI_Init(&argc, &argv);
		t1 = MPI_Wtime();
		t2 = MPI_Wtime();

		if(t2 - t1 > 0.1 || t2 - t1 < 0)
		{
				err++;
				fprintf(stderr, "Two successive calls to MPI_Wtime gave strange results: (%f)(%f)\n", t1 , t2);
		}

		for(i = 0; i < 10; i++)
		{
				t1 = MPI_Wtime();
				sleep(1);
				t2 = MPI_Wtime();
				if(t2 - t1 >= (1 - 0.01) && t2 - t1 <= 5.0) break;

				if(t2 - t1 > 5.0) i = 9;
		}

		if(i == 10){
				fprintf(stderr, "Timer around sleep(1) did not give 1 second;gave %f\n", t2 - t1);
				err++;
		}

		tick = MPI_Wtick();
		if(tick > 1.0 || tick < 0.0)
		{
				err++;
				fprintf(stderr, "MPI_Wtick gave a strange result: (%f)\n", tick);
		}
		MPI_Finalize();

		return 0;
}

