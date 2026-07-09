%{
	#include "q1.tab.h"
%}

%%
int {return INT; }
char {return CHAR; }
; {return SEMIC; }
[a-zA-Z][a-zA-Z0-9_]* {return ID; }
%%

int yywrap()
{ return 1;
}
