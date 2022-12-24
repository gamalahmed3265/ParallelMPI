
#include <stdio.h>
#include <mpi.h>
int main()
{
	MPI_Init(NULL,NULL);
	printf("Hello World!\n");
	MPI_Finalize();
	return 0;
}
