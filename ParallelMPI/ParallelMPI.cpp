
#include <stdio.h>
#include <mpi.h>
#include<string.h>
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len);
double f(double x);
int main()
{
	int my_rank, comm_size,n=1024,local_n;
	double a = 0.0, b = 3.0, h, local_a, local_b;
	h = (b - a) / n;
	double local_int, total_int;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	local_n = n / comm_size;

	local_a =a+ my_rank * local_n * h;
	local_b = local_a + local_n * h;

	local_int = Trap(local_a,local_b,local_n,h);

	if (my_rank != 0) {
		MPI_Send(&local_int,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
	}
	else
	{
		total_int = local_int;
		for (int source = 1; source < comm_size; source++)
		{
			MPI_Recv(&local_int, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD,MPI_STATUSES_IGNORE);
			total_int += local_int;
		}
		printf("With n= %d Trapezoidal or estimate\n",n);
		printf("of the intergal from %f to %f = %.15e\n",a,b,total_int);

	}

	MPI_Finalize();
	return 0;
}
double Trap(double left_endpt, double right_endpt, int trap_count, double base_len) {
	double estimate, x;
	int i;
	estimate = (f(left_endpt) + f(right_endpt)) / 2;
	for ( i = 1; i < trap_count; i++)
	{
		x = left_endpt + i * base_len;
		estimate += f(x);
	}
	estimate = estimate * base_len;
	return estimate;

}
double f(double x) {
	return x * x;
}