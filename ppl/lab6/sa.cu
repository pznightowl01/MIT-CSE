//Name: Princita Zina Miranda
//Section: SCE-C
//Roll no: C17, Reg no: 220905115

//Q) 1D seq. convolution

#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>

__global__ void convolution_1D(float *N,float *M,float *P,int mask_width,int width){
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i<width){
        float Pvalue=0;
        int N_start_point=i-(mask_width/2);
        for(int j=0;j<mask_width;j++){
            if(N_start_point+j>=0 && N_start_point+j<width)
                Pvalue+=N[N_start_point+j]*M[j];
        }
        P[i]=Pvalue;
    }
}

int main(){
    int width,mask_width;
    scanf("%d",&width);
    scanf("%d",&mask_width);

    float *h_N=(float*)malloc(width*sizeof(float));
    float *h_M=(float*)malloc(mask_width*sizeof(float));
    float *h_P=(float*)malloc(width*sizeof(float));

    for(int i=0;i<width;i++)
        scanf("%f",&h_N[i]);
    for(int i=0;i<mask_width;i++)
        scanf("%f",&h_M[i]);

    float *d_N,*d_M,*d_P;
    cudaMalloc((void**)&d_N,width*sizeof(float));
    cudaMalloc((void**)&d_M,mask_width*sizeof(float));
    cudaMalloc((void**)&d_P,width*sizeof(float));

    cudaMemcpy(d_N,h_N,width*sizeof(float),cudaMemcpyHostToDevice);
    cudaMemcpy(d_M,h_M,mask_width*sizeof(float),cudaMemcpyHostToDevice);

    int blockSize=256;
    int gridSize=(width+blockSize-1)/blockSize;

    convolution_1D<<<gridSize,blockSize>>>(d_N,d_M,d_P,mask_width,width);
    cudaDeviceSynchronize();

    cudaMemcpy(h_P,d_P,width*sizeof(float),cudaMemcpyDeviceToHost);

    for(int i=0;i<width;i++)
        printf("%f ",h_P[i]);

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);
    free(h_N);
    free(h_M);
    free(h_P);
    return 0;
}
