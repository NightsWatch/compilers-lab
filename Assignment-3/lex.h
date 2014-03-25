/*	Delimiters	*/
#define EOI		"eoi"
	/* End of input			*/
#define SEMI	"SEMI"	/* ; 				*/
#define LP		"LP"	/* (				*/
#define RP		"RP"	/* )				*/
//#define LSB		26
//#define RSB		27




#define COMPOPER "compoper"


/*	Operators	*/
#define OPERATOR "operator"	/* * 				*/
#define DATA_TYPE "DATE_TYPE"
#define EQUALS "EQUALS"
#define CHAR 	"char"
#define FLOAT "float"
/*	ID	*/
#define NUM	"num"
#define ID	"id"
#define  CONTINUE "CONTINUE"
#define BREAK "BREAK"
#define RETURN "RETURN"
#define IF "IF"
#define ELSE "ELSE"
#define WHILE "WHILE"
#define FOR "FOR"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define TIMES "TIMES"
#define KEYWORD "keyword"
#define LESSTHAN "LESSTHAN"
#define GREATERTHAN "GREATERTHAN"
#define EQUALTO "EQUALTO"
#define COMMA "COMMA"
#define VOID "VOID"
#define LFP	"LFP"
#define RFP	"RFP"
#define DIVIDE "DIVIDE"

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;
