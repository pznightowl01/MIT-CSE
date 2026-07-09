//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program that takes a string Sin as input and one integer value N and produces an output string, Sout, in parallel by concatenating input string Sin, N times as shown below.
//Input:
//Sin = "Hello" N=3
//Ouput:
//Sout = "HelloHelloHello"

//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) CUDA program to concatenate string Sin N times to produce Sout.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

__global__ void concat(char *Sin,char *Sout,int len,int N){
	int i=threadIdx.x;
	if(i<len){
		for(int j=0;j<N;j++)
			Sout[j*len+i]=Sin[i];
	}
}

int main(){
	char Sin[MAX],Sout[MAX];
	char *d_Sin,*d_Sout;
	int N,len;

	printf("enter string:");
	fgets(Sin,MAX,stdin);
	Sin[strcspn(Sin,"\n")]='\0';

	printf("enter N:");
	scanf("%d",&N);

	len=strlen(Sin);

	cudaMalloc((void**)&d_Sin,len*sizeof(char));
	cudaMalloc((void**)&d_Sout,len*N*sizeof(char));

	cudaMemcpy(d_Sin,Sin,len*sizeof(char),cudaMemcpyHostToDevice);

	concat<<<1,len>>>(d_Sin,d_Sout,len,N);

	cudaMemcpy(Sout,d_Sout,len*N*sizeof(char),cudaMemcpyDeviceToHost);
	Sout[len*N]='\0';

	printf("Sout = %s\n",Sout);

	cudaFree(d_Sin);
	cudaFree(d_Sout);

	return 0;
}
