%{
    enum yytokentype{
        NUMBER  = 258,
        ADD     = 259,
        SUB     = 260,
        MUL     = 261,
        DIV     = 262,
        ABS     = 263,
        EOL     = 264
    };

    int yylval;
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

int main(void)
{
    int tok;
    
    while(tok = yylex())
    {
        printf("%d", tok);
        if( tok == NUMBER )
        {
            printf(" = %d", yylval);
        }
        printf("\n");
    }

    return 0;
}
