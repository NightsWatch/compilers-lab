#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define ID	6	/* Decimal Number or Identifier */
#define MINUS 9
#define DIV 10
#define NUM	19
//#define SPACE 20

#define LESSTHAN	7
#define GREATERTHAN	8
#define EQUALTO 11

#define COLE 12
#define IF 13
#define THEN 14
#define WHILE 15
#define DO 16
#define BEGIN 17
#define END 18

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern yylineno;
