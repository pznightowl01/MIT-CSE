#include <stdio.h>

void main() {
    int n1, n2, x, i, gcd, opCount = 0;
    
    // Input both numbers
    printf("Enter both numbers ");
    scanf("%d %d", &n1, &n2);
    
    // Find the minimum of the two numbers
    x = n1 < n2 ? n1 : n2;
    
    // Loop to find the Greatest Common Divisor (GCD)
    for (i = x; i >= 1; i--) {
        opCount++; // Counting the number of operations
        if (n1 % i == 0 && n2 % i == 0) { // Check if i is a common divisor
            gcd = i; // If common divisor found, store it as GCD
            break; // Break the loop since we found the GCD
        }
    }
    
    // Output the GCD and the operation count
    printf("GCD of %d and %d is %d\nOpcount is: %d\n", n1, n2, gcd, opCount);
}


Time Complexity Analysis:

- The time complexity of this algorithm is O(min(n1, n2)), where n1 and n2 are the input numbers.

- The loop iterates from the minimum of the two numbers down to 1, checking each integer if it divides both numbers evenly.

- The worst-case scenario occurs when the two input numbers are relatively prime (having no common factors other than 1), and the loop iterates until it reaches 1.

- Thus, the time complexity depends on the smaller of the two input numbers.
