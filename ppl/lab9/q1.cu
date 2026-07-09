//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to perform parallel Sparse Matrix-Vector multiplication using compressed sparse row (CSR) storage format. Represent the input sparse matrix in CSR format in the host code.

#include "cuda_runtime.h"
#include <stdio.h>
#include <string.h>
#include "device_launch_parameters.h"

__global__ void csr(int* da, int* ca, int* ra, int* db, int* o){
	int k=threadIdx.x;
	int s=ra[k];
	int e=ra[k+1];
	for(int j=s; j<e; j++){
		o[k]+=da[j]*db[ca[j]];
	}
}

int main(){
	int m, n;
	printf("enter m & n: ");
	scanf("%d\t%d", &m, &n);
	int a[m][n], b[n];
	int c=0;
	printf("enter mat: ");
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			scanf("%d", &a[i][j]);
			if(a[i][j]!=0)
				c++;
		}
	}
	
	printf("enter vector: ");
	for(int i=0; i<n; i++){
		scanf("%d", &b[i]);
	}
		
	int data[c], col[c], row[m+1];
	int k1=0, k2=0;
	row[m]=c;
	for(int i=0; i<m; i++){
		row[k2++]=k1;
		for(int j=0; j<n; j++){
			if(a[i][j]!=0){
				data[k1]=a[i][j];
				col[k1++]=j;
			}
		}
	}
	int* da, *ca, *ra, *db, *o;
	
	cudaMalloc((void **)&da, c*sizeof(int));
	cudaMalloc((void **)&ca, c*sizeof(int));
	cudaMalloc((void **)&ra, (m+1)*sizeof(int));
    	cudaMalloc((void **)&db, n*sizeof(int));
    	cudaMalloc((void **)&o, m*sizeof(int));
    	
    	cudaMemcpy(da,data, c*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(ca,col, c*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(ra,row, (m+1)*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(db,b, n*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemset(o, 0, m*sizeof(int));
	
	dim3 grid(1, 1, 1);
	dim3 blk(m, 1, 1);

	csr<<<grid, blk>>>(da,ca, ra, db,o);

	int oh[m];
	cudaMemcpy(oh, o, m*sizeof(int), cudaMemcpyDeviceToHost);

	for(int i=0; i<m; i++)
		printf("%d\t",oh[i]);
	printf("\n");
	
	cudaFree(da);
	cudaFree(ca);
	cudaFree(ra);
	cudaFree(db);
	cudaFree(o);
}
