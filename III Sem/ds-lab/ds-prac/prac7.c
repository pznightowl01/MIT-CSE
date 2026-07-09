#include <stdio.h>
#include <string.h>

// Function to check if a string is a palindrome
int isPalindrome(char str[], int start, int end) {
    // Base case: if there is only one character or none
    if (start >= end) {
        return 1; // It's a palindrome
    }

    // Check if the characters at the current positions are the same
    if (str[start] != str[end]) {
        return 0; // It's not a palindrome
    }

    // Recursive case: check the remaining characters
    return isPalindrome(str, start + 1, end - 1);
}

int main() {
    char input[100];

    // Input from the user
    printf("Enter a string: ");

    // Check the return value of fgets
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1; // Return an error code
    }

    // Remove the newline character if present
    input[strcspn(input, "\n")] = '\0';

    // Check if the input string is a palindrome
    if (isPalindrome(input, 0, strlen(input) - 1)) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is not a palindrome.\n");
    }

    return 0;
}
