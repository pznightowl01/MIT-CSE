//Name: Princita Zina Miranda
//Section: SCE-C
//Roll no: C17, Reg no: 220905115

//Q) Write a program in CUDA to perform odd even transposition sort in parallel

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void oddeven(int *A,int n,int phase){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    int idx=2*i+phase;
    if(idx+1<n){
        if(A[idx]>A[idx+1]){
            int t=A[idx];
            A[idx]=A[idx+1];
            A[idx+1]=t;
        }
    }
}

int main(){
    int n;
    printf("length of the vector:\n");
    scanf("%d",&n);

    int a[n];
    printf("enter elements:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    int *A;
    cudaMalloc((void**)&A,n*sizeof(int));
    cudaMemcpy(A,a,n*sizeof(int),cudaMemcpyHostToDevice);

    int thr=256;
    int blks=(n/2+thr-1)/thr;

    for(int p=0;p<n;p++){
        oddeven<<<blks,thr>>>(A,n,p%2);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(a,A,n*sizeof(int),cudaMemcpyDeviceToHost);

    printf("Sorted array:\n");
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");

    cudaFree(A);
    return 0;
}
