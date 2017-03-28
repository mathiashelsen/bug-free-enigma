%{
    #include "clc.tab.h"
%}

%x COMMENT
%x REFERENCE

%%
"/*"    { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>([^*]|\n)+|.

"+"     { return ADD; }
"-"     { return SUB; }
"*"     { return MUL; }
"/"     { return DIV; }
"|"     { return ABS; }
\n      { return EOL; }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
"("     { return OP; }
")"     { return CP; }
"["     { BEGIN(REFERENCE); }
<REFERENCE>"]"     { BEGIN(INITIAL); }
<REFERENCE>[0-9]+ { yylval = atoi(yytext); return REF; }
[ \t]   { }
.       { printf("ERROR ERROR ERROR\n"); }
%%

