//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read a value NxM numjber of elements into 1D array in the root, where N is the total no. of processes.
// Find the square of the first M no.'s, the cube of next M no.'s and so on.
// Print the results in the root.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int rank,size,N,i,le=0,lo=0,ge=0,go=0;
    int *a=NULL,*b;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
    {
        scanf("%d",&N);
        a=(int*)malloc(N*sizeof(int));
        for(i=0;i<N;i++)
            scanf("%d",&a[i]);
    }

    MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);

    b=(int*)malloc((N/size)*sizeof(int));

    MPI_Scatter(a,N/size,MPI_INT,b,N/size,MPI_INT,0,MPI_COMM_WORLD);

    for(i=0;i<N/size;i++)
    {
        if(b[i]%2==0){b[i]=1;le++;}
        else{b[i]=0;lo++;}
    }

    MPI_Gather(b,N/size,MPI_INT,a,N/size,MPI_INT,0,MPI_COMM_WORLD);

    MPI_Reduce(&le,&ge,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    MPI_Reduce(&lo,&go,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0)
    {
        for(i=0;i<N;i++)
            printf("%d ",a[i]);
        printf("\nEven(Count)=%d\nOdd(Count)=%d\n",ge,go);
    }

    MPI_Finalize();
    return 0;
}
