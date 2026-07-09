// Name : Princita Zina Miranda
// Section : SCE-C
// Reg No. : 220905115 (Roll No. 17)

// Write a C program that takes C program as input, recognizes all the keywords and prints them in uppercase

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char word[])
{
    char *kw[] = {"int", "char", "if", "else", "/**/"};

    for (int i = 0; i < 5; i++)
        if (strcmp(word, kw[i]) == 0)
            return 1;

    return 0;
}

int main()
{
    FILE *fp;
    char temp[50];
    int i = 0, c;
    int str = 0;

    fp = fopen("q3in.c", "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '"')
        {
            str = !str;
            i = 0;
            continue;
        }

        if (str)
            continue;

        if (isalpha(c))
        {
            temp[i++] = c;
        }
        else
        {
            temp[i] = '\0';
            if (isKeyword(temp))
            {
                for (int j = 0; temp[j]; j++)
                    printf("%c", toupper(temp[j]));
                printf("\n");
            }
            i = 0;
        }
    }

    fclose(fp);
    return 0;
}
