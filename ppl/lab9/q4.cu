//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program that reads an input matrix A of size mxn and produces an output matrix B of size mxn such that, each element of the output matrix is calculated in parallel. Each element, B[i][j], in the output matrix is obtained by adding the elements in ith row and jth column of the input matrix A.

//		A					B
//	1	2	3		O/p:	11	13	15
//	4	5	6			20	22	24

#include "cuda_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"

__global__ void comp(int* A,int* B,int m,int n){
	int i=threadIdx.y+blockIdx.y*blockDim.y;
	int j=threadIdx.x+blockIdx.x*blockDim.x;
	if(i<m&&j<n){
		int r=0,c=0;
		for(int k=0;k<n;k++)r+=A[i*n+k];
			for(int k=0;k<m;k++)c+=A[k*n+j];
			B[i*n+j]=r+c;
	}
}

int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	
	int sz=m*n*sizeof(int);
	
	int *hA=(int*)malloc(sz);
	int *hB=(int*)malloc(sz);
	
	for(int i=0;i<m*n;i++)
		scanf("%d",&hA[i]);
	
	int *dA,*dB;
	
	cudaMalloc(&dA,sz);cudaMalloc(&dB,sz);
	cudaMemcpy(dA,hA,sz,cudaMemcpyHostToDevice);
	
	dim3 t(16,16),b((n+15)/16,(m+15)/16);
	comp<<<b,t>>>(dA,dB,m,n);
	
	cudaMemcpy(hB,dB,sz,cudaMemcpyDeviceToHost);
	
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
			printf("%d\t",hB[i*n+j]);
	printf("\n");
	}
	
	cudaFree(dA);
	cudaFree(dB);
	free(hA);
	free(hB);
	
	return 0;
}
