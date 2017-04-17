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
    UNITARY_MINUS,
    RECALL_VALUE,
    STORE_VALUE
};

struct symref{
    int nodetype;
    struct symbol *s;
};

struct symasgn {
    int nodetype;
    struct symbol *s;
    struct ast *v;
};

/* Hooray for the Symbol Table! Hooray! */
struct symbol {
    char *name;
    int value; // -> Ptr?
    struct ast *func;
    struct symlist *syms;
};

struct symlist {
    struct symbol *sym;
    struct symlist *next;
};

#define NHASH 9997
struct symbol symtab[NHASH];
struct symbol *lookup(char *);
struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);


struct ast *newast(int nodetype, struct ast *l, struct ast *r);
struct ast *newnum(int number);
struct ast *newref(struct symbol *s);
struct ast *newasgn(struct symbol *s, struct ast *v);

void eval(struct ast *);

void treefree(struct ast *);

void emit(enum emitType type, struct ast *data);

void createPreamble();
