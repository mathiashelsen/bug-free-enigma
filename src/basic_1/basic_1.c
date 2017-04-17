#include "basic_1.h"

uint32_t stackPtr = 0;
uint32_t stackDepth = 0;
FILE *fp;

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

void eval(struct ast *a)
{
    switch(a->nodetype)
    {
        case 'K':   emit(NEW_NUMBER, a);
                    break;
        case '+':   eval(a->r);
                    eval(a->l);
                    emit(ADD, NULL); 
                    break;
        case '-':   eval(a->r);
                    eval(a->l);
                    emit(SUB, NULL);
                    break;
        case 'M':   eval(a->l);
                    emit(UNITARY_MINUS, NULL);
                    break;
        default:    printf("Error: unknown nodetype in AST\n");
                    
    } 
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

int main(int argc, char **argv)
{ 
    if(argc == 1)
    {
        fp = fopen("default.ss", "w");
    } 
    else if(argc == 2)
    {
        fp = fopen(argv[1], "w"); 
    }
    else
    {
        printf("Too many arguments\n");
        return -1;
    }

    createPreamble();
    printf("> ");
    return yyparse();

    fclose(fp);
}

void emit(enum emitType type, struct ast *data)
{
    char *outStr = malloc(sizeof(char)*1024);
    switch(type)
    {
        case NEW_NUMBER: ;
            struct numval * ptr = (struct numval *)data;
            if( ptr->number < 2048 )
            {
                char *outStr = malloc(sizeof(char)*1024);
                memset(outStr, 0, sizeof(outStr));

                stackPtr++;
                stackDepth++; 

                // Increment stack pointer
                fprintf(fp, "// Incrementing stack pointer and writing value to MEM\n");
                sprintf(outStr, "ADD\tR0\t1\tA\tR0\n");
                fprintf(fp, "%s", outStr);

                // Write value to old pointer
                memset(outStr, 0, sizeof(outStr));
                sprintf(outStr, "MOV\tR0\t%d\tA\t*R0\n", ptr->number);
                fprintf(fp, "%s", outStr);

                fprintf(fp, "%s", NOPSTR);
                fprintf(fp, "%s", NOPSTR);
               
                free(outStr);
            }
            else
            {
                yyerror("Error creating number, larger than IMM size in opcode! Number input: ", ptr->number); 
            }
            break;
        case ADD: ;
            // Add the two numbers that are on top of the stack
            memset(outStr, 0, sizeof(outStr));

            fprintf(fp, "// Signed add of top two numbers from stack\n");
            sprintf(outStr, "SUB\tR0\t1\tA\tR1\n");
            fprintf(fp, "%s", outStr);
            fprintf(fp, "%s", NOPSTR);
            fprintf(fp, "%s", NOPSTR);
            
            memset(outStr, 0, sizeof(outStr));
            sprintf(outStr, "ADDS\t*R0\t*R1\tA\tR1\n");
            fprintf(fp, "%s", outStr);
            memset(outStr, 0, sizeof(outStr));
            sprintf(outStr, "MOV\tR1\tR1\tA\tR0\n");
            fprintf(fp, "%s", outStr);
            fprintf(fp, "%s", NOPSTR);
            fprintf(fp, "%s", NOPSTR);

            stackPtr--;
            stackDepth--;

            break;
        case SUB: ;
            // Add the two numbers that are on top of the stack
            memset(outStr, 0, sizeof(outStr));

            fprintf(fp, "// Signed add of top two numbers from stack\n");
            sprintf(outStr, "SUB\tR0\t1\tA\tR1\n");
            fprintf(fp, "%s", outStr);
            fprintf(fp, "%s", NOPSTR);
            fprintf(fp, "%s", NOPSTR);
            
            memset(outStr, 0, sizeof(outStr));
            sprintf(outStr, "SUBS\t*R0\t*R1\tA\tR1\n");
            fprintf(fp, "%s", outStr);
            memset(outStr, 0, sizeof(outStr));
            sprintf(outStr, "MOV\tR1\tR1\tA\tR0\n");
            fprintf(fp, "%s", outStr);
            fprintf(fp, "%s", NOPSTR);
            fprintf(fp, "%s", NOPSTR);

            stackPtr--;
            stackDepth--;

            break;
        case UNITARY_MINUS: ;
            memset(outStr, 0, sizeof(outStr));

            fprintf(fp, "// Unitary minus on last number of stack\n");
            sprintf(outStr, "MOV\tR0\t0\tA\tR10\n");
            fprintf(fp, "%s", outStr);
            fprintf(fp, "%s", NOPSTR);
            fprintf(fp, "%s", NOPSTR);

            memset(outStr, 0, sizeof(outStr));
            sprintf(outStr, "SUBS\tR10\t*R0\tA\t*R0\n");
            fprintf(fp, "%s", outStr);
            fprintf(fp, "%s", NOPSTR);
            fprintf(fp, "%s", NOPSTR);
            break;
    }
    free(outStr);
}

void createPreamble()
{
    // We put R0 to the initial stackPtr;
    char *outStr = malloc(sizeof(char)*1024);

    memset(outStr, 0, sizeof(outStr));
    sprintf(outStr, "MOV\tR0\t%d A R0\n", stackPtr);
    fprintf(fp, "%s", outStr);

    memset(outStr, 0, sizeof(outStr));
    sprintf(outStr, "MOV\tR0\t%d N R0\n", stackPtr);
    fprintf(fp, "%s", outStr);
    fprintf(fp, "%s", outStr);
    
}
