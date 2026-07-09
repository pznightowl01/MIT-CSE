//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to read mxn matrix A and replace 1st row of this matrix by same elements, 2nd row elements by square of each element and 3rd row elements by cube of each element and so on.

#include "cuda_runtime.h"
#include <stdio.h>
#include <string.h>
#include "device_launch_parameters.h"

__global__ void change(int* da,int n){
    int k=threadIdx.x,temp;
    for(int j=0; j<n; j++){
        temp=da[k*n+j];
        for(int i=0; i<k; i++)
            da[k*n+j]*=temp;
    }
}

int main(){
    int m,n;
    printf("enter m,n : ");
    scanf("%d %d",&m,&n);

    int a[m][n];
    printf("enter mat : ");
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            scanf("%d",&a[i][j]);

    int* da;
    cudaMalloc((void **)&da, (m*n)*sizeof(int));
    cudaMemcpy(da,a, m*n*sizeof(int), cudaMemcpyHostToDevice);

    dim3 grid(1, 1, 1);
    dim3 blk(m, 1, 1);

    change<<<grid, blk>>>(da,n);

    cudaMemcpy(a, da, m*n*sizeof(int), cudaMemcpyDeviceToHost);

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            printf("%d\t",a[i][j]);
        printf("\n");
    }
    cudaFree(da);
}
