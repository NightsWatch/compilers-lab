#include <stdio.h>
#include <ctype.h>
#include "lex.h"
#include <string>
#include "lex.hpp"
//char *yytext;    /* in lex.c     */
//int yyleng;
//int yylineno;]

char* yytext = ""; /* Lexeme (not '\0'
                      terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */

int linecommented=0;
int blockcommented=0;

char* lex (void) {
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
         if (linecommented)
         {
          linecommented=0;
         }
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
          //printf("%c", *current);
        //printf("lc %d, bc %d",linecommented,blockcommented);
        if(linecommented || blockcommented)
            {
              

              if(*current=='*' && *(current+1)=='/')
               { 
                if(blockcommented)
                  {
                    blockcommented=0;
                    ++current;
                   
                  }
           
                  continue;

               }

              else
                continue;
            }

          switch( *current )
          {
             case ';':
              return SEMI;
             case '+':
              return OPERATOR;
             case '-':
              return OPERATOR;
             case '*':
             if(*(current+1)=='/')
             {
              printf("Stray */ found\n");
              ++current;
              continue;
             }
              return OPERATOR;

             case '/':
              if(*(current+1)=='/')
              {
                linecommented=1;
                continue;
              }
              else if(*(current+1)=='*')
               { if(linecommented)
                  continue;

                 blockcommented=1;
                 continue;
               }
              return OPERATOR;
             case '(':
              return LP;
             case ')':
              return RP;
            // case '[':
            //     return LSB;
            // case ']':
            //     return RSB;
            case '<':
              return COMPOPER;
            case '>':
            return COMPOPER;
            case '=':
            return COMPOPER;
            case  '{':
              return LFP;
            case  '}':
              return RFP;
             case '\n':
                if(linecommented)
                  linecommented=0;
             case '\t':
             case ' ' :
              break;
             default:

          if(*current=='\'')
            {
              if(*(current+2)!='\'')
                 fprintf(stderr, "No valid token <%c>\n", *current);
              else
                {yyleng=3;
                return CHAR;}
            }

           else if(!isalnum(*current))
               fprintf(stderr, "No valid token <%c>\n", *current);

            
                
            else {
                   /*   if(*current=='/' && *(current+1)=='*')
                        blockcommented=1;

                      if(*current=='/' && *(current+1)=='/')
                        {
                        if (!blockcommented)
                          linecommented=1;
                        else
                          continue;
                        }*/

                      if (*current=='i' && *(current+1)=='f' &&  (*(current+2)==' ' ) || *(current+2)=='(') {
                            //current+=3;
                          yyleng=2;

                          return KEYWORD;
                      }

                      if(*current=='f' && *(current+1)=='o' && *(current+2)=='r' && (*(current+3)=='(' || *(current+3)==' ')) {
                          yyleng=3;
                          return KEYWORD;
                      }

                      if (*current=='w' && *(current+1)=='h' && *(current+2)=='i' && *(current+3)=='l' && *(current+4)=='e' &&  (*(current+5)==' ' || *(current+5)=='(' )) {
                          yyleng=5;
                          return KEYWORD;
                      }

                      if (*current=='e' && *(current+1)=='l' && *(current+2)=='s' && *(current+3)=='s' &&  (*(current+4)==' ' || *(current+4)=='(' )) 
                      {
                          yyleng=5;
                          return KEYWORD;
                      }

                     if (*current=='i' && *(current+1)=='n' && *(current+2)=='t') 
                      {
                          yyleng=3;
                          return KEYWORD;
                      }


                     if (*current=='c' && *(current+1)=='h' && *(current+2)=='a'&& *(current+3)=='r') 
                      {
                          yyleng=4;
                          return KEYWORD;
                      }

                    if (*current=='d' && *(current+1)=='o' && *(current+2)=='u'&& *(current+3)=='b' && *(current+4)=='l' && *(current+5)=='e') 
                      {
                          yyleng=6;
                          return KEYWORD;
                      }

                     if (*current=='f' && *(current+1)=='l' && *(current+2)=='o'&& *(current+3)=='a'&& *(current+2)=='t') 
                      {
                          yyleng=5;
                          return KEYWORD;
                      } 
                      /*if (*current=='m' && *(current+1)=='a' && *(current+2)=='i'&& *(current+3)=='n') 
                      {
                          yyleng=4;
                          return KEYWORD;
                      } */                    

                     if( ( *current-'a'>=0 && 'z'-(*current)>=0 ) || ( *current-'A'>=0 && 'Z'-(*current)>=0 ) )
                       {
                          while(isalnum(*current))
                            ++current;
                           yyleng = current - yytext;
                          return ID;
                       }

                       if(*current-'0'>=0 && '9'-(*current)>=0)
                       {

                            while(*current-'0'>=0 && '9'-(*current)>=0 )
                            {  
                                                         ++current;
                             // printf("%c",*current);
                            }
                         if( ( *current-'a'>=0 && 'z'-(*current)>=0 ) || ( *current-'A'>=0 && 'Z'-(*current)>=0 ) )
                         {
                            printf("Invalid token\n");
                            continue;

                         }
                          //printf("yes");
                          if(*current=='.')
                          { //printf("sadsadyes");
                              ++current;
                              while(*current-'0'>=0 && '9'-(*current)>=0 )
                                {

                                  ++current;
                                }    
                                  if( ( *current-'a'>=0 && 'z'-(*current)>=0 ) || ( *current-'A'>=0 && 'Z'-(*current)>=0 ) )
                                  {
                                      printf("Invalid token\n");
                                      continue;

                                  }

                                yyleng = current - yytext;
                                return FLOAT;                      }    
                          }
                          
                          yyleng = current - yytext;
                          return NUM;
                       
                     }

            
            break;
            }
          }

        

      

  }
}

void getTokens( string inp, string outp)
    {
      while(1) {
          char *val;
          val=lex();
          if(val==EOI)
            break;
          printf("<%s,",val);
          
          
         int temp=0;
          for (temp=0;temp<yyleng;temp++)
          {
            printf("%c",yytext[temp]);

          }
          
          
          printf(">\n");
        }
        return ;


    }

