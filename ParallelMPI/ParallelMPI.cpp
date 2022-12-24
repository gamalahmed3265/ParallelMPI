
#include <stdio.h>
#include <mpi.h>
int main()
{
	int my_rank, comm_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	printf("PROC %d of %d >Does anyone have a toothpick\n", my_rank, comm_size);
	MPI_Finalize();
	return 0;
}
