//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program that reads a MXN matrix A and produces a resultant matrix B of same size as follows: Replace all the even numbered matrix elements with their row sum and odd numbered matrix elements with their column sum.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void transform_matrix(int*a,int*b,int m,int n){
	int r=blockIdx.y*blockDim.y+threadIdx.y;
	int c=blockIdx.x*blockDim.x+threadIdx.x;

	if(r<m&&c<n){
		int val=a[r*n+c];
		int sum=0;

		if(val%2==0){
			for(int i=0;i<n;i++){
				sum+=a[r*n+i];
				}
		}else{
			for(int i=0;i<m;i++){
				sum+=a[i*n+c];
			}
		}
		b[r*n+c]=sum;
	}
}

int main(){
	int m,n;
	printf("Enter dimensions of matrix (m x n): ");
	scanf("%d %d",&m,&n);

	size_t size=sizeof(int)*m*n;

	int*a=(int*)malloc(size);
	int*b=(int*)malloc(size);

	int*d_a,*d_b;

	cudaMalloc((void**)&d_a,size);
	cudaMalloc((void**)&d_b,size);

	printf("Enter elements of matrix A:\n");
	for(int i=0;i<m*n;i++){
		scanf("%d",&a[i]);
	}

	cudaMemcpy(d_a,a,size,cudaMemcpyHostToDevice);

	dim3 threads(16,16);
	dim3 blocks((n+15)/16,(m+15)/16);

	transform_matrix<<<blocks,threads>>>(d_a,d_b,m,n);

	cudaMemcpy(b,d_b,size,cudaMemcpyDeviceToHost);

	printf("Resultant matrix B:\n");
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			printf("%d ",b[i*n+j]);
	}
	printf("\n");
	}

	cudaFree(d_a);
	cudaFree(d_b);
	free(a);
	free(b);

return 0;
}
