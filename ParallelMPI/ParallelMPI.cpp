
#include <stdio.h>
#include <mpi.h>
#include<string.h>
const int MAX_STRING = 100;
int main()
{
	int my_rank, comm_size;
	char message[MAX_STRING];
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	// every rank or id for Prosc send to 0
	if (my_rank != 0) {
		sprintf_s(message,"Proc %d of %d Does anyone have a toolhpick?\n", my_rank,comm_size);
		/*MPI_Send(void* buf, int count, MPI_Datatype
			datatype, int dest, int tag, MPI_Comm comm)*/
		MPI_Send(message,strlen(message)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
	}
	else
	{
		sprintf_s(message, "Proc %d of %d Does anyone have a toolhpick?\n", my_rank, comm_size);
		// every rank or id Prosc recive from 0
		//q is that proc will be send the message or sender 
		//0 this source
		for (int q = 1; q < comm_size; q++)
		{
			/*MPI_Recv(void* buf, int count, MPI_Datatype
			datatype, int source, int tag,
			MPI_Comm comm, MPI_Status * status)*/
			MPI_Recv(message,MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
			printf("%s", message);
		}
	}

	MPI_Finalize();
	return 0;
}
