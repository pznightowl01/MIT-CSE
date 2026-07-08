%{
#include "q3.tab.h"
%}

%%
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
"+" { return '+'; }
"-" { return '-'; }
"*" { return '*'; }
"/" { return '/'; }
"(" { return '('; }
")" { return ')'; }
"$" { return NL; }
%%

int yywrap()
{ return 1;
}
