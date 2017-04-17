#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>


extern int yylineno;
void yyerror(char *s, ...);

struct ast{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval{
    int nodetype;
    int number;
};

enum emitType {
    ADD_NUMBER 
};

struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(int number);

double eval(struct ast *);

void treefree(struct ast *);

void emit(enum emitType type, struct ast *data);
