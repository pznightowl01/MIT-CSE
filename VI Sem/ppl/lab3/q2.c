//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read an integer value M and NxM  elements into an 1D array in the root process, where N is the number of processes.
// Root process sends M elements to each process.
// Each process finds average of M elements it recieved and sends these average values to root.
// Root collects all the values and find the total average.
// Use collective communication routines.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int rank, size, m;
    int *buf = NULL, *buf1;
    int m_avg, t_avg;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        printf("Enter M: ");
	fflush(stdout);
        scanf("%d", &m);

        buf=(int *)malloc(size*m*sizeof(int));
        printf("Enter %d elements:\n", size * m);
	fflush(stdout);

        for (int i=0; i<size*m; i++){
			scanf("%d", &buf[i]);
	}
    }

    MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);

    buf1=(int *)malloc(m*sizeof(int));

    MPI_Scatter(buf,m,MPI_INT,buf1,m,MPI_INT,0,MPI_COMM_WORLD);

    int sum=0;
    for (int i=0; i<m; i++)
        sum+=buf1[i];

    m_avg=sum/m;

    MPI_Reduce(&m_avg,&t_avg, 1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0){
        t_avg=t_avg/size;
        printf("Total Average = %d\n", t_avg);
	fflush(stdout);
        free(buf);
    }

    free(buf1);
    MPI_Finalize();
    return 0;
}
