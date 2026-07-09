//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to perform tiled ID convolution operation on the input array N of size width using the mask array, M of size mask width, to produce the resultant array P of size width

#include <stdio.h>
#include <cuda.h>

#define N 12
#define BLOCK_SIZE 4

__global__ void Scan(int *d_in, int *d_out, int *d_blockSums, int n) {
    __shared__ int temp[BLOCK_SIZE];

    int tid = threadIdx.x;
    int gid = blockIdx.x * blockDim.x + tid;

    temp[tid] = (gid < n) ? d_in[gid] : 0;
    __syncthreads();

    for (int offset = 1; offset < BLOCK_SIZE; offset *= 2) {
        int val = 0;
        if (tid >= offset)
            val = temp[tid - offset];
        __syncthreads();
        temp[tid] += val;
        __syncthreads();
    }

    if (tid == BLOCK_SIZE - 1)
        d_blockSums[blockIdx.x] = temp[tid];

    if (gid < n)
        d_out[gid] = temp[tid];
}

__global__ void addBlockOffsets(int *d_out, int *d_blockSums, int n) {
    int gid = blockIdx.x * blockDim.x + threadIdx.x;

    if (gid < n && blockIdx.x > 0) {
        int offset = 0;
        for (int i = 0; i < blockIdx.x; i++)
            offset += d_blockSums[i];
        d_out[gid] += offset;
    }
}

int main() {
    int h_in[N] = {1, 2, 3, 4, 1, 1, 1, 1, 2, 2, 2, 2};
    int h_out[N];

    int *d_in, *d_out, *d_blockSums;
    int numBlocks = (N + BLOCK_SIZE - 1) / BLOCK_SIZE;

    cudaMalloc(&d_in, N * sizeof(int));
    cudaMalloc(&d_out, N * sizeof(int));
    cudaMalloc(&d_blockSums, numBlocks * sizeof(int));

    cudaMemcpy(d_in, h_in, N * sizeof(int), cudaMemcpyHostToDevice);

    Scan<<<numBlocks, BLOCK_SIZE>>>(d_in, d_out, d_blockSums, N);
    addBlockOffsets<<<numBlocks, BLOCK_SIZE>>>(d_out, d_blockSums, N);

    cudaMemcpy(h_out, d_out, N * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Prefix Sum: ");
    for (int i = 0; i < N; i++)
        printf("%d ", h_out[i]);
    printf("\n");

    cudaFree(d_in);
    cudaFree(d_out);
    cudaFree(d_blockSums);

    return 0;
}
