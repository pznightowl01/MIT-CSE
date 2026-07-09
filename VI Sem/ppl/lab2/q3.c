//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read N elements of the array in the root process (process 0) where N is equal to the total number of processes. The root process sends one value to each of the slaves. Let even ranked process finds square of the received element and odd ranked process finds cube of received element. Use Buffered send.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int rank, size, N;
    int *array = NULL;
    int val, res;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    N = size;

    int buffer_size = 2 * (N - 1) * sizeof(int) + 2 * MPI_BSEND_OVERHEAD;
    int *buffer = (int *)malloc(buffer_size);
    MPI_Buffer_attach(buffer, buffer_size);

    if (rank == 0) {
        array = (int *)malloc(N * sizeof(int));
        printf("Enter %d elements:\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &array[i]);
        }
        for (int i = 1; i < N; i++) {
            MPI_Bsend(&array[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for (int i = 1; i < N; i++) {
            MPI_Recv(&res, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            printf("Root received result %d from process %d\n", res, i);
        }
        free(array);
    }
    else {
        MPI_Recv(&val, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        if (rank % 2 == 0) {
            res = val * val;
            printf("Process %d (Even): %d^2 = %d\n", rank, val, res);
        } else {
            res = val * val * val;
            printf("Process %d (Odd): %d^3 = %d\n", rank, val, res);
        }
        MPI_Bsend(&res, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);

    MPI_Finalize();
    return 0;
}

