// Name : Princita Zina Miranda
// Section : SCE-C
// Roll no. C17, Reg. no. 220905115

// Q) Implement at least 2 programs to identify deadlock conditions in synchronous send and standard send with multiple point to point communications between two processes

#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank;
    int data1 = 10, data2 = 20;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        printf("Process 0: Sending first message\n");
        MPI_Send(&data1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        printf("Process 0: Sending second message\n");
        MPI_Send(&data2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);

        MPI_Recv(&data1, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&data2, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else if (rank == 1)
    {
        printf("Process 1: Sending first message\n");
        MPI_Send(&data1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

        printf("Process 1: Sending second message\n");
        MPI_Send(&data2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);

        MPI_Recv(&data1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&data2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Finalize();
    return 0;
}
