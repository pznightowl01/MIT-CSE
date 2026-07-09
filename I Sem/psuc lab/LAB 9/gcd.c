#include<stdio.h>
int GCD(int x,int y)
{
 if(y==0)
 return x;
 else if (x>=y&&y>0)
 return(GCD(y,x%y));
}
void main()
{
 int a,b,gcd,temp;
 printf("enter two numbers:");
 scanf("%d%d",&a,&b);
 if(b>a)
 {
 temp=b;
 b=a;
 a=temp;
 }
 printf("gcd of %d and %d is %d",a,b,GCD(a,b));
}

