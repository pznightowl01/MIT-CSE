//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program that reads a character type matrix A and integer type matrix B of size mxn. It produces an output string STR such that, every character of A is repeated r times (where r is the integer value in matrix B which is having the same index as that of the character taken in A). Write the kernel such that every value of input matrix must be produced required number of times by one thread.
//Example:
//		A					B
//	p	C	a	P		O/p:	1	2	3	4
//	e	X	a	M			2	4	3	2

#include "cuda_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"

__global__ void comp(char* A,int* B,char* S,int m,int n){
int idx=threadIdx.x+blockIdx.x*blockDim.x;
int total=m*n;
if(idx<total){
int pos=0;
for(int i=0;i<idx;i++)pos+=B[i];
for(int k=0;k<B[idx];k++)S[pos+k]=A[idx];
}}

int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	int sz=m*n;
	
	char *hA=(char*)malloc(sz*sizeof(char));
	int *hB=(int*)malloc(sz*sizeof(int));
	
	for(int i=0;i<sz;i++)
		scanf(" %c",&hA[i]);
	for(int i=0;i<sz;i++)
		scanf("%d",&hB[i]);
		
	int out=0;
	for(int i=0;i<sz;i++)
		out+=hB[i];
		
	char *hS=(char*)malloc(out*sizeof(char));
	
	char *dA,*dS;
	int *dB;
	
	cudaMalloc(&dA,sz);cudaMalloc(&dB,sz*sizeof(int));
	cudaMalloc(&dS,out);
	
	cudaMemcpy(dA,hA,sz,cudaMemcpyHostToDevice);
	cudaMemcpy(dB,hB,sz*sizeof(int),cudaMemcpyHostToDevice);
	
	comp<<<(sz+255)/256,256>>>(dA,dB,dS,m,n);
	cudaMemcpy(hS,dS,out,cudaMemcpyDeviceToHost);
	
	for(int i=0;i<out;i++)
		printf("%c",hS[i]);
	
	cudaFree(dA);
	cudaFree(dB);
	cudaFree(dS);
	free(hA);
	free(hB);
	free(hS);
	
	return 0;
}
