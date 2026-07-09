//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program which reads a string consisting of N words and reverse each word of it in parallel.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

__global__ void reverseWords(char *A,char *B,int len){
	int i=threadIdx.x;
	if(i<len){
		if(A[i]==' '){
			B[i]=' ';
			return;
		}
		int start=i,end=i;
		while(start>0 && A[start-1]!=' ') start--;
		while(end<len && A[end]!=' ') end++;
		B[start+(end-1-i)]=A[i];
	}
}

int main(){
	char A[N],B[N];
	char *d_A,*d_B;
	int len;

	printf("enter string:");
	fgets(A,N,stdin);
	len=strlen(A);
	A[len-1]='\0';
	len--;

	cudaMalloc((void**)&d_A,len*sizeof(char));
	cudaMalloc((void**)&d_B,len*sizeof(char));

	cudaMemcpy(d_A,A,len*sizeof(char),cudaMemcpyHostToDevice);

	reverseWords<<<1,len>>>(d_A,d_B,len);

	cudaMemcpy(B,d_B,len*sizeof(char),cudaMemcpyDeviceToHost);
	B[len]='\0';

	printf("reversed words string:%s\n",B);

	cudaFree(d_A);
	cudaFree(d_B);

	return 0;
}
