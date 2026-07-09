//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA which performs convolution operation on one dimensional input array N of size width using a mask array M of size mask_width to produce the resultant one dimensional array P of size width

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void kernel(float*A,float*B,float*C,int mw,int w){
	int i=blockIdx.x*blockDim.x+threadIdx.x;
	if(i<w){
		int start=i-mw/2;
		float sum=0.0;
	for(int j=0;j<mw;j++){
		int idx=start+j;
		if(idx>=0&&idx<w)
			sum+=A[idx]*B[j];
		}
	
	C[i]=sum;
	}
}

int main(){
	int n1,n2;
	
	scanf("%d",&n1);
	scanf("%d",&n2);
	
	float a[n1],b[n2],c[n1];
	float *A,*B,*C;
	
	cudaMalloc((void**)&A,n1*sizeof(float));
	cudaMalloc((void**)&B,n2*sizeof(float));
	cudaMalloc((void**)&C,n1*sizeof(float));
	
	for(int i=0;i<n1;i++)
		scanf("%f",&a[i]);
		
	for(int i=0;i<n2;i++)
		scanf("%f",&b[i]);
		
	cudaMemcpy(A,a,n1*sizeof(float),cudaMemcpyHostToDevice);
	cudaMemcpy(B,b,n2*sizeof(float),cudaMemcpyHostToDevice);
	
	int blksz=256;
	int gridsz=(n1+blksz-1)/blksz;
	
	kernel<<<gridsz,blksz>>>(A,B,C,n2,n1);
	
	cudaMemcpy(c,C,n1*sizeof(float),cudaMemcpyDeviceToHost);
	
	for(int i=0;i<n1;i++)
		printf("%f ",c[i]);
	
	cudaFree(A);
	cudaFree(B);
	cudaFree(C);
	return 0;
}
