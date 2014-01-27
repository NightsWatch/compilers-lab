#include <stdio.h>
#include <ctype.h>
#include "lex.h"

char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int lex(void){

   static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
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
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
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
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            
            if (*current==':')
            {
              ++current;
              if(*current=='=')
                {
                  ++current;
                  yyleng=2;
                 return COLE;
                }

            }
             

            if(!isalnum(*current))
               fprintf(stderr, "No valid token <%c>\n", *current);

            else{

                    if (*current=='i' && *(current+1)=='f' &&  *(current+2)==' ' )
                    {
                      //current+=3;
                      yyleng=2;

                      return IF;
                    }

                    if (*current=='t' && *(current+1)=='h' && *(current+2)=='e' && *(current+3)=='n' && *(current+4)==' '  )
                        {
                          //current+=5;
                          yyleng=4;
                          return THEN;
                        }

                   if (*current=='w' && *(current+1)=='h' && *(current+2)=='i' && *(current+3)=='l' && *(current+4)=='e' &&  *(current+5)==' '  )
                        {
                          //current+=6;
                          yyleng=5;
                          return WHILE;
                        }

                    if (*current=='d' && *(current+1)=='o'  &&  *(current+2)==' '  )
                        {
                          //current+=3;
                          yyleng=2;
                          return DO;
                        }

                    if (*current=='b' && *(current+1)=='e' && *(current+2)=='g' && *(current+3)=='i' && *(current+4)=='n' &&  *(current+5)==' '  )
                        {
                          //current+=6;
                          yyleng=5;
                          return BEGIN;
                        }

                    if (*current=='e' && *(current+1)=='n' && *(current+2)=='d' /* && (*(current+4)==' ' ||  *(current+5)=='\0') */ )
                        {
                          yyleng=3;
                          // current+=4;
                          return END;
                        }


             // do for-- do, end, begin


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


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}
