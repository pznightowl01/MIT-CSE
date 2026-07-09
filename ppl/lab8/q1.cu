//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to add two Matrices for the following specifications:
//a. Each row of resultant matrix to be computed by one thread.
//b. Each column of resultant matrix to be computed by one thread.
//c. Each element of resultant matrix to be computed by one thread.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void add_m_r(int *a, int *b, int *c, int n, int m){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n){
        for (int j=0; j<m; j++){
            c[i*m+j]=a[i*m+j]+b[i*m+j];
        }
    }
}

__global__ void add_m_c(int *a, int *b, int *c, int n, int m){
    int j=blockIdx.x*blockDim.x+threadIdx.x;
    if(j<m){
        for(int i=0; i<n; i++){
            c[i*m+j]=a[i*m+j]+b[i*m+j];
        }
    }
}

__global__ void add_m_ele(int *a, int *b, int *c, int n, int m){
    int idx=blockIdx.x*blockDim.x+threadIdx.x;
    if(idx<n*m){
        int i=idx/m;
        int j=idx%m;
        c[i*m+j]=a[i*m+j]+b[i*m+j];
    }
}

int main(){
    int n, m;
    printf("enter the dim of the matrices (nxm): ");
    
    scanf("%d %d", &n, &m);
    int size=sizeof(int)*n*m;

    int *a=(int *)malloc(size);
    int *b=(int *)malloc(size);
    int *c=(int *)malloc(size);
    
    int *d_a, *d_b, *d_c;
    
    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    printf("enter the matrix a:\n");
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            scanf("%d", &a[i*m+j]);
        }
    }

    printf("enter the matrix b:\n");
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            scanf("%d", &b[i*m+j]);
        }
    }

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    int blk_sz=256;
    int grid_sz;

    int opt;
    printf("enter opt:-\n(1.row-wise\n2.column-wise\n3.element-wise):\n");
    scanf("%d", &opt);
    switch (opt){
    case 1:
        grid_sz=(n+blk_sz-1)/blk_sz;
        
        add_m_r<<<grid_sz, blk_sz>>>(d_a, d_b, d_c, n, m);

        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
        
        printf("resultant matrix (case 1):\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                printf("%d ", c[i*m+j]);
            }
            printf("\n");
        }
        break;
        
    case 2:
        grid_sz=(m+blk_sz-1)/blk_sz;
        add_m_c<<<grid_sz, blk_sz>>>(d_a, d_b, d_c, n, m);

        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
        printf("resultant matrix (case 2):\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                printf("%d ", c[i*m+j]);
            }
            printf("\n");
        }
        break;
        
    case 3:
        grid_sz=(n*m+blk_sz-1)/blk_sz;
        add_m_ele<<<grid_sz, blk_sz>>>(d_a, d_b, d_c, n, m);

        cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
        printf("resultant matrix (case 3):\n");
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                printf("%d ", c[i*m+j]);
            }
            printf("\n");
        }
        break;
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);
    return 0;
}
