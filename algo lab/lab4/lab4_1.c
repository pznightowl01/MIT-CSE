#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Recursive function to generate all permutations of array indices
void permute(int arr[], int n, float **mat, int l, int r, float *minCost, int res[], int *opCount) {
    // Base case: If current permutation is complete
    if (l == r) {
        // Calculate the cost of the current permutation
        float tempCost = 0;
        for (int i = 0; i < n; i++)
            tempCost += mat[i][arr[i]]; // Accumulate the cost
        *opCount += n + 1; // Count the number of operations
        // Update minimum cost if the current permutation has lower cost
        if (*minCost > tempCost) {
            *minCost = tempCost;
            // Store the current permutation as the result
            for (int i = 0; i < n; i++)
                res[i] = arr[i];
            *opCount += n; // Count the number of operations
        }                                                                                  
    } else {
        // Recursive case: Generate permutations by swapping elements
        for (int i = l; i <= r; i++) {
            swap(&arr[l], &arr[i]); // Swap elements
            permute(arr, n, mat, l + 1, r, minCost, res, opCount); // Recur for the next index
            swap(&arr[l], &arr[i]); // Restore the array to its original state
        }
    }
}

int main() {
    int n, opCount = 0;
    printf("Enter the number of persons and jobs: ");
    scanf("%d", &n);

    // Allocate memory for the cost matrix
    float **mat = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++)
        mat[i] = (float *)malloc(n * sizeof(float));

    // Input efficiencies of persons for jobs
    printf("Enter efficiencies of persons for jobs:\n");
    for (int i = 0; i < n; i++) {
        printf("Person %d:\n", i + 1);
        for (int j = 0; j < n; j++) {
            printf("Job %d: ", j + 1);
            scanf("%f", &mat[i][j]);
        }
    }

    float minCost = 1e9f; // Initialize minimum cost to a large value
    int *res = (int *)malloc(n * sizeof(int)); // Array to store the result
    int *arrForPerm = (int *)malloc(n * sizeof(int)); // Array for generating permutations
    for (int i = 0; i < n; i++)
        arrForPerm[i] = i; // Initialize array for permutations

    // Generate all permutations and find the minimum cost assignment
    permute(arrForPerm, n, mat, 0, n - 1, &minCost, res, &opCount);

    // Output the minimum cost and the assignment
    printf("\nMinimum Cost: %.2f\n", minCost);
    printf("Assignment:\n");
    for (int i = 0; i < n; i++)
        printf("Person %d -> Job %d\n", i + 1, res[i] + 1);

    // Output total operations performed
    printf("Total operations: %d\n", opCount);

    // Free dynamically allocated memory
    free(res);
    free(arrForPerm);
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);

    return 0;
}


Time Complexity Analysis:

- Let `n` be the number of persons (or jobs), and let's denote it as the size of the problem.

- The number of permutations of `n` elements is `n!` (n factorial).

- The algorithm generates all permutations of indices (which represent job assignments) and calculates the cost for each permutation.
- The time complexity of generating all permutations using backtracking is O(n!).

- For each permutation, it calculates the total cost, which requires O(n) operations.

- Therefore, the overall time complexity is O(n! * n), which is dominated by the factorial term.