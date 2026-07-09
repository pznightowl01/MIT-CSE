//Name: Princita Zina Miranda
//Section: SCE-C
//Roll no: C17, Reg no: 220905115

//Q) Write a program in CUDA which takes N integers as input.
//It converts these integers into their corresponding octal values
//and stores the result in another array in parallel.

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include<stdio.h>

__global__ void to_octal(int *da,int *db,int n){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n){
        int num=da[i];
        int oct=0,place=1;
        while(num>0){
            oct+=(num%8)*place;
            num/=8;
            place*=10;
        }
        db[i]=oct;
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);

    int a[n],b[n];
    int *da,*db;

    printf("Enter elements:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    cudaMalloc((void**)&da,n*sizeof(int));
    cudaMalloc((void**)&db,n*sizeof(int));

    cudaMemcpy(da,a,n*sizeof(int),cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n+threads-1)/threads;

    to_octal<<<blocks,threads>>>(da,db,n);
    cudaDeviceSynchronize();

    cudaMemcpy(b,db,n*sizeof(int),cudaMemcpyDeviceToHost);

    printf("Octal values:\n");
    for(int i=0;i<n;i++)
        printf("%d ",b[i]);
    printf("\n");

    cudaFree(da);
    cudaFree(db);
    return 0;
}
