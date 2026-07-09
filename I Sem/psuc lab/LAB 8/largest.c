#include <stdio.h>
int largest(int a[],int);
int main()
{
 int i,j,n,a[50];
 printf("Enter the size of list\n");
 scanf("%d",&n);
 printf("Enter the list\n");
 for (i=0;i<n;i++)
 {
 scanf("%d",&a[i]);
 }
 printf("The largest element in the list is %d",largest(a,n));
 return 0;
}
int largest(int a[],int num)
{
 int large=a[0],i;
 for(i=0;i<num;i++)
 {
 if(a[i]>large)
 large=a[i];
 }
 return(large);
}
