#include<stdio.h>
int prod(int x,int y)
{
 if(y==1)
 {
 return x;
 }
 else
 return x+prod(x,y-1);
}
void main()
{
 int x,y;
 printf("enter two numbers:");
 scanf("%d%d",&x,&y);
 printf("product of two numbers is %d",prod(x,y));
 return 0;
}
