#include <stdio.h>
#include <string.h>

void main() {
    char s1[50], s2[50];
    int i, j, ind, flag = 0;
    
    // Input first string
    printf("Enter string 1: ");
    scanf("%s", s1);
    
    // Input second string
    printf("Enter string 2: ");
    scanf("%s", s2);
    
    // Loop to find substring
    for (i = 0; i < strlen(s1) - strlen(s2) + 1; i++) {
        // Iterate through characters of the second string
        for (ind = 0; ind < strlen(s2); ind++) {
            // Check if characters match
            if (s2[ind] != s1[i + ind])
                break; // If characters don't match, break the loop
        }
        // If inner loop completes without breaking, it means a match was found
        if (ind == strlen(s2))
            break; // Break the outer loop as well
    }
    
    // Output results
    if (ind == strlen(s2))
        printf("Substring is at index %d.\nCount : %d\n", i, i + ind);
    else
        printf("String 1 does not contain substring 2.\nCount : %d\n", i);
}


Time Complexity Analysis:

- Let `n` be the length of the first string `s1` and `m` be the length of the second string `s2`.
- The outer loop iterates `n - m + 1` times, where `n - m + 1` represents the number of possible starting positions of `s2` within `s1`.

- Inside the outer loop, the inner loop iterates at most `m` times, comparing characters of `s1` and `s2`.

- Therefore, the overall time complexity of this algorithm is O(n * m), where `n` is the length of the first string and `m` is the length of the second string.