#include <stdio.h>
#include<string.h>
int IsPalin(char s[200],int n)
{
 int i,j,hold;
 hold=1;
 for(i=0,j=n-1;i<=n/2;i++,j--)//NOT N-2 IT WIIL BE N-1
 {
 if(s[i]!=s[j])
 {
 printf("it is not a palindrome");
 hold=0;
 break;
 }
 }
 if(hold==1)
 printf("It is a palindrome\n");
 return (n);
}
int main()
{
 char s[200],n;
 printf("Enter the string \n");
 gets(s);
 n=strlen(s);
 printf("\nThe size of the string is %d\n",n);
 IsPalin(s,n);
 return 0;
}
