//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read a 3 X 3 matrix. Enter an element to be searched in the root process. Find the number of occurrences of this element in the matrix using three processes.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    int rank, size, ele, result;
    int mat[3][3];
    int sMat[3];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(size!=3){
        if (rank==0)
            printf("Number of processes must be 3\n");
            fflush(stdout);
        MPI_Finalize();
        exit(0);
    }

    if(rank==0){
        printf("Enter the elements of 3x3 matrix:\n");
        fflush(stdout);
        for (int i=0; i<3; i++)
            for (int j=0; j<3; j++)
                scanf("%d", &mat[i][j]);

        printf("Enter element to be searched: ");
        fflush(stdout);
        scanf("%d", &ele);
    }

    MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(mat,3,MPI_INT,sMat,3,MPI_INT,0,MPI_COMM_WORLD);

    int res=0;
    for (int i=0; i<3; i++)
        if (sMat[i]==ele)
            res++;

    MPI_Reduce(&res,&result,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0)
        printf("Total number of occurrences is: %d\n", result);
        fflush(stdout);

    MPI_Finalize();
    return 0;
}

