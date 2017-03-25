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
"("     { return OP; }
")"     { return CP; }
[ \t]   { }
.       { printf("ERROR ERROR ERROR\n"); }
%%

