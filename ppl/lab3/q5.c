//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read a value NxM numjber of elements into 1D array in the root, where N is the total no. of processes.
// Find the square of the first M no.'s, the cube of next M no.'s and so on.
// Print the results in the root.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc,char *argv[])
{
    int rank,size,M,i,p;
    int *a=NULL,*b,*c=NULL;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
    {
        scanf("%d",&M);
        a=(int*)malloc(size*M*sizeof(int));
        c=(int*)malloc(size*M*sizeof(int));
        for(i=0;i<size*M;i++)
            scanf("%d",&a[i]);
    }

    MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);

    b=(int*)malloc(M*sizeof(int));

    MPI_Scatter(a,M,MPI_INT,b,M,MPI_INT,0,MPI_COMM_WORLD);

    p=rank+2;
    for(i=0;i<M;i++)
        b[i]=pow(b[i],p);

    MPI_Gather(b,M,MPI_INT,c,M,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        for(i=0;i<size*M;i++)
            printf("%d ",c[i]);
    }

    MPI_Finalize();
    return 0;
}
