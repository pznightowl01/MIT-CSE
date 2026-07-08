// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//That changes a number from decimal to hexadecimal notation.

%{
int num = 0;
%}

%%

[0-9]+ { num = atoi(yytext); }

%%

int main(){
    yylex();
    printf("hexadecimal no. is %X\n",num);
}

int yywrap(){
    return 1;
} 
