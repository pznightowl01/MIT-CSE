//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a simple MPI program to find out pow(x, rank) for all the processes where 'x' is the integer constant and 'rank' is the rank of the process. Write a program  in MPI where even ranked process prints "Hello" and odd ranked process prints "World".

#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int main (int argc, char *argv[]){
	int x = 4, rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
    	int val = 1;
    	for (int i = 0; i < rank; i++)
        	val *= x;
    	printf("Power of %d^%d is %d\n", x, rank, val);
    	
    	if(rank%2==0){
    		printf("Rank: %d, Hello\n", rank);
    		printf("\n");
    	}
    	else{
    		printf("Rank: %d, World\n", rank);
    		printf("\n");
    	}
	MPI_Finalize();
	return 0;
	}
