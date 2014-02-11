/*	Delimiters	*/
#define EOI		"eoi"
	/* End of input			*/
#define SEMI	"semi"	/* ; 				*/
#define LP		"lp"	/* (				*/
#define RP		"rp"	/* )				*/
//#define LSB		26
//#define RSB		27




#define COMPOPER "compoper"


/*	Operators	*/
#define OPERATOR "operator"	/* * 				*/

#define CHAR 	"char"
#define FLOAT "float"
/*	ID	*/
#define NUM	"num"
#define ID	"id"

#define KEYWORD "keyword"


#define LFP	"lfp"
#define RFP	"rfp"

extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;
