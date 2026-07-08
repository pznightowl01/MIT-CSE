//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Implement a CUDA program to add two vectors of length N by keeping threads per block = 256 (constant) and varying number of blocks.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>

__global__ void vecadd(int *A, int *B, int *C, int n) {
    int index=blockIdx.x*blockDim.x+threadIdx.x;
    if(index<n) {
        C[index]=A[index]+B[index];
    }
}

int main() {
    int n;
    printf("length of the vector: ");
    scanf("%d", &n);

    int tpb=256;
    int gridn=(n+tpb-1)/tpb;

    int *a,*b,*c;
    int *A,*B,*C;

    a=(int*)malloc(n*sizeof(int));
    b=(int*)malloc(n*sizeof(int));
    c=(int*)malloc(n*sizeof(int));

    for(int i=0; i<n; i++) {
        a[i]=i;
        b[i]=i*2;
    }

    cudaMalloc((void**)&A, n*sizeof(int));
    cudaMalloc((void**)&B, n*sizeof(int));
    cudaMalloc((void**)&C, n*sizeof(int));

    cudaMemcpy(A,a,n*sizeof(int),cudaMemcpyHostToDevice);
    cudaMemcpy(B,b,n*sizeof(int),cudaMemcpyHostToDevice);

    vecadd<<<gridn, tpb>>>(A,B,C,n);

    cudaMemcpy(c,C,n*sizeof(int),cudaMemcpyDeviceToHost);

    for (int i=0; i<n; i++) {
        printf("result[%d] = %d\n", i, c[i]);
    }

    cudaFree(A);
    cudaFree(B);
    cudaFree(C);

    free(a);
    free(b);
    free(c);

    return 0;
}
