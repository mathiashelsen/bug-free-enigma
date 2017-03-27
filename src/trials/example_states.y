%{
    #include <stdio.h>
%}

/* Declaring the tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token OP CP
%token EOL

%%

calclist: EOL
    | calclist EOL
    | calclist exp EOL { printf(" = %d\n", $2); }
    ;

exp: factor
    | exp ADD factor { $$ = $1 + $3; }
    | exp SUB factor { $$ = $1 - $3; }
    ;

factor: term
    | factor MUL term { $$ = $1*$3; }
    | factor DIV term { $$ = $1/$3; }
    ;

term: NUMBER
    | ABS term { $$ = $2 >= 0 ? $2 : -$2; }
    | OP exp CP    { $$ = $2; }
    ;

%%

int main(void)
{
    yyparse();
    return 0;
} 

yyerror(char *s)
{
    fprintf(stderr, "ERROR: %s\n", s);
}
