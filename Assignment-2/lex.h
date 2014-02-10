/*	Delimiters	*/
#define EOI		0	/* End of input			*/
#define SEMI	1	/* ; 				*/
#define LP		2	/* (				*/
#define RP		3	/* )				*/
#define LSB		26
#define RSB		27


#define LESSTHAN	4
#define GREATERTHAN	5
#define EQUALTO 6
#define LEQ	7
#define GEQ	8
#define DEQUAL	9

#define IF 10
#define ELSE 11
#define WHILE 12
#define FOR	13


#define INT  14
#define FLOAT	15
#define CHAR 	16
#define DOUBLE	17

/*	Operators	*/
#define MINUS 18
#define DIV 19
#define PLUS	20 /* + 				*/
#define TIMES	21	/* * 				*/

/*	ID	*/
#define NUM	22
#define ID	23

#define LFP	24
#define RFP	25

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;
