/* Lexical analyser for a sample c like language. */

%{
	#include <math.h>
%}

DIGIT	[0-9]
ID 	[a-zA-Z][a-zA-Z0-9_]*

%%
{DIGIT}+			{
					printf("int\t%d\n",atoi(yytext));
				}
{DIGIT}+"."{DIGIT}*				{
							printf("float\t%g\n",atof(yytext));
						}
if|else|while|for|int|float|char|double		{
							printf("keyword\t%s\n",yytext);
						}
{ID}				{
					printf("id\t%s\n",yytext);
				}
"+"|"-"|"*"|"/"|"="			printf("operator\t%s\n",yytext);
"//"[^\n]*			/* eat up one line comments	*/
[^ \t\n]+			/* eat up white space */
.				printf("Invalido\n");	/* All other default erroneous characters */
%%

int main() {
	yylex();
	return 0;
}

/* Code for identifying and ignoring block comments to be added. It's a bit tricky.. */
