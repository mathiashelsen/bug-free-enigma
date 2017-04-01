#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "calc_ast.h"

struct ast *newast(int nodetype, struct ast *l, struct ast *r)
{
    struct ast *a = malloc(sizeof(struct ast));

    if(!a)
    {
        yyerror("Could not allocate sufficient memory\n");
        exit(-1);
    }

    a->nodetype = nodetype;
    a->l = l;
    a->r = r;

    return a;
}

struct ast *newnum(double value)
{
    struct numval *a = malloc(sizeof(struct numval));

    if(!a)
    {
        yyerror("Could not allocate sufficient memory\n");
        exit(-1);
    }

    a->nodetype = 'K';
    a->number = value;

    return (struct ast *)a;
}

double eval(struct ast *a)
{
    double v;

    switch(a->nodetype)
    {
        case 'K':   v = ((struct numval *)a)->number;
                    break;
        case '+':   v = eval(a->l) + eval(a->r);
                    break;
        case '-':   v = eval(a->l) - eval(a->r);
                    break;
        case '*':   v = eval(a->l) * eval(a->r);
                    break;
        case '/':   v = eval(a->l) / eval(a->r);
                    break;
        case 'M':   v = (-1.0)*eval(a->l);
                    break;
        default:    printf("Error: unknown nodetype in AST\n");
                    
    } 

    return v;
}

void treefree(struct ast *a)
{
    switch(a->nodetype)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            treefree(a->r);
        case 'M':
        case '|':
            treefree(a->l);
        case 'K':
            free(a);
            break;
        default:
            printf("Bad nodetype: %c\n", a->nodetype);
    }
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

int main(void)
{   
    printf("> ");
    return yyparse();
}
