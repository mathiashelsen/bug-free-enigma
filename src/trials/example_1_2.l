

%%
"+"     { printf("PLUS\n"); }
"-"     { printf("MINUS\n"); }
"/"     { printf("DIVIDE\n"); }
"*"     { printf("MULTIPLY\n"); }
[0-9]+  { printf("NUMBER %s\n", yytext); }
[ \t]   { }
\n      { printf("NEWLINE\n"); }
.       { printf("Error: could not parse %s\n", yytext); }
%%
