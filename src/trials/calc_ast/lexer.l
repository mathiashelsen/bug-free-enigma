%option noyywrap nodefault yylineno
%{
    #include "calc_ast.h"
    #include "parser.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

"+" |
"-" |
"*" | 
"/" |
"(" |
")" { return yytext[0]; }
[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}? { yylval.d = atof(yytext); return NUMBER; }
\n { return EOL; }
"//".*
[ \t] {}
. { yyerror("Mystery character %c\n", *yytext); }
%%
