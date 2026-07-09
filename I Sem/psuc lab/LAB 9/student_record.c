#include<stdio.h>
struct student_record
{
 int rollno,m1,m2,m3;
 float mavg;
 char name[100];
};
int main()
{
 int i,j,k;
 struct student_record temp,test[3];
 printf("enter the value\n");
 for(i=0;i<3;i++)
 {
 printf("enter then name:");
 scanf("%s",test[i].name);
 printf("enter roll number:");
 scanf("%d",&test[i].rollno);
 printf("enter the marks in subject m1,m2,m3");
 scanf("%d%d%d",&test[i].m1,&test[i].m2,&test[i].m3);
 test[i].mavg=(test[i].m1+test[i].m2+test[i].m3)/3.0;
 }
 for(i=0;i<3;i++)
 {
 temp=test[i];
 k=i;
 for(j=k+1;j<3;j++)
 {
 if(temp.mavg>test[i].mavg)
 {
 temp=test[i];
 k=j;
 }
 }
 test[k]=test[i];
 test[i]=temp;
 }
 for(i=0;i<3;i++)
 {
 printf("name of the student");
 puts(test[i].name);
 printf("roll number of student is %d\n",test[i].rollno);
 printf("marks of student in subject m1,m2,m3 are %d %d %d\n",test[i].m1,test[i].m2,test[i].m3);
 printf("\n");
 }
 return 0;
}
