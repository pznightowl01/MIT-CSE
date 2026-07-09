#include<stdio.h>
int main()
{
    int a[50],n,i,pos;
    printf("Enter the elements to array\n");
    scanf("%d",&n);
    printf("enter %d elements\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        printf("Enter the location to delete the element\n");
        scanf("%d",&pos);
    {
        if(pos>=n+1)
        {
            printf("deletion is not possible\n");
        }
        else
        {
           for(i=pos-1;i<n-1;i++)
                a[i]=a[i+1];
                printf("the new array is\n");
                for(i=0;i<n-1;i++)
                    printf("%d\n",a[i]);
        }
    }
    }
    return 0;
}
