//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read N elements of an array in the master process. Let N processes including master process check the array values are primes or not.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int isPrime(int num){
    if (num <= 1)
        return 0;

    for (int i = 2; i * i <= num; i++){
        if (num % i == 0){
        	return 0;
        	}
    }
    return 1;
}

int main(int argc, char *argv[]){
    int rank, size;
    int *arr = NULL;
    int element;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        arr = (int *)malloc(size * sizeof(int));

        printf("Enter %d elements:\n", size);
        for (int i = 0; i < size; i++){
            scanf("%d", &arr[i]);
            }
    }
    MPI_Scatter(arr, 1, MPI_INT, &element, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (isPrime(element)){
        printf("Process %d: %d is a PRIME number\n", rank, element);
        }
    else{
        printf("Process %d: %d is NOT a prime number\n", rank, element);
        }
    if (rank == 0){
        free(arr);
	}
    MPI_Finalize();
    return 0;
}
