#include <stdio.h>
 int fact(int num)
 {
 int i,fact;
 fact=1;
 for(i=1;i<=num;i++)
 {
 fact=fact*i;
 }
 return(fact);
 }
 int main()
 {
 int n,m,r,result;
 printf("Enter the number \n");
 scanf("%d",&n);
 printf("\n The factorial of %d is %d\n",n,fact(n));
 printf("Enter the number of terms\n");
 scanf("%d",&m);
 printf("\nEnter the index\n");
 scanf("%d",&r);
 if(r>n)
 printf("Enter a valid input");
 else
 {
 result=fact(m)/(fact(r)*fact(m-r));
 printf("\nThe combinations possible are %d",result);
 }

 return 0;
}
