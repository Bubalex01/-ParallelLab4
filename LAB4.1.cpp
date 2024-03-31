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
		for (int i = 1; i <= numt - 1; i++) { //Отправка начальный значений
			if (i <= extraRows) {
				rows = rowsForA + 1;
			}
			else {
				rows = rowsForA;
			}
			MPI_Send(&buff, 1, MPI_INT, i, 1, MPI_COMM_WORLD);//начальный номер строки
			MPI_Send(&rows, 1, MPI_INT, i, 1, MPI_COMM_WORLD);//количество строк
			MPI_Send(&matrix1[buff][0], N * N, MPI_INT, i, 1, MPI_COMM_WORLD);//Отправка строки
			MPI_Send(&matrix2, N * N, MPI_INT, i, 1, MPI_COMM_WORLD);
			buff += rows;
		}
		for (int i = 1; i <= numt - 1; i++) { //Получение результата
			MPI_Recv(&buff, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&rows, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&(matrixResult[buff][0]), rows*N, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
		}
		endTime = MPI_Wtime();
		double time = endTime - beginTime;
		printf("Time %f s\n", time);
	}
	else {
		MPI_Recv(&buff, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&rows, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&matrix1[buff][0], N * N, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&matrix2, N * N, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		//printf("%d\n", buff+rows);
		for (int i = buff; i < buff+rows; i++) {
			for (int k = 0; k < N; k++) {
				for (int j = 0; j < N; j++) {
					matrixResult[i][j] += matrix1[i][k] * matrix2[k][j];
				}
			}
		}
		MPI_Send(&buff, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&(matrixResult[buff][0]), rows * N, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}
	MPI_Finalize();

}	