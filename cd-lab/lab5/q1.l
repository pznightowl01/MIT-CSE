// Name : Princita Zina Miranda 
// Section : SCE-C 
// Reg No. : 220905115 (Roll No. 17)

//Count the number of vowels and consonants in the given input.

%{
#include <stdio.h>
int v = 0;
int c = 0;
%}

%%

[aeiouAEIOU] { v++; }
[a-zA-Z] { c++; }

%%

int main() {
    yylex();
    printf("Vowels are %d and consonants are %d\n", v, c);
    return 0;
}

int yywrap() {
    return 1;
}
