//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Implement at least 2 programs to identify deadlock conditions in synchronous send and standard send with multiple point to point communications between two processes

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int rank;
    int data = 20;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Process 0: Sending data to Process 1\n");
        MPI_Ssend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        MPI_Recv(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0: Received data\n");
    }
    else if (rank == 1)
    {
        printf("Process 1: Sending data to Process 0\n");
        MPI_Ssend(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1: Received data\n");
    }
    MPI_Finalize();
    return 0;
}
