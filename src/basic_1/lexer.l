%option noyywrap nodefault yylineno
%{
    #include "basic_1.h"
    #include "parser.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"(" |
")"     { return yytext[0]; }
[0-9]+  { yylval.d = atoi(yytext); return NUMBER; }
\n      { return EOL; }
"//".*
[ \t]   {}
.       { yyerror("Mystery character %c\n", *yytext); }
%%
