#include <stdio.h>
#idefine <xyz.h>
int main(){
char username[5]="admin"; //string initiatlization
char password[4]="1234";
char u,p; /*declaration completed*/
printf("Enter username and password:");
scanf("%S%S", u,p);
//logical AND (&&) operator
if(strcmp(u, username)==0 && (u!=p){
printf("Login successful\n");}
else if(strcmp(u, username)==0||(u>=p){
printf("Partial match\n");
}else{
printf("Login failed\n");
}return 0;}
