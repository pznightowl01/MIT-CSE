//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q)Write a program in CUDA to add two vectors of length N using block size as N

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void vecadd(int *A,int *B,int *C){
    int index=blockIdx.x*blockDim.x+threadIdx.x;
    C[index]=A[index]+B[index];
    }

int main(){
    int n;
    printf("length of the vector : ");
    scanf("%d",&n);

    int a[n],b[n],c[n];
    int *A,*B,*C;

    cudaMalloc((void **)&A,n*sizeof(int));
    cudaMalloc((void **)&B,n*sizeof(int));
    cudaMalloc((void **)&C,n*sizeof(int));

    printf("enter vector a: ");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    printf("enter vector b: ");
    for(int i=0;i<n;i++)
        scanf("%d",&b[i]);
    printf("\n");
    
    cudaMemcpy(A,a,n*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(B,b,n*sizeof(int),cudaMemcpyHostToDevice);

    dim3 grid(n,1,1);
    dim3 blk(1,1,1);

    vecadd<<<grid,blk>>>(A,B,C);
    cudaMemcpy(c,C,n*sizeof(int),cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++)
        printf("result: %d\t",c[i]);
        printf("\n");
    printf("\n");
    cudaFree(A);
    cudaFree(B);
    cudaFree(C);
}
