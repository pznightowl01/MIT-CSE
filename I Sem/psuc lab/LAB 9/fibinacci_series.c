#include<stdio.h>
int FIB(int n)
{
 if(n<=1)
 return n;
 else
 return(FIB(n-1)+FIB(n-2));
}
void main()
{
 int i,n,fib,a[20];
 printf("enter number of fibonacci numbers you need:");
 scanf("%d",&n);
 printf("fibonacci series is:");
 for(i=1;i<=n;i++)
 {
 printf("%d",FIB(i));
 }
}

