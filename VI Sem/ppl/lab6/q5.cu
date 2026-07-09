//Name: Princita Zina Miranda
//Section: SCE-C
//Roll no: C17, Reg no: 220905115

//Q) Write a program in CUDA which takes N binary numbers as input and stores the one's complement of each element in another array in parallel

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <string.h>

#define MAX 4

__global__ void ones_complement(char *inp,char *out,int n,int len){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n){
        for(int j=0;j<len;j++){
            char bit=inp[i*len+j];
            out[i*len+j]=(bit=='0')?'1':(bit=='1')?'0':bit;
        }
    }
}

int main(){
    int n;
    printf("enter number of binary numbers: ");
    scanf("%d",&n);

    char hi[n][MAX],ho[n][MAX];
    printf("enter binary numbers (up to %d bits each):\n",MAX-1);
    for(int i=0;i<n;i++)
    	scanf("%s",hi[i]);

    char *inp,*out;
    cudaMalloc((void**)&inp,n*MAX*sizeof(char));
    cudaMalloc((void**)&out,n*MAX*sizeof(char));

    cudaMemcpy(inp,hi,n*MAX*sizeof(char),cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n+threads-1)/threads;
    
    ones_complement<<<blocks,threads>>>(inp,out,n,MAX);
    cudaDeviceSynchronize();

    cudaMemcpy(ho,out,n*MAX*sizeof(char),cudaMemcpyDeviceToHost);

    printf("1's complement values:\n");
    for(int i=0;i<n;i++)
    	printf("%s\n",ho[i]);

    cudaFree(inp);
    cudaFree(out);
    return 0;
}
