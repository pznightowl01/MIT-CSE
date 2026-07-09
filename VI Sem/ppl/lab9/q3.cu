//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program that reads a matrix A of size mxn and produce an opnput matrix B of same size such that it replcs all the non-border elements(numbers in bold) of A with its equivalent 1's complement and remaining elements same as matrix A
//		A						B
//	1	2	3	4		1	2	3	4
//	6	5	8	3		6	10	111	3
//	2	4	10	1		2	11	101	1
//	9	1	2	5		9	1	2	5

#include "cuda_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include "device_launch_parameters.h"
__global__ void comp(int* da, int m, int n) {
    int r = threadIdx.x;
    if (r<= 0||r>=m-1)
        return;
    for (int c=1; c<n-1; c++) {
        int num=da[r*n+c];
        int res=0, plc=1;
        if (num==0) res=1;
        else {
            while (num>0) {
                res=((num%2==0)?1:0)*plc+res;
                num/=2;
                plc*=10;
            }
        }
        da[r*n+c]=res;
    }
}
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int sz=m*n*sizeof(int);
    int *h=(int*)malloc(sz);
    for (int i=0; i<m*n; i++) scanf("%d", &h[i]);
    int* d;
    cudaMalloc(&d, sz);
    cudaMemcpy(d, h, sz, cudaMemcpyHostToDevice);
    comp<<<1, m>>>(d, m, n);
    cudaMemcpy(h, d, sz, cudaMemcpyDeviceToHost);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) printf("%d\t", h[i*n+j]);
        printf("\n");
    }
    cudaFree(d);
    free(h);
    return 0;
}
