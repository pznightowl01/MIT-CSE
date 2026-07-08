// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//Find the number of positive integer, negative integer, positive floating positive number and negative floating point number

%{
#include <stdio.h>
int pos = 0;
int neg = 0;
int fpos = 0;
int fneg = 0;
%}

%%

"-"[0-9]+\.[0-9]+ { fneg++; }
"-"[0-9]+ { neg++; }
[+]?[0-9]+\.[0-9]+ { pos++; }
[+]?[0-9]+ { fpos++; }

%%

int main(){
yylex();
printf("positive integer: %d\nnegative integer: %d\nfloat positive integer: %d\nfloat negative integer: %d\n", pos, neg, fpos, fneg); }
int yywrap()
{
return 1;
}
