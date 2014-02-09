#include <stdio.h>
#include <ctype.h>
#include "lex.h"

char *yytext;    /* in lex.c     */
int yyleng;
int yylineno;

char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */


int lex (void) {
     static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */
   while(1) {
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
      }

      for(; *current; ++current){
          yytext = current;
          yyleng = 1;

          switch( *current )
          {
             case ';':
              return SEMI;
             case '+':
              return PLUS;
             case '-':
              return MINUS;
             case '*':
              return TIMES;
             case '/':
              return DIV;
             case '(':
              return LP;
             case ')':
              return RP;
            case '<':
              return LESSTHAN;
            case '>':
            return GREATERTHAN;
            case '=':
            return EQUALTO;
            case  '{':
              return LFP;
            case  '}':
              return RFP;
             case '\n':
             case '\t':
             case ' ' :
              break;
             default:

           if(!isalnum(*current))
               fprintf(stderr, "No valid token <%c>\n", *current);

            else {
                      if (*current=='i' && *(current+1)=='f' &&  (*(current+2)==' ' ) || *(current+2)=='(') {
                            //current+=3;
                          yyleng=2;

                          return IF;
                      }

                      if(*current=='f' && *(current+1)=='o' && *(current+2)=='r' && (*(current+3)=='(' || *(current+3)==' ')) {
                          yyleng=3;
                          return FOR;
                      }

                      if (*current=='w' && *(current+1)=='h' && *(current+2)=='i' && *(current+3)=='l' && *(current+4)=='e' &&  (*(current+5)==' ' || *(current+5)=='(' )) {
                          yyleng=5;
                          return WHILE;
                      }

                      if (*current=='e' && *(current+1)=='l' && *(current+2)=='s' && *(current+3)=='s' &&  (*(current+4)==' ' || *(current+4)=='(' )) 
                      {
                          yyleng=5;
                          return WHILE;
                      }

                  if( ( *current-'a'>=0 && 'z'-(*current)>=0 ) || ( *current-'A'>=0 && 'Z'-(*current)>=0 ) )
                       {
                          while(isalnum(*current))
                            ++current;
                           yyleng = current - yytext;
                          return ID;
                       }

                       if(*current-'0'>=0 && '9'-(*current)>=0)
                       {
                          while(*current-'0'>=0 && '9'-(*current)>=0)
                            ++current;
                           yyleng = current - yytext;
                          return NUM;
                       }

            }
            break;

        }

    }

  }
}

int main() {
  while(1) {
    int val;
    val=lex();
    if(val==EOI)
      break;
    printf("%d\t%s\n",val,yytext);
  }
  return 0;
}
