y.tab.c y.tab.h: yaccparser.y
	yacc -d yaccparser.y

lex.yy.c: lexanalyser.lex y.tab.h
	lex lexanalyser.lex

yaccparser: lex.yy.c y.tab.c y.tab.h
	g++ y.tab.c lex.yy.c -lfl -o yaccparser


lex.o: lex.cpp lex.hpp lex.h
	g++ -c lex.cpp lex.h lex.hpp -w

parser.o: parser.cpp parser.hpp
	g++ -c parser.cpp parser.hpp -w

parser: lex.o parser.o
	g++ lex.o parser.o -o parser -w