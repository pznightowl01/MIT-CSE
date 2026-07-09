//Name : Princita Zina Miranda
//Section : SCE-C
//reg no. 220905115 (roll no. 17)

// to count the no. of lines and characters in a file

#include <stdio.h>
#include <stdlib.h>
int main(){
FILE *fptr;
char filename[100], c;
int line_cnt=0, char_cnt=0;

printf("Name : Princita Zina Miranda");
printf("\nSection : SCE-C");
printf("\nreg no. 220905115 (roll no. 17)\n");

printf("\nEnter the filename to open for reading: \n");
scanf("%s", filename);
fptr = fopen(filename, "r");

while ((c = fgetc(fptr))!= EOF){
char_cnt++;
if(c=='\n'){
line_cnt++;
}
}
printf("\nno. of lines in file is: %d\n", line_cnt);
printf("\nno. of characters in file is: %d\n", char_cnt);
fclose(fptr);
return 0;
}
