#include<stdio.h>
int CornerSum(int r,int c,int arr[50][50])
{
 int sum;
 sum=arr[0][0]+arr[0][c-1]+arr[r-1][0]+arr[r-1][c-1];
 return (sum);
}
int main()
{
 int i,j,rows,cols;
 int arr[50][50];
 printf("Enter the number of rows\n");
 scanf("%d",&rows);
 printf("Enter the number of columns\n");
 scanf("%d",&cols);
 printf("Enter the matrix\n");
 for(i=0;i<rows;i++)
 {
 for(j=0;j<cols;j++)
 {
 scanf("%d",&arr[i][j]);
 }
 }
 printf("The matrix is \n");
 for(i=0;i<rows;i++)
 {
 for(j=0;j<cols;j++)
 {
 printf("%d ",arr[i][j]);
 }
 printf("\n");
 }

 printf("The sum of the corner elements is %d",CornerSum(rows,cols,arr));
 return 0;
}
