%{
    #include <stdio.h>

    struct node{
        int result;
        struct node *previous;
    };

    int stackDepth;
    struct node *curNode;

    void addNode(int _result);
    void deleteTree(struct node *np);
    int getNodeValue(int index);
%}

/* Declaring the tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token REF
%token OP CP
%token EOL

%%

calclist:
    | calclist exp EOL { addNode($2); printf("[%d] = %d\n", stackDepth, $2); }
    ;

exp: factor
    | exp ADD factor { $$ = $1 + $3; }
    | exp SUB factor { $$ = $1 - $3; }
    ;

factor: term
    | factor MUL term { $$ = $1*$3; }
    | factor DIV term { $$ = $1/$3; }
    ;

term: NUMBER
    | ABS term { $$ = $2 >= 0 ? $2 : -$2; }
    | OP exp CP    { $$ = $2; }
    | REF { $$ = getNodeValue($1); }
    ;

%%

int main(void)
{
    stackDepth = 0;
    struct node *root;
    root = malloc(sizeof(struct node));
    root->previous = NULL;
    root->result = 0;
    curNode = root;

    yyparse();

    deleteTree(curNode);

    return 0;
}

int getNodeValue(int index)
{
    if(index > stackDepth)
    {
        return 0;
    } else {
        int i = stackDepth - index;
        struct node *np = curNode;
        while(i)
        {
            np = np->previous; 
            i--;
        }
        return np->result;

    }
} 

void addNode(int _result)
{
    struct node *np = malloc(sizeof(struct node));
    np->previous = curNode;
    np->result = _result;
    curNode = np;
    stackDepth++;
}

void deleteTree(struct node *np)
{
    while(np)
    {
        np = np->previous;
        free(np);
    }

}

yyerror(char *s)
{
    fprintf(stderr, "ERROR: %s\n", s);
}
