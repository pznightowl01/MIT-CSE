//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to read a word of length N. Using N processes including
// the root get output word with the pattern as shown in example. Display the
// resultant output word in the root.
// Example: Input: PCAP
// Output: PCCAAAPPPP

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
    int r,s;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&r);
    MPI_Comm_size(MPI_COMM_WORLD,&s);

    int x,y,a[10];
    char str[10];
    x=r+1;

    if(r==0){
        printf("Enter word: ");
        fflush(stdout);
        scanf("%s",str);
    }

    MPI_Scan(&x,&y,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    MPI_Gather(&y,1,MPI_INT,a,1,MPI_INT,0,MPI_COMM_WORLD);

    if(r==0){
        int i=0,j=0,t=s*(s+1)/2;
        while(i<t){
            if(i==a[j])
            	j++;
            	printf("%c",str[j]);
            	fflush(stdout);
            	i++;
        }
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

