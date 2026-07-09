// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//Convert uppercase characters to lowercase characters of C file excluding the characters present in the comment.

%{
#include<stdio.h>
FILE *in,*out;
%}

%%
[A-Z] {fputc(yytext[0]+32,out);}
\/\/.*|\/\*([^*]|\*+[^*/])*\*\/ {fputs(yytext,out);}
(.|\n) {fputs(yytext,out);}
%%

int yywrap(){
    return 1;
}

int main(){
    in=fopen("in.c","r");
    yyin=in;
    out=fopen("out2.c","w");
    yylex();
    yywrap();
    fclose(in);
    fclose(out);
}
