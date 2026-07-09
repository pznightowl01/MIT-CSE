#include<stdio.h>
int main()
{
    int a[20],n,i,j,temp;
    printf("Enter the number of elements to the array\n");
    scanf("%d",&n);
    printf("enter %d integers\n",n);
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
    {
        if(a[j]<a[j+1])
        {
            temp=a[j];
            a[j]=a[j+1];
            a[j+1]=temp;
        }
    }
    printf("After sorting, The list in ascending order is\n");
    for(i=0;i<n-1;i++)
        printf("%d\n",a[i]);
    return 0;
}
