calc_ast: calc_ast.c calc_ast.h lexer.l parser.y
	bison -d parser.y
	flex -o lexer.lex.c lexer.l
	gcc -g -o $@ parser.tab.c lexer.lex.c calc_ast.c

