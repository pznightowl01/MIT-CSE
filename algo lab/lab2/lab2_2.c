#include <stdio.h>
#include <math.h>

// Function to check if a number is prime
int isPrime(int n, int *opCount) {
    int i;
    for (i = 2; i <= sqrt(n); i++) { // Loop until square root of n
        (*opCount)++; // Counting the number of operations
        if (n % i == 0) // If divisible, it's not prime
            return 0;
    }
    return 1; // If not divisible, it's prime
}

void main() {
    int gcd = 1, n1, n2, i = 2, x, y, opCount = 0;
    
    // Input the two numbers
    printf("Enter the 2 numbers ");
    scanf("%d %d", &n1, &n2);
    
    // Determine the smaller and larger numbers
    x = n1 < n2 ? n1 : n2;
    y = n1 > n2 ? n1 : n2;
    
    // Loop until i reaches x
    do {
        opCount++;
        if ((x % i == 0) && (y % i == 0)) { // If i divides both x and y
            if (isPrime(i, &opCount)) { // Check if i is prime
                x = x / i;
                y = y / i;
                gcd *= i; // Update gcd
                i--; // Decrement i to re-check if it divides the updated x and y
            }
        }
        i++;
    } while (i <= x); // Loop until i is less than or equal to x
    
    // Output the GCD and the operation count
    printf("The GCD of %d and %d is : %d\nOpCount is %d\n", n1, n2, gcd, opCount);
}

Time Complexity Analysis:

- The time complexity of this algorithm depends on the input numbers n1 and n2.

- In the worst-case scenario, where both numbers are large and have a large common divisor, the loop iterates up to the smaller of the two numbers (x).

- Inside the loop, the `isPrime()` function is called for each number from 2 to sqrt(x). The `isPrime()` function itself has a time complexity of O(sqrt(n)).

- Therefore, the overall time complexity of this algorithm is O(sqrt(min(n1, n2))).