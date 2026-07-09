#include<stdio.h>
int main()
{
    int a[20],n,i,l,s;
    printf("Enter the size of the array \t");
    scanf("%d",&n);
    printf("enter the elements of the array \t");
    for(i=0;i<n;i++)
    {
        scanf("%d", &a[i]);
    }
    l=a[i];
    for(i=0;i<n;i++)
    {
        if(l<a[i])
        {
            l=a[i];
        }
    }
    printf("the largest element in the array is %d",l);
    s=a[i];
    for(i=0;i<n;i++)
    {
        if(s>a[i])
        {
            s=a[i];
        }
    }
    printf("the smallest element in the array is %d",s);
return 0;
}
