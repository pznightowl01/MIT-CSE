//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a program in MPI to simulate simple calculator. Perform each operation using different process in parallel.

#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]){
	int a = 2, b = 4, x, rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	switch(rank){
    		case 0:
    		x = a+b;
    		printf("Rank %d gives a+b = %d\n", rank, x);
    		break;
    	case 1:
    		x = a-b;
    		printf("Rank %d gives a-b = %d\n", rank, x);
    		break;
    	case 2:
    		x = a*b;
    		printf("Rank %d gives a*b = %d\n", rank, x);
    		break;
    	case 3:
    		x = a/b;
    		printf("Rank %d gives a/b = %d\n", rank, x);
    		break;

    	default:
    		printf("Invalid rank number %d \n", rank);
    		break;
    	}
    	MPI_Finalize();
	return 0;
	}
