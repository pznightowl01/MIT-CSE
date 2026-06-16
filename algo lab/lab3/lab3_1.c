#include <stdio.h>
#include <stdlib.h>

// Function to perform bubble sort on an array and return the number of comparisons
int bubbleSort(int *a, int n) {
    int i, j, temp, count = 0;
    
    // Outer loop for passes
    for (i = 0; i < n - 1; i++) {
        // Inner loop for comparisons and swapping
        for (j = 0; j < n - i - 1; j++) {
            count++; // Counting comparisons
            if (a[j] > a[j + 1]) { // Swap if the current element is greater than the next
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    return count; // Return the total number of comparisons
}

void main() {
    int n, i, count;
    
    // Input the size of the array
    printf("Enter n: ");
    scanf("%d", &n);
    
    // Dynamically allocate memory for the array
    int *arr = (int *) malloc(n * sizeof(int));
    
    // Input array elements
    for (i = 0; i < n; i++) {
        printf("Enter arr[%d] ", i);
        scanf("%d", &arr[i]);
    }

    // Sort the array and get the number of comparisons
    count = bubbleSort(arr, n);

    // Output sorted array
    printf("Sorted array is ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    // Output time complexity (Best Case)
    printf("\nTime complexity (Best Case): O(%d)\n", n);

    // Prepare array for worst-case scenario
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    
    // Sort the array again for worst-case scenario
    count = bubbleSort(arr, n);

    // Output sorted array for worst-case scenario
    printf("Sorted array (Worst Case) is ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);

    // Output time complexity (Worst Case)
    printf("\nTime complexity (Worst Case): O(%d)\n", n * n);

    // Free dynamically allocated memory
    free(arr);
}

Time Complexity Analysis:

- Best Case: When the array is already sorted, the best-case time complexity is O(n), where n is the number of elements in the array. This is because in each pass, the algorithm only performs comparisons without any swaps.

- Worst Case: When the array is sorted in reverse order, the worst-case time complexity is O(n^2), where n is the number of elements in the array. In each pass, the algorithm performs comparisons and swaps for each element.