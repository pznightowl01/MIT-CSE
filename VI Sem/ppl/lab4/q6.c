//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program to calculate π-value by integrating f(x) = 4 / (1 + x ^ 2) . Area under the curve is divided into rectangles and the rectangles are distributed to the processors.

#include "mpi.h"
#include <stdio.h>
int main(int c,char**v){

	MPI_Init(&c,&v);
	int r,s,n=1000000;
	double h,sum=0,x,pi;
	
	MPI_Comm_rank(MPI_COMM_WORLD,&r);
	MPI_Comm_size(MPI_COMM_WORLD,&s);
	h=1.0/n;
	
	for(int i=r;i<n;i+=s){
		x=h*(i+0.5);
		sum+=4.0/(1.0+x*x);
	}
	
	sum*=h;
	MPI_Reduce(&sum,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(r==0){
		printf("%f\n",pi);
		}
MPI_Finalize();
return 0;
}
