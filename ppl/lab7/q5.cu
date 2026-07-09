//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program which reads a string Sin and produces an output string T as shown below.
//Input:
//Sin: "Hai"
//Ouput:
//T: "Haaiii "

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

__global__ void repeat(char *Sin,char *T){
	int i=threadIdx.x;
	int pos=0;

	for(int k=0;k<i;k++)
		pos+=k+1;

	for(int j=0;j<=i;j++)
		T[pos+j]=Sin[i];
}

int main(){
	char Sin[MAX],T[MAX];
	char *d_Sin,*d_T;
	int len,size=0;

	printf("enter string:");
	fgets(Sin,MAX,stdin);
	Sin[strcspn(Sin,"\n")]='\0';

	len=strlen(Sin);

	for(int i=1;i<=len;i++)
		size+=i;

	cudaMalloc((void**)&d_Sin,len*sizeof(char));
	cudaMalloc((void**)&d_T,size*sizeof(char));

	cudaMemcpy(d_Sin,Sin,len*sizeof(char),cudaMemcpyHostToDevice);

	repeat<<<1,len>>>(d_Sin,d_T);

	cudaMemcpy(T,d_T,size*sizeof(char),cudaMemcpyDeviceToHost);
	T[size]='\0';

	printf("T:%s\n",T);

	cudaFree(d_Sin);
	cudaFree(d_T);

	return 0;
}
