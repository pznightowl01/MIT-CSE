//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read value of N in the root process.Using N processes, including root, find out 1! + (1+2) + 3! + (1+2+3+4) + 5! + (1+2+3+4+5+6) and print the result in the root process

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int factorial(int n){
    int fact = 1;
    for (int i = 1; i <= n; i++)
        fact *= i;
    return fact;
}

int sum(int n){
    return (n * (n + 1)) / 2;
}

int main(int argc, char *argv[]){
    int rank, size, N;
    int val1, final = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter value of N: ");
        fflush(stdout);
	scanf("%d", &N);


        for (int i = 1; i < size; i++)
            MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    if (size != N){
        if (rank == 0)
            printf("Error\n");
        MPI_Finalize();
        return 0;
    }

    int k = rank + 1;

    if (k % 2 == 1){
        val1 = factorial(k);
        }
    else{
        val1 = sum(k);
        }
    if (rank == 0){
        final = val1;
        for (int i = 1; i < size; i++){
            int temp;
            MPI_Recv(&temp, 1, MPI_INT, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            final += temp;
        }
        printf("Final Result = %d\n", final);
    }
    else{
        MPI_Send(&val1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
