y.tab.c y.tab.h: yaccparser.y
	yacc -d yaccparser.y

lex.yy.c: lexanalyser.lex y.tab.h
	lex lexanalyser.lex

yaccparser: lex.yy.c y.tab.c y.tab.h
	g++ y.tab.c lex.yy.c -lfl -o yaccparser