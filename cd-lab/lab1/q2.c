//Name : Princita Zina Miranda
//Section : SCE-C
//reg no. 220905115 (roll no. 17)

//To reverse the file contents and store in another file.
//Also, display the size of the file using file handling function.

#include <stdio.h>
#include <stdlib.h>
int main(){
	FILE *fptr1, *fptr2;
	char filename[100], r_filename[100], c;
	long f_size;

	printf("Name : Princita Zina Miranda");
	printf("\nSection : SCE-C");
	printf("\nreg no. 220905115 (roll no. 17)\n");

	printf("\nEnter the filename to open for reading: \n");
	scanf("%s", filename);

	printf("Enter filename for reversed content: ");
	scanf("%s", r_filename);

	fptr1 = fopen(filename, "r");
	if (fptr1 == NULL){
		printf("Cannot open file %s \n", filename);
		exit(0);
		}

	fseek(fptr1, 0, SEEK_END);
	f_size=ftell(fptr1);
	rewind(fptr1);

	fptr2 = fopen(r_filename,"w");
	if (fptr2 == NULL){
    		printf("Cannot open file %s \n", filename);
    		fclose(fptr1);
    		return 0;
		}

	for(int i=f_size-1; i>=0; i--){
        	fseek(fptr1, i, SEEK_SET);
        	c = fgetc(fptr1);
        	fputc(c, fptr2);
    		}

	fclose(fptr1);
Name : Princita Zina Miranda, Section : SCE-C, Reg no. 220905115 (roll no. 17)

	fclose(fptr2);
	printf("reversed file saved as %s\n",r_filename);
	return 0;
}
