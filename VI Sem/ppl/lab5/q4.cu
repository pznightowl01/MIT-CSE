//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

//Q) write a program in CUDA to perform linear agebra function of the form y = ax + y, where x and y are vectors and (alpha) is a scalar value

#include <stdio.h>

__global__ void axpy(float alpha, float *x, float *y, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) {
        y[idx] = alpha * x[idx] + y[idx];
    }
}

int main() {
    int n;
    float alpha;

    printf("enter vector size: ");
    scanf("%d", &n);

    printf("enter scalar alpha: ");
    scanf("%f", &alpha);

    float x[n], y[n];
    float *X, *Y;

    printf("enter vector x:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &x[i]);

    printf("enter vector y:\n");
    for (int i = 0; i < n; i++)
        scanf("%f", &y[i]);

    cudaMalloc((void**)&X, n * sizeof(float));
    cudaMalloc((void**)&Y, n * sizeof(float));

    cudaMemcpy(X, x, n * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(Y, y, n * sizeof(float), cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n + threads - 1) / threads;

    axpy<<<blocks, threads>>>(alpha, X, Y, n);

    cudaMemcpy(y, Y, n * sizeof(float), cudaMemcpyDeviceToHost);

    printf("Result vector y:\n");
    for (int i = 0; i < n; i++)
        printf("%f ", y[i]);
    printf("\n");

    cudaFree(X);
    cudaFree(Y);

    return 0;
}
