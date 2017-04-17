%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include "basic_1.h"

%}

%union{
    struct ast *a;
    int d;
    struct symbol *s;
    struct symlist *sl;
}

%token <d> NUMBER
%token <s> NAME
%token EOL

%type <a> exp 

%right '='
%left '+' '-'
%nonassoc '|' UMINUS

%%

calclist:
    | calclist exp EOL {
        eval($2);
        }
    | calclist EOL {
        }
    ;

exp: exp '+' exp   { $$ = newast('+', $1, $3); }
    | exp '-' exp   { $$ = newast('-', $1, $3); }
    | '(' exp ')'   { $$ = $2; }
    | NUMBER        { $$ = newnum($1); }
    | NAME          { $$ = newref($1); }
    | NAME '=' exp  { $$ = newasgn($1, $3); }
    ;

%%
