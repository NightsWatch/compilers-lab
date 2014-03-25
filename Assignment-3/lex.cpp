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

FILE* fp;

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
         if(!fgets(input_buffer,1023,fp)){
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
              case ',':
                return COMMA;
             case '+':
              return PLUS;
             case '-':
              return MINUS;
             case '*':
             if(*(current+1)=='/')
             {
              printf("Stray */ found\n");
              ++current;
              continue;
             }
              return TIMES;

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
              return DIVIDE;
             case '(':
              return LP;
             case ')':
              return RP;
            // case '[':
            //     return LSB;
            // case ']':
            //     return RSB;
            case '<':
              if(*(current+1)=='=')
                ++current;
              return LESSTHAN;
            case '>':
            if(*(current+1)=='=')
                ++current;
            return GREATERTHAN;
            case '=':
             if(*(current+1)=='=')
                { 

                  ++current;
                  return EQUALTO;
                }
            return EQUALS;
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

                      if (*current=='v' && *(current+1)=='o' && *(current+2)=='i' && *(current+3)=='d'   && (*(current+4)==' ' || *(current+4)==')' ) )
                       {     //current+=3;
                          yyleng=4;

                          return VOID;
                      }


                      if (*current=='r' && *(current+1)=='e' && *(current+2)=='t' && *(current+3)=='u' && *(current+4)=='r' &&  *(current+5)=='n'  && (*(current+6)==' ' || *(current+6)==';' ))
                       {     //current+=3;
                          yyleng=6;

                          return RETURN;
                      }



                      if (*current=='b' && *(current+1)=='r' && *(current+2)=='e' && *(current+3)=='a' && *(current+4)=='k'  && (*(current+5)==' ' || *(current+5)==';' ))
                        {    //current+=3;
                          yyleng=5;

                          return BREAK;
                      }


                      if (*current=='c' && *(current+1)=='o' && *(current+2)=='n' && *(current+3)=='t' && *(current+4)=='i' &&  *(current+5)=='n' &&  *(current+6)=='u' &&  *(current+7)=='e' && (*(current+8)==' ' || *(current+8)==';' ))
                        {    //current+=3;
                          yyleng=8;

                          return CONTINUE;
                      }

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
                          return ELSE;
                      }

                     if (*current=='i' && *(current+1)=='n' && *(current+2)=='t' && *(current+3)==' ') 
                      {
                          yyleng=3;
                          cout << "here" << endl;
                          return DATA_TYPE;
                      }


                     if (*current=='c' && *(current+1)=='h' && *(current+2)=='a'&& *(current+3)=='r' && *(current+4)==' ') 
                      {
                          yyleng=4;
                          return DATA_TYPE;
                      }

                    if (*current=='d' && *(current+1)=='o' && *(current+2)=='u'&& *(current+3)=='b' && *(current+4)=='l' && *(current+5)=='e' && *(current+6)==' ') 
                      {
                          yyleng=6;
                          return DATA_TYPE;
                      }

                     if (*current=='f' && *(current+1)=='l' && *(current+2)=='o'&& *(current+3)=='a'&& *(current+4)=='t' && *(current+5)==' ') 
                      {
                          yyleng=5;
                          return DATA_TYPE;
                      } 

                     
                     if( ( *current-'a'>=0 && 'z'-(*current)>=0 ) || ( *current-'A'>=0 && 'Z'-(*current)>=0 ) )
                       {

                          while(isalnum(*current))
                            ++current;
                           yyleng = current - yytext;
                           if(*current=='(')
                           {
                              
                              return FUNCNAME;
                           }
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

void LexAnalyser::getTokens( string inp, string outp)
    {
      //ifstream fin(inp);
      fp=fopen(inp.c_str(),"r");
      FILE* fop;
      fop=fopen(outp.c_str(),"w");
      while(1) {
          char *val;
          val=lex();
          if(val==EOI)
            break;
          fprintf(fop,"%s",val);
          
          
         /*int temp=0;
          for (temp=0;temp<yyleng;temp++)
          {
            fprintf(fop,"%c",yytext[temp]);

          }
         */ 
          
          fprintf(fop,"\n");
        }

        fclose(fp);
        fclose(fop);


    }
