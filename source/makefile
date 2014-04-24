CC=gcc
L_NAME=rusper

$(L_NAME): y.tab.c lex.yy.c
	$(CC) -W -Wall y.tab.c lex.yy.c -lm -o $(L_NAME) -g

lex: lex.yy.c y.tab.c
	$(CC) -W -Wall lex.yy.c y.tab.c -ll -o $(L_NAME)_lex

y.tab.c: $(L_NAME).y
	yacc -d -v $(L_NAME).y

lex.yy.c: $(L_NAME).l
	lex $(L_NAME).l

clean:
	rm -f y.tab.h y.tab.c lex.yy.c y.output $(L_NAME)
	rm -f $(L_NAME)_lex
	rm -f core.*
