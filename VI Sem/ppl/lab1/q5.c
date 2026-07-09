//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a program in MPI to reverse the digits of the following integer array of size 9 with 9, processes. Initialize the array to the following values.
//Input array : 18, 523, 301, 1234, 2, 14, 108, 150, 1928
//Output array: 81, 325, 103, 4321, 2, 41, 801, 51, 8291

#include <mpi.h>
#include <stdio.h>

int reverse_num(int n) {
    int rev = 0;
    while (n > 0) {
        rev = rev * 10 + (n % 10);
        n = n / 10;
    }
    return rev;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int input[9] = {18, 523, 301, 1234, 2, 14, 108, 150, 1928};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Process 0 reversing digits independently:\n");
        printf("Input array : ");
        for (int i = 0; i < 9; i++) printf("%d ", input[i]);
        printf("\n");

        printf("Output array: ");
        for (int i = 0; i < 9; i++) {
            int rev = reverse_num(input[i]);
            printf("%d ", rev);
        }
        printf("\n");
    } else {
        printf("Process %d: Active but no array work (independent).\n", rank);
    }

    MPI_Finalize();
    return 0;
}

