//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read two strings S1 and S2 of same length in the root process.
// Using N processes including the root (string length is evenly divisible by N), produce the resultant string as shown below.
// Display the resultant string process.
// Use collective communication routines.
// Example:
//	String S1:string	String S2:string	Resultant String:slternigntgh

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, len, chunk;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char *S1=NULL, *S2=NULL, *result=NULL;

    if (rank == 0) {
        printf("Enter length of string (multiple of %d): ", size);
	fflush(stdout);
        scanf("%d", &len);

        S1 = (char *)malloc(len*sizeof(char));
        S2 = (char *)malloc(len*sizeof(char));

        printf("Enter string S1: ");
	fflush(stdout);
        scanf("%s", S1);
        printf("Enter string S2: ");
	fflush(stdout);
        scanf("%s", S2);
    }

    MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
    chunk=len/size;

    char *sub1=(char *)malloc(chunk*sizeof(char));
    char *sub2=(char *)malloc(chunk*sizeof(char));
    char *local=(char *)malloc(2*chunk*sizeof(char));

    MPI_Scatter(S1,chunk,MPI_CHAR,sub1,chunk,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(S2,chunk,MPI_CHAR,sub2,chunk,MPI_CHAR,0,MPI_COMM_WORLD);

    int k=0;
    for (int i=0; i<chunk; i++) {
        local[k++]=sub1[i];
        local[k++]=sub2[i];
    }

    if(rank==0)
        result=(char *)malloc(2*len*sizeof(char));

    MPI_Gather(local,2*chunk,MPI_CHAR,result,2*chunk,MPI_CHAR,0,MPI_COMM_WORLD);

    if(rank==0) {
        result[2*len]='\0';
        printf("Resultant String: %s\n", result);
	fflush(stdout);
    }

    MPI_Finalize();
    return 0;
}
