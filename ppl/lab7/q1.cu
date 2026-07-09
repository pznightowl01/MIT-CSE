//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) Write a program in CUDA to count the number of times a given word is repeated in a sentence. (Use Atomic function)

#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__global__ void wc_kernel(char* str, char* key, int str_len, int key_len, int* w_in, int wc, int* rs) {
    int idx=threadIdx.x+blockIdx.x*blockDim.x;

    if (idx>=wc)
    	return;

    int si=w_in[idx];
    int ei=(idx+1<wc) ? w_in[idx+1] : str_len;
    
    bool is_eq=true;
    int i1=si, i2=0;

    while (i1<ei && i2<key_len) {
        if (str[i1]!=key[i2]) {
            is_eq=false;
            break;
        }
        i1++;
        i2++;
    }

    if (is_eq && i2==key_len) {
        atomicAdd(rs, 1);
    }
}

int main() {
    char str[100], key[20];
    printf("enter string: ");
    scanf("%[^\n]s", str);
    printf("enter key: ");
    scanf("%s", key);

    int str_len=strlen(str), key_len=strlen(key);

    int wc=0;
    int* w_in=(int*)malloc((str_len/2+1) * sizeof(int));  

    w_in[wc++]=0;  

    for (int i=0; i<str_len; i++) {
        if (str[i]==' ') {
            w_in[wc++]=i+1;
        }
    }

    char* d_str;
    char* d_key;
    int* d_w_in;
    int* d_rs;
    
    cudaMalloc((void**)&d_str, str_len*sizeof(char));
    cudaMalloc((void**)&d_key, key_len*sizeof(char));
    cudaMalloc((void**)&d_w_in, wc*sizeof(int));
    cudaMalloc((void**)&d_rs, sizeof(int));
    
    cudaMemcpy(d_str, str, str_len*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_key, key, key_len*sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(d_w_in, w_in, wc*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemset(d_rs, 0, sizeof(int));

    int grid_sz=(wc+256-1)/256;

    wc_kernel<<<grid_sz, 256>>>(d_str, d_key, str_len, key_len, d_w_in, wc, d_rs);
    int rs=0;
    cudaMemcpy(&rs, d_rs, sizeof(int), cudaMemcpyDeviceToHost);

    printf("input string: %s\n", str);
    printf("key: %s\n", key);
    printf("total occurrences of '%s': %d\n", key, rs);

    cudaFree(d_str);
    cudaFree(d_key);
    cudaFree(d_w_in);
    cudaFree(d_rs);
    free(w_in);
    return 0;
}
