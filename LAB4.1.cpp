#include <cstdio>
#include "mpi.h"

int main(int argc, char *argv[])
{	//теги сообщений 1 - от мастера, 2 - от рабочих
	int numt, rank;
	int rowsForA, extraRows, rows; //Дополнительные строки если кол-во строк не делится на целое
	int buff = 0;
	MPI_Status status;
	double beginTime, endTime;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matrixResult[i][j] = 0;
		}

	}
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numt);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) { // Мастер распределяет строки между процессами
		printf("Master is here\n");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrix1[i][j] = Rrand(-10, 10);
			}

		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				matrix2[i][j] = Rrand(-10, 10);
			}

		}
		beginTime = MPI_Wtime();
		rowsForA = N / (numt - 1); //общее кол-во процессов минус 1 
		extraRows = N % (numt-1); //Остаток требующий распределения
		
	MPI_Finalize();

}	
