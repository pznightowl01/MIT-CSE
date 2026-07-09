// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//Given a input C file, replace all scanf with READ and printf with WRITE statements also find the number of scanf and printf in the file.

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

%{
#include <stdio.h>
int sf = 0;
int pf = 0;
%}

%%
"scanf" { sf++; fwrite("READ", 1, 4, yyout); }
"printf" { pf++; fwrite("WRITE", 1, 5, yyout); }
[ \t\n]   ;
. { fwrite(yytext, 1, yyleng, yyout); }

%%

int main(int argc, char **argv) {
    yyin = fopen("in.c", "r");
    yyout = fopen("out1.c", "w+");
    yylex();
    printf("Number of scanfs are %d\nand printfs are %d\n", sf, pf);
    return 0;
}

int yywrap() {
    return 1;
}
