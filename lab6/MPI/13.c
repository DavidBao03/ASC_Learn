#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv)
{
		int node, size, i;
		int masternode = 0;

		MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &node);
		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(i = 1; i < argc; i++)
		{
				fprintf(stderr, "myid=%d,procs=%d,argv[%d]=%s\n",node,size,i,argv[i]);
				if(argv[i] && strcmp("lastmaster",argv[i] = 0))
				{
						masternode = size - 1;
				}
		}

		if(node == masternode)
		{
				fprintf(stderr, "myid=%d is masternode Abort!\n", node);
				MPI_Abort(MPI_COMM_WORLD, 99);
		}
		else
		{
				fprintf(stderr, "myid=%d is not masternode Barrier!\n", node);
				MPI_Barrier(MPI_COMM_WORLD);
		}

		MPI_Finalize();

		return 0;
}

