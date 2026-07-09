//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to perform selection sort in parallel

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>

__global__ void selsortparallel(int *A, int *C, int s)
{
    int i=blockIdx.x*blockDim.x+threadIdx.x;

    if(i<s){
        int k=0;
        for (int j=0; j<s; j++){
            if ((A[j]<A[i])||(A[j]==A[i]&&j<i)){
                k++;
            }
        }
        
        C[k]=A[i];
    }
}

int main(){
    int n;

    printf("length of the vector:\n");
    scanf("%d", &n);

    int a[n], c[n];
    int *A, *C;

    cudaMalloc((void **)&A,n*sizeof(int));
    cudaMalloc((void **)&C,n*sizeof(int));

    printf("enter the elements of the vector:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &a[i]);

    cudaMemcpy(A,a,n*sizeof(int), cudaMemcpyHostToDevice);

    dim3 blk(256);
    dim3 grid((n+blk.x-1)/blk.x);

    selsortparallel<<<grid, blk>>>(A, C, n);

    cudaMemcpy(c,C,n*sizeof(int), cudaMemcpyDeviceToHost);

    printf("sorted vector:\n");
    for (int i=0; i<n; i++)
        printf("%d\t", c[i]);
    printf("\n");

    cudaFree(A);
    cudaFree(C);

    return 0;
}
