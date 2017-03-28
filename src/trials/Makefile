example1_3: example_1_3.l example_1_3.y
	bison -d example_1_3.y
	flex example_1_3.l
	gcc -o $@ example_1_3.tab.c lex.yy.c -lfl

example_states: example_states.l example_states.y
	bison -d example_states.y
	flex example_states.l
	gcc -o $@ example_states.tab.c lex.yy.c -lfl


clc: clc.l clc.y
	bison -d clc.y
	flex clc.l
	gcc -o $@ clc.tab.c lex.yy.c -lfl
