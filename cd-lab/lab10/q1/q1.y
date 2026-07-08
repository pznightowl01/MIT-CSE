%{
	#include<stdio.h>
	#include<stdlib.h>
	int yylex();
	int yyerror();
%}

%token INT CHAR SEMIC ID SPACE

%%
stmt : dt ID SEMIC {printf("Valid Expression\n"); exit(0);}
dt : INT|CHAR;
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
