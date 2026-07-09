// Name : Princita Zina Miranda
// Section : SCE-C
// Reg No. : 220905115 (Roll No. 17)

// Write a C program to discard preprocessor directives from the given input 'C' file

#include <stdio.h>
#include <stdlib.h>
#define Pi 3

int main() {
	FILE *fi, *fo;
	int c;
	fi = fopen("q2.c", "r");
	if (fi == NULL) {
		printf("Cannot open file \n");
		exit(0); 
	}
	fo = fopen("q2out.c", "w");
	c = getc(fi);
	while (c != EOF) {
		if(c =='\"') {
			putc(c, fo);
			c = getc(fi);
			putc(c, fo);
			while(c != '\"') {
				c = getc(fi);
				putc(c, fo);
			}
		}
		else if(c == '#') {
			while(c != '\n')
				c = getc(fi);
		}
		else putc(c, fo);
		c = getc(fi);
	}
	fclose(fi);
	fclose(fo);
	return 0;
}
