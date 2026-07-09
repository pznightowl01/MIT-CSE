//Name : Princita Zina Miranda
//Section : SCE-C
//reg no. 220905115 (roll no. 17)

//Program to remove single and multiline comments from a given ‘C’ file.

//This is a single line comment
/* *****This is a
******Multiline Comment
**** */


#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fa, *fb;
	int ca, cb;
	fa = fopen("sol.c", "r");
	if (fa == NULL){
		printf("Cannot open file \n");
		exit(0); }
		fb = fopen("solout.c", "w");
		ca = getc(fa);
		while (ca != EOF){
			if(ca==' '){
				putc(ca,fb);
				while(ca==' ')
				ca = getc(fa);
				}
			if (ca=='/'){
				cb = getc(fa);
				if (cb == '/'){
					while(ca != '\n')
					ca = getc(fa);
					}
				else if (cb == '*'){
					do{
						while(ca != '*')
						ca = getc(fa);
						ca = getc(fa);
						} 
					while (ca != '/');
					}
				else{
					putc(ca,fb);
					putc(cb,fb);
				}
			}
			else putc(ca,fb);
			ca = getc(fa);
		}
	fclose(fa);
	fclose(fb);
	return 0;
	}
