/* Lexical analyser for a sample c like language. */

%{
#include <iostream>
#include "y.tab.h"

%}

%option noyywrap

%Start	BL_CMNT

DIGIT	[0-9]
ID 	[a-zA-Z][a-zA-Z0-9_]*

%%
<INITIAL>"/*"													{BEGIN BL_CMNT;}
<BL_CMNT>"*/"													{BEGIN 0;}
<BL_CMNT>.														/* eat up the block comment characters */
<BL_CMNT>\n 													/* eat up lines in block comments */
<INITIAL>"*/"													printf("Unmatched end of comment\n");
<INITIAL>{DIGIT}+{ID}+{DIGIT}*									printf("Error:\tInvalid numbers\n");
<INITIAL>{DIGIT}+												{printf("int\t\t\t%s\n",(yytext));return NUM;}
<INITIAL>{DIGIT}+"."{DIGIT}*									{printf("float\t\t%s\n",(yytext));return FLOAT;}
<INITIAL>"'"."'"												{printf("char\t\t%c\n",yytext[1]);return CHAR;}
<INITIAL>if														{printf("keyword\t\t%s\n",yytext);return IF;}
<INITIAL>else													{printf("else\n");return ELSE;}
<INITIAL>while													{printf("while\n");return WHILE;}
<INITIAL>for													{printf("for\n");return FOR;}
<INITIAL>return													{printf("return\n");return RETURN;}
<INITIAL>break													{printf("break\n");return BREAK;}
<INITIAL>continue												{printf("continue\n");return CONTINUE;}
<INITIAL>void													{printf("void\n");return VOID;}
<INITIAL>int|float|char|double									{printf("data_type\n");return DATA_TYPE;}		
<INITIAL>{ID}													{printf("id\t\t\t%s\n",yytext);return ID;}
<INITIAL>"+"													{printf("operator\t%s\n",yytext);return PLUS;}
<INITIAL>"-"													{printf("operator\t%s\n",yytext);return MINUS;}
<INITIAL>"*"													{printf("operator\t%s\n",yytext);return TIMES;}
<INITIAL>"/"													{printf("operator\t%s\n",yytext);return DIVIDE;}
<INITIAL>"="													{printf("operator\t%s\n",yytext);return EQUALS;}
<INITIAL>"=="													{printf("compoper\t%s\n",yytext);return EQUALTO;}
<INITIAL>"<"|"<="												{printf("compoper\t%s\n",yytext);return LESSTHAN;}
<INITIAL>">"|">="												{printf("compoper\t%s\n",yytext);return GREATERTHAN;}
<INITIAL>"("													{printf("brace\t\t%s\n", yytext);return LP;}
<INITIAL>")"													{printf("brace\t\t%s\n", yytext);return RP;}
<INITIAL>"{"													{printf("brace\t\t%s\n", yytext);return LFP;}
<INITIAL>"}"													{printf("brace\t\t%s\n", yytext);return RFP;}
<INITIAL>";"													{printf("delimiter\t%s\n",yytext);return SEMI;}
<INITIAL>","													{printf("delimiter\t%s\n",yytext);return COMMA;}
<INITIAL>"//"[^\n]*												/* eat up one line comments	*/
<INITIAL>[ \t\n]+												/* eat up white spaces */
<INITIAL>.														printf("Invalid characters: %s\n",yytext);	/* All other erroneous characters */
%%