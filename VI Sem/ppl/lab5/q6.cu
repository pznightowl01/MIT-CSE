//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) write a program in CUDA to perform odd even transposition sort in parallel

#include <stdio.h>

__global__ void oddeven(int *a,int n,int phase){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    int idx=2*i+phase;
    if(idx+1<n){
        if(a[idx]>a[idx+1]){
            int t=a[idx];
            a[idx]=a[idx+1];
            a[idx+1]=t;
        }
    }
}

int main(){
    int n;
    printf("size: ");
    scanf("%d",&n);

    int a[n];
    printf("array:\n");
    for(int i=0;i<n;i++)scanf("%d",&a[i]);

    int *d;
    cudaMalloc((void**)&d,n*sizeof(int));
    cudaMemcpy(d,a,n*sizeof(int),cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(n/2+threads-1)/threads;

    for(int p=0;p<n;p++){
        oddeven<<<blocks,threads>>>(d,n,p%2);
        cudaDeviceSynchronize();
    }

    cudaMemcpy(a,d,n*sizeof(int),cudaMemcpyDeviceToHost);

    printf("sorted:\n");
    for(int i=0;i<n;i++)printf("%d ",a[i]);
    printf("\n");

    cudaFree(d);
    return 0;
}
