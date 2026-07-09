//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) A CUDA program which takes a string as input and determines the number of occcurences of a character 'a' in the string. This program uses atomicAdd() function.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void CUDACount(char* A,unsigned int *d_co){
	int i=threadIdx.x;
	if(A[i]=='a')
		atomicAdd(d_co,1);
}

int main(){
	char A[N];
	char *d_A;
	unsigned int *co=(unsigned int*)malloc(sizeof(unsigned int));
	unsigned int *d_co;
	unsigned int *rs=(unsigned int*)malloc(sizeof(unsigned int));
	int len;

	printf("enter string:");
	fgets(A,N,stdin);
	len=strlen(A);
	*co=0;

	cudaEvent_t start,stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	cudaMalloc((void**)&d_A,len*sizeof(char));
	cudaMalloc((void**)&d_co,sizeof(unsigned int));

	cudaMemcpy(d_A,A,len*sizeof(char),cudaMemcpyHostToDevice);
	cudaMemcpy(d_co,co,sizeof(unsigned int),cudaMemcpyHostToDevice);

	cudaEventRecord(start,0);

	CUDACount<<<1,len>>>(d_A,d_co);

	cudaError_t error=cudaGetLastError();
	if(error!=cudaSuccess){
		printf("CUDA Error: %s\n",cudaGetErrorString(error));
	}

	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);

	float elapsedTime;
	cudaEventElapsedTime(&elapsedTime,start,stop);

	cudaMemcpy(rs,d_co,sizeof(unsigned int),cudaMemcpyDeviceToHost);

	printf("total occurences of a=%u\n",*rs);
	printf("time taken=%f",elapsedTime);

	cudaFree(d_A);
	cudaFree(d_co);
	printf("\n");
	return 0;
}
