%{
    #include "example_1_3.tab.h"
%}

%%
"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"|"     { return ABS; }
\n      { return EOL; }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
[ \t]   { }
.       { printf("ERROR ERROR ERROR\n"); }
%%

