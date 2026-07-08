// Name : Princita Zina Miranda
// Section : SCE-C
// Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program where the master process (process 0) sends a number to each of the slaves and the slaves processes recieve the number and prints. Use standard

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;
    int number = 5;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        for (int i = 1; i < size; i++){
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Master sent %d to process %d\n", number, i);
            fflush(stdout);
        }
    }
    else if (rank == 1){
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received number %d\n", rank, number);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}
