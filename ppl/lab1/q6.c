//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a program in MPI to find the prime numbers between 1 and 100 using two processes

#include <mpi.h>
#include <stdio.h>

int is_prime(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        start = 1;
        end = 50;
    } else {
        start = 51;
        end = 100;
    }

    printf("Process %d finding prime numbers from %d to %d:\n", rank, start, end);

    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}

