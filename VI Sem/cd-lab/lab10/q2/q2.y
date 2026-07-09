%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
%}

%token IF ELSE NUMBER IDENTIFIER ASSIGN EQUALS NL

%%
program : ifstmt NL {printf("Valid Expression\n"); exit(0);}

ifstmt : IF '(' condition ')' '{' statements '}' ELSE '{' statements '}' | IF '(' condition ')' '{' statements '}';

condition : NUMBER | IDENTIFIER '<' NUMBER | NUMBER EQUALS NUMBER;

statements: statement | statements statement;

statement : IDENTIFIER ASSIGN expression ';';

expression: NUMBER | IDENTIFIER | expression '+' expression;
%%

int yyerror(char *msg)
{
printf("Invalid Expression\n");
exit(0);
}

void main ()
{
printf("Enter the expression\n");
yyparse();
}
