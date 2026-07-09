// Name : Princita Zina Miranda
// Section : SCE-C
// Reg No. : 220905115 (Roll No. 17)

// Write a C program that takes a file as input and replaces blank spaces and tabs by single space and writes the output to a file.

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fa, *fb;
    int ch;
    int sp = 0;

    fa = fopen("q1.c", "r");
    if (fa == NULL) {
        printf("Cannot open input file\n");
        exit(1);
    }

    fb = fopen("q1out.c", "w");
    if (fb == NULL) {
        printf("Cannot open output file\n");
        fclose(fa);
        exit(1);
    }

    while ((ch = getc(fa)) != EOF) {
        if (ch == ' ' || ch == '\t') {
            if (!sp) {
                putc(' ', fb);
                sp = 1;
            }
        } else {
            putc(ch, fb);
            sp = 0;
        }
    }

    fclose(fa);
    fclose(fb);
    return 0;
}
