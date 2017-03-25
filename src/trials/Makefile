example1_3: example_1_3.l example_1_3.y
	bison -d example_1_3.y
	flex example_1_3.l
	gcc -o $@ example_1_3.tab.c lex.yy.c -lfl
