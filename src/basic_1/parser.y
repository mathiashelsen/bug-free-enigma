%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include "basic_1.h"

%}

%union{
    struct ast *a;
    double d;
}

%token <d> NUMBER
%token EOL

%type <a> exp term

%%

calclist:
    | calclist exp EOL {
        eval($2);
        treefree($2);
        printf("> ");
        }
    | calclist EOL {
        printf("> ");
        }
    ;

exp: term 
    | exp '+' term { $$ = newast('+', $1, $3); }
    | exp '-' term { $$ = newast('-', $1, $3); }
    ;

term: NUMBER        { $$ = newnum($1); }
    | '|' term      { $$ = newast('|', $2, NULL); }
    | '(' exp ')'   { $$ = $2; }
    | '-' term      { $$ = newast('M', $2, NULL); }
    ;

%%
