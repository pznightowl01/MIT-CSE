#include<stdio.h>
#include<string.h>
void main()
{
    char a[50];
    int count=0,i;
    printf("Enter the string:\n");
    scanf("%s",&a);
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]==''&& a[i+1]!='')
            count++
    }
    printf("Number of words given in the string is: %d\n",count+1);
}

