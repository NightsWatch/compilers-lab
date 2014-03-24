%{

#include <iostream>	

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
	| FOR LP id EQUALS expr SEMI expr SEMI expr RP LFP stmnts RFP
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
	termp expr''
	;
termp:
	term expr'
	;
expr':
	| PLUS term expr'
	| MINUS term expr'
	;
term:
	factor term'
	;
term':
	| TIMES factor term'
	| DIVIDE factor term'
	;
factor:
	id_or_data
	| LP expr RP
	;
expr'':
	| LESSTHAN termp expr''
	| GREATERTHAN termp expr''
	| EQUALTO termp expr''
	;



