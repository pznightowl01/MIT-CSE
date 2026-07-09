//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115
 
//Q) Write a program in CUDA which displays a shopping mall item menu with its price. The N number of friends are allowed to purchase as many items they want. Calculate the total purchase done by N friends.

#include <stdio.h>
#include <cuda.h>

#define ITEMS 5
#define FRIENDS 3

__global__ void calculateTotal(int *prices, int *cart, int *totals) {
    int fid = threadIdx.x;

    int sum = 0;
    for (int i = 0; i < ITEMS; i++) {
        sum += cart[fid * ITEMS + i] * prices[i];
    }

    totals[fid] = sum;
}

int main() {
    int h_prices[ITEMS] = {10, 20, 30, 40, 50};

    int h_cart[FRIENDS * ITEMS] = {
        1, 0, 2, 1, 0,
        0, 1, 1, 0, 2,
        2, 1, 0, 1, 1
    };

    int h_totals[FRIENDS];
    int grandTotal = 0;

    int *d_prices, *d_cart, *d_totals;

    cudaMalloc(&d_prices, ITEMS * sizeof(int));
    cudaMalloc(&d_cart, FRIENDS * ITEMS * sizeof(int));
    cudaMalloc(&d_totals, FRIENDS * sizeof(int));

    cudaMemcpy(d_prices, h_prices, ITEMS * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_cart, h_cart, FRIENDS * ITEMS * sizeof(int), cudaMemcpyHostToDevice);

    calculateTotal<<<1, FRIENDS>>>(d_prices, d_cart, d_totals);

    cudaMemcpy(h_totals, d_totals, FRIENDS * sizeof(int), cudaMemcpyDeviceToHost);

    printf("Menu:\n");
    for (int i = 0; i < ITEMS; i++)
        printf("Item %d : %d\n", i + 1, h_prices[i]);

    printf("\nTotal Purchase by each friend:\n");
    for (int i = 0; i < FRIENDS; i++) {
        printf("Friend %d : %d\n", i + 1, h_totals[i]);
        grandTotal += h_totals[i];
    }

    printf("\nGrand Total: %d\n", grandTotal);

    cudaFree(d_prices);
    cudaFree(d_cart);
    cudaFree(d_totals);

    return 0;
}
