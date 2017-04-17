#include "basic_1.h"

uint32_t stackPtr = 0;
uint32_t stackDepth = 0;

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

struct ast *newnum(int value)
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
        case 'K':   emit(ADD_NUMBER, a);
                    break;
        case '+':   v = eval(a->l) + eval(a->r);
                    break;
        case '-':   v = eval(a->l) - eval(a->r);
                    break;
        case 'M':   v = (-1)*eval(a->l);
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

void emit(enum emitType type, struct ast *data)
{
    switch(type)
    {
        case ADD_NUMBER: ;
            struct numval * ptr = (struct numval *)data;
            if( ptr->number < 2048 )
            {
                char *outStr = malloc(sizeof(char)*1024);
                memset(outStr, 0, sizeof(outStr));

                sprintf(outStr, "ADD\tR0\t%d A R1\n", stackDepth);
                printf("%s", outStr);

                memset(outStr, 0, sizeof(outStr));
                sprintf(outStr, "MOV\tR0\t%d N R0\n", stackDepth);
                printf("%s", outStr);
                printf("%s", outStr);

                memset(outStr, 0, sizeof(outStr));
                sprintf(outStr, "MOV\tR1\t%d A *R0\n", ptr->number);
                printf("%s", outStr);
               
                stackDepth++; 
                free(outStr);
            }
            else
            {
                yyerror("Error creating number, larger than IMM size in opcode! Number input: ", ptr->number); 
            }
    }
}
