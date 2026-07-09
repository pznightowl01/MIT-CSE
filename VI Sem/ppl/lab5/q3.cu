//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to process a ID array containing angles in radians to generate sine of the angles in the output array. Use appropriate function.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void vecadd(float*A,float*C){
    int index=blockIdx.x*blockDim.x+threadIdx.x;
    C[index]=sinf(A[index]);
}

int main(){
    int n;
    printf("length of the vector : ");
    scanf("%d",&n);

    float a[n],c[n];
    float *A,*C;

    cudaMalloc((void **)&A,n*sizeof(float));
    cudaMalloc((void **)&C,n*sizeof(float));

    printf("Enter vector one : ");
    for(int i=0;i<n;i++)
        scanf("%f",&a[i]);
    
    cudaMemcpy(A,a,n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 grid(n,1,1);
    dim3 blk(1,1,1);

    vecadd<<<grid,blk>>>(A,C);
    cudaMemcpy(c,C,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("%f\t",c[i]);
    printf("\n");
    cudaFree(A);
    cudaFree(C);
}
