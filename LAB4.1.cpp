#include <cstdio>
#include "mpi.h"

int main(int argc, char *argv[])
{	
	int numt, rank;
	int rowsForA, extraRows, rows; 
	int buff = 0;
	MPI_Status status;
	double beginTime, endTime;
	
	
	MPI_Finalize();

}	