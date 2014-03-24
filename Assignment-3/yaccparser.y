%{

#include <iostream>	

void yyerror(char *s);
int yylex(void);

%}

%token DATA_TYPE ID EQUALS CONTINUE BREAK RETURN NUM FLOAT CHAR IF ELSE WHILE FOR PLUS TIMES LP RP LESSTHAN GREATERTHAN EQUALTO SEMI LFP RFP COMMA VOID MINUS DIVIDE 

%%

func_list:
	| func func_list  
	;
func:
	void_or_datatype ID LP arg_list RP LFP stmnts RFP
	;
void_or_datatype:
	VOID
	| DATA_TYPE
	;
arg_list:
	arg COMMA arg_list
	| arg
	;
arg: 
	DATA_TYPE ID
	;
stmnts:
	| stmnt SEMI stmnts
	;
stmnt:
	declaration SEMI
	| ID EQUALS expr SEMI
	| func_call SEMI
	| iff
	| WHILE LP expr RP LFP stmnts RFP 
	| FOR LP ID EQUALS expr SEMI expr SEMI expr RP LFP stmnts RFP
	| CONTINUE SEMI
	| BREAK SEMI
	| RETURN id_or_data SEMI
	;
iff:
	IF LP expr RP LFP stmnts RFP ell
	;
ell:
	| ELSE IF LP expr RP LFP stmnts RFP ell
	| ELSE LP expr RP LFP stmnts RFP 
	;
id_or_data:
	ID
	| num_or_char
	;
expr:
	func_call
	| eval
	;
func_call:
	ID LP arg_passed RP
	;
arg_passed:
	ID COMMA arg_passed
	| ID
	;
declaration:
	DATA_TYPE ID assign
	;
assign:
	| EQUALS expr
	;
num_or_char:
	NUM
	| FLOAT
	| CHAR
	;
eval:
	termp expr2
	;
termp:
	term expr1
	;
expr1:
	| PLUS term expr1
	| MINUS term expr1
	;
term:
	factor term1
	;
term1:
	| TIMES factor term1
	| DIVIDE factor term1
	;
factor:
	id_or_data
	| LP expr RP
	;
expr2:
	| LESSTHAN termp expr2
	| GREATERTHAN termp expr2
	| EQUALTO termp expr2
	;



%%


#include <stdio.h>
#include <iostream>

using namespace std;

// stuff from lex that yacc needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;

main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("input.txt", "r");
	
	
	yyin = myfile;

	
	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}