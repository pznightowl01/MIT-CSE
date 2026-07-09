//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to multiply two Matrices for the following specifications:
//a. Each row of resultant matrix to be computed by one thread.
//b. Each column of resultant matrix to be computed by one thread.
//c. Each element of resultant matrix to be computed by one thread.

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

__global__ void mult_m_r(int *a, int *b, int *c, int n, int m, int k){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<n){
        for(int j=0; j<k; j++){
            int sum=0;
            for(int l=0; l<m; l++){
                sum+=a[i*m+l]*b[l*k+j];
            }
            c[i*k+j]=sum;
        }
    }
}

__global__ void mult_m_c(int *a, int *b, int *c, int n, int m, int k){
    int j=blockIdx.x*blockDim.x+threadIdx.x;
    if(j<k){
        for(int i=0; i<n; i++){
            int sum=0;
            for(int l=0; l<m; l++){
                sum+=a[i*m+l]*b[l*k+j];
            }
            c[i*k+j]=sum;
        }
    }
}

__global__ void mult_m_ele(int *a, int *b, int *c, int n, int m, int k){
    int idx=blockIdx.x*blockDim.x+threadIdx.x;
    if(idx<n*k){
        int i=idx/k;
        int j=idx%k;
        int sum=0;
        for(int l=0; l<m; l++){
            sum+=a[i*m+l]*b[l*k+j];
        }
        c[i*k+j]=sum;
    }
}

int main(){
    int n, m, k;
    printf("enter dim of A (nxm): ");
    scanf("%d %d", &n, &m);
    printf("enter dim of B col (k): ");
    scanf("%d", &k);

    size_t szA=sizeof(int)*n*m;
    size_t szB=sizeof(int)*m*k;
    size_t szC=sizeof(int)*n*k;

    int *a=(int *)malloc(szA);
    int *b=(int *)malloc(szB);
    int *c=(int *)malloc(szC);
    
    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, szA);
    cudaMalloc((void **)&d_b, szB);
    cudaMalloc((void **)&d_c, szC);

    printf("enter matrix a:\n");
    for(int i=0; i<n*m; i++)
    	scanf("%d", &a[i]);

    printf("enter matrix b:\n");
    for(int i=0; i<m*k; i++)
    	scanf("%d", &b[i]);

    cudaMemcpy(d_a, a, szA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, szB, cudaMemcpyHostToDevice);

    int blk_sz=256;
    int grid_sz;
    int opt;

    printf("enter opt:-\n(1.row-wise\n2.column-wise\n3.element-wise):\n");
    scanf("%d", &opt);

    switch(opt){
    case 1:
        printf("resultant matrix (case 1):\n");
        grid_sz=(n+blk_sz-1)/blk_sz;
        mult_m_r<<<grid_sz, blk_sz>>>(d_a, d_b, d_c, n, m, k);
        
        cudaMemcpy(c, d_c, szC, cudaMemcpyDeviceToHost);
        printf("resultant matrix:\n");
    	for(int i=0; i<n; i++){
        	for(int j=0; j<k; j++){
            		printf("%d ", c[i*k+j]);
        	}
        printf("\n");
    	}
        break;
        
    case 2:
        grid_sz=(k+blk_sz-1)/blk_sz;
        mult_m_c<<<grid_sz, blk_sz>>>(d_a, d_b, d_c, n, m, k);
        cudaMemcpy(c, d_c, szC, cudaMemcpyDeviceToHost);
        
        printf("resultant matrix:\n");
    	for(int i=0; i<n; i++){
        	for(int j=0; j<k; j++){
            		printf("%d ", c[i*k+j]);
        	}
        printf("\n");
    	}
        break;
        
    case 3:
        grid_sz=(n*k+blk_sz-1)/blk_sz;
        mult_m_ele<<<grid_sz, blk_sz>>>(d_a, d_b, d_c, n, m, k);
        cudaMemcpy(c, d_c, szC, cudaMemcpyDeviceToHost);
        
        printf("resultant matrix:\n");
    	for(int i=0; i<n; i++){
        	for(int j=0; j<k; j++){
            		printf("%d ", c[i*k+j]);
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
