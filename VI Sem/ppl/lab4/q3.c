//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read 4 X 4 matrix and display the following output using four processes.

//I/p matrix:
//1 2 3 4
//1 2 3 1
//1 1 1 1
//2 1 2 1
//O/p matrix:
//1 2 3 4
//2 4 6 5
//3 5 7 6
//5 6 9 7

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int r, s;
    int n;
    int *matrix=NULL, *rm=NULL;
    int *row, *rs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    if(r==0){
        printf("Enter matrix dimension (N): ");
        fflush(stdout);
        scanf("%d", &n);
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    if(s!=n){
        if(r==0){
        	printf("Error: Number of processes (%d) must equal N (%d)\n", s, n);
        	fflush(stdout);
        	}
        MPI_Finalize();
        return 0;
    }

    row=(int*)malloc(n*sizeof(int));
    rs=(int*)malloc(n*sizeof(int));

    if(r==0){
        matrix=(int*)malloc(n*n*sizeof(int));
        rm=(int*)malloc(n*n*sizeof(int));
        printf("Enter %d elements:\n", n*n);
        fflush(stdout);
        for(int i=0; i<n*n; i++) {
            scanf("%d", &matrix[i]);
        }
    }

    MPI_Scatter(matrix,n,MPI_INT,row,n,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scan(row,rs,n,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(rs,n,MPI_INT,rm,n,MPI_INT,0,MPI_COMM_WORLD);

    if(r==0){
        printf("\nOutput Matrix:\n");
        fflush(stdout);
        for(int i=0; i<n; i++){
            for (int j=0; j<n; j++) {
                printf("%d ", rm[i*n+j]);
            }
            printf("\n");
        }
        free(matrix);
        free(rm);
    }

    free(row);
    free(rs);
    MPI_Finalize();
    return 0;
}
