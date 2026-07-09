#include<string.h>
struct employes
{
 int empno;
 char name[50];
 int age;
 int salary;
 int doj;
};
void main()
{
 printf("enter name of employee:\n");
 gets(e1.name);
 printf("enter employee number, age, salary, date of joining:\n");
 scanf("%d %d %d %d",&e1.empno,&e1.age,&e1.salary,&e1.doj);
 printf("retirement year of employee is %d\n",e1.doj+55-e1.age);
 int sum=1.2*e1.salary;
 int power=55-e1.age;
 printf("retirement salary is %d",pow(sum,power));
}
