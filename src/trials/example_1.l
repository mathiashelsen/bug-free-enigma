/* WC example */

%{
    int chars = 0;
    int words = 0;
    int lines = 0;
%}

%%

[a-zA-Z]+   { words++; chars+=strlen(yytext); }
\n          { lines++; }
.           { chars++; }

%%

int main(void)
{
    yylex();
    printf("%d\t%d\t%d\n", chars, words, lines);
    return 0;
};
