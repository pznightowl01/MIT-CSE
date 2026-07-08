//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read matrix A of size 5 X 5. It produces a resultant matrix B of size 5 X 5. It sets all the principal diagonal elements of B matrix with 0. It replaces each row elements in the B matrix in the following manner: If the element is below the principal diagonal it replaces it with the maximum value of the column in the A matrix having the same row number of B. If the element is above the principal diagonal it replaces it with the minimum value of the column in the A matrix having the same row number of B. Produce the B Matrix using 5 processes. Use only Collective communication routines except broad- cast routine.

#include "mpi.h"
#include <stdio.h>
int main(int c,char**v){

	MPI_Init(&c,&v);
	int r,s;
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&s);
	int A[5][5],row[5],Brow[5],B[5][5];
	
	if(r==0){
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				scanf("%d",&A[i][j]);
		}
		
	MPI_Bcast(A,25,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Scatter(A,5,MPI_INT,row,5,MPI_INT,0,MPI_COMM_WORLD);
	int mn=row[0],mx=row[0];
	
	for(int i=1;i<5;i++){
		if(row[i]<mn)mn=row[i];
			if(row[i]>mx)mx=row[i];
	}
	
	for(int j=0;j<5;j++){
		if(r==j)
			Brow[j]=0;
		else if(r>j)
			Brow[j]=mx;
		else
			Brow[j]=mn;
	}
	
	MPI_Gather(Brow,5,MPI_INT,B,5,MPI_INT,0,MPI_COMM_WORLD);
	if(r==0){
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++)
				printf("%d ",B[i][j]);
				printf("\n");
		}
	}
MPI_Finalize();
return 0;
}
