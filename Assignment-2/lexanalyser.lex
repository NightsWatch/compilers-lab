/* Lexical analyser for a sample c like language. */

%{
	#include <math.h>
%}

%Start	BL_CMNT

DIGIT	[0-9]
ID 	[a-zA-Z][a-zA-Z0-9_]*

%%
<INITIAL>"/*"													{BEGIN BL_CMNT;}
<BL_CMNT>"*/"													{BEGIN 0;}
<BL_CMNT>.														/* eat up the block comment characters */
<INITIAL>{DIGIT}+												printf("int\t\t%d\n",atoi(yytext));
<INITIAL>{DIGIT}+"."{DIGIT}*									printf("float\t\t%g\n",atof(yytext));
<INITIAL>"'"."'"												printf("char\t\t%c\n",yytext[1]);
<INITIAL>if|else|while|for|int|float|char|double|return			printf("keyword\t\t%s\n",yytext);
<INITIAL>{ID}													printf("id\t\t%s\n",yytext);
<INITIAL>"+"|"-"|"*"|"/"|"="									printf("operator\t%s\n",yytext);
<INITIAL>"<"|">"|"<="|">="|"=="									printf("compoper\t%s\n",yytext);
<INITIAL>"("|")"|"{"|"}"										printf("brace\t\t%s\n", yytext);/* Matching braces for if, for etc */
<INITIAL>";"													printf("delimiter\t%s\n",yytext);
<INITIAL>"//"[^\n]*												/* eat up one line comments	*/
<INITIAL>[ \t\n]+												/* eat up white spaces */
<INITIAL>.														printf("Invalid characters: %s\n",yytext);	/* All other erroneous characters */
%%

int main() {
	yylex();
	return 0;
}

