#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#define NOPSTR "MOV\tR0\t0\tN\tR0\n"


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
    NEW_NUMBER,
    ADD,
    SUB,
    UNITARY_MINUS
};

struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(int number);

void eval(struct ast *);

void treefree(struct ast *);

void emit(enum emitType type, struct ast *data);

void createPreamble();
