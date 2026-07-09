#include<stdio.h>
#include<string.h>
int main()
{
    char str[20][20],a[20];
    int i,j,n;
    printf("Enter no. of names\n");
    scanf("%d",&n);
    printf("Enter names in any order\n");
    for(i=0;i<len;i++)
    {
        scanf("%s", &str[i]);
    }
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-;j++)
        {
            if(strcmp(str[i],str[j])>0)
            {
                strcpy(a,str[i]);
                strcpy(str[i],sr[j]);
                strcpy(str[i],a);
            }
        }
    }
            printf("the sorted order of names are\n");
            for(i=0;i<n;i++)
            {
                printf("%s",str[i]);
            }
            return 0;
}
