//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a CUDA program that reads a string S and produces the string RS as follows:
//Input string S: PCAP Output string RS: PCAPPCAPCP
//Note: Each work item  copies required number of charact6ers from S in RS

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__global__
void kernel(char* s_in, int* si_len, char* s_out)
{
    int idx=threadIdx.x+blockIdx.x*blockDim.x;

    int si=0;
    for(int i=0; i<idx; i++)
        si+=(*si_len)-i;

    int total_chars=(*si_len)-idx;
    for(int i=0; i<total_chars; i++)
        s_out[si++]=s_in[i];
}

int main()
{
    char s_in[100], s_out[100];
    printf("input string S: ");
    scanf("%s", s_in);

    int si_len=strlen(s_in);
    int so_len=0;

    for (int i=0; i<si_len; i++)
        so_len+=(i+1);

    char* d_in;
    int* di_len;
    char* d_out;

    cudaMalloc((void**) &d_in, si_len*sizeof(char));
    cudaMalloc((void**) &di_len, sizeof(int));
    cudaMalloc((void**) &d_out, (so_len+1)*sizeof(char));

    cudaMemcpy(d_in, s_in, si_len*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(di_len, &si_len, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_out, s_out, (so_len+1)*sizeof(char), cudaMemcpyHostToDevice);

    kernel<<<1, si_len>>>(d_in, di_len, d_out);

    cudaMemcpy(s_out, d_out, (so_len+1)*sizeof(char), cudaMemcpyDeviceToHost);

    s_out[so_len]='\0';

    printf("output string RS: %s\n", s_out);

    cudaFree(d_in);
    cudaFree(di_len);
    cudaFree(d_out);

    return 0;
}
