//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program to read a matrix A of size NXN. It replaces the principal diagonal elements with zero. Elements above the principal diagonal by their factorial and elements below the principal diagonal by their sum of digits.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__device__ long long factorial(int n){
    if(n<=0) return 1;
    long long res=1;
    for(int i=2;i<=n;i++){
        res*=i;
    }
    return res;
}

__device__ int sumOfDigits(int n){
    int sum=0;
    if(n<0) n=-n;
    while(n>0){
        sum+=n%10;
        n/=10;
    }
    return sum;
}

__global__ void processMatrix(int *a,long long *b,int n){
    int r=blockIdx.y*blockDim.y+threadIdx.y;
    int c=blockIdx.x*blockDim.x+threadIdx.x;

    if(r<n && c<n){
        int idx=r*n+c;

        if(r==c){
            b[idx]=0;
        }
        else if(c>r){
            b[idx]=factorial(a[idx]);
        }
        else{
            b[idx]=(long long)sumOfDigits(a[idx]);
        }
    }
}

int main(){
    int n;

    printf("enter size of matrix (n): ");
    scanf("%d",&n);

    size_t szA=sizeof(int)*n*n;
    size_t szB=sizeof(long long)*n*n;

    int *a=(int *)malloc(szA);
    long long *b=(long long *)malloc(szB);

    int *d_a;
    long long *d_b;

    cudaMalloc((void **)&d_a,szA);
    cudaMalloc((void **)&d_b,szB);

    printf("enter matrix elements:\n");
    for(int i=0;i<n*n;i++){
        scanf("%d",&a[i]);
    }

    cudaMemcpy(d_a,a,szA,cudaMemcpyHostToDevice);

    dim3 threads(16,16);
    dim3 blocks((n+threads.x-1)/threads.x,(n+threads.y-1)/threads.y);

    processMatrix<<<blocks,threads>>>(d_a,d_b,n);

    cudaMemcpy(b,d_b,szB,cudaMemcpyDeviceToHost);

    printf("resultant matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%lld ",b[i*n+j]);
        }
        printf("\n");
    }

    cudaFree(d_a);
    cudaFree(d_b);
    free(a);
    free(b);

    return 0;
}
