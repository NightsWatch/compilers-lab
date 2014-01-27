/*

stmt → id := expr
        | if expr then stmt
        | while expr do stmt
        | begin opt_stmts end 
opt_stmts → stmt_list |є
stmt_list  → stmt_list; stmt | stmt



expr -> termp expr''

termp -> term expr'

expr' -> PLUS term expr' | MINUS term expr' | є

term -> factor term'

term' -> TIMES factor term' | DIVIDE factor term' | є

factor -> NUM_OR_ID | LP expr RP

expr'' -> LESSTHAN termp expr'' | GREATERTHAN termp expr'' | EQUALTO termp expr'' | є


*/

#include <stdio.h>
#include "lex.h"

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );

extern char *newname( void       );
extern void freename( char *name );


opt_statement()
{
    /*  opt_stmts → stmt_list |є 
    stmt_list  → stmt_list; stmt | stmt

    equivalent to

    stmt_list ->stmt stmt'
    stmt' -> ; stmt stmt'| e

    */

     statements();
    printf("enter optstat\n");

     printf("\n" );
    while(match(SEMI))
    {       
        printf("enter optstat match\n");
        
            advance();
            statements();
            printf("\n");
                        //continue;
             

    }

}

statements()
{
    /*  
    stmt → id := expr 
        | if expr then stmt
        | while expr do stmt
        | begin opt_stmts end 

    */
    char *tempvar;

    while( !match(EOI) )
    {
        //stmt → id := expr; 

    	//printf("enter st while\n");
        if( match( SEMI ) )
            break;


        if(match(ID))
        { 
        	char id=*yytext;
        	//printf("match id %c\n",*id);
           
           	advance();
        
            if(match(COLE))
            {
            	//printf("match cole\n");
                advance();
                //advance();
                //expression();
	

                tempvar = expression();
		       printf("%c = %s\n", id, tempvar );
            }
		
		
	   // printf("if %s=%s", );
            else
                {
                    printf("Unknown grammar");
                    break;
                }


        }


        else if(match(IF))
            {   

                advance();

                tempvar = expression();

                if(match(THEN))
                    advance();
                printf("if %s then ", tempvar);
            }



        else if(match(WHILE))
            {   
            	printf("match while\n");
                advance();

                tempvar = expression();

                if(match(DO))
                    advance();
                printf("while %s do ", tempvar);
            }
        
        else if(match(BEGIN))
            {   
                advance();
                        printf("match begin\n");

                tempvar = opt_statement();

                if(match(END))
                   {
                   printf("begin  end ");
                   freename( tempvar );break;}// advance();
            }

            
               else if(match(END))
                   {
                   printf("begin end ");
                   freename( tempvar );break;}



         freename( tempvar );
    }
}


char    *termp()
{
    /*  termp -> term expr'

    expr' -> PLUS term expr' | MINUS term expr' | є

     */
  
        // printf("enter termp %s", yytext);

    char  *tempvar, *tempvar2;

    tempvar=term();

    while(match(MINUS) || match(PLUS))
   {
        
        //printf("looping %c ", *yytext);
        while( match( PLUS ) )
        {
            advance();
            tempvar2 = term();
            printf("%s += %s\n", tempvar, tempvar2 );
            freename( tempvar2 );
        }

       // if(flagp==1)continue;
       
         while( match( MINUS ) )
        {
            advance();
            tempvar2 = term();
            printf("%s -= %s\n", tempvar, tempvar2 );
            freename( tempvar2 );
        }
    }

    //printf("returning termp\n");
    return tempvar;
}



char    *expression()
{

     //printf("enter expr %s", yytext);
     //expr -> termp expr''
   
        char  *tempvar, *tempvar2, *tempvar3;
        tempvar = termp();
        //printf("returned frrm termp\n");
   
         // Grammar for expr''

         //     expr'' -> LESSTHAN termp expr'' | GREATERTHAN termp expr'' | EQUALTO termp expr'' | є
     
   while(match(LESSTHAN) || match(GREATERTHAN) || match(EQUALTO))
   {
      

         while( match( LESSTHAN ) )
            {
                advance();
                tempvar2 = termp();
                printf("%s= %s < %s\n", tempvar,tempvar, tempvar2 );
                freename( tempvar2 );
                //freename(tempvar);
            }

        //if(flagl=1)continue;
       

        while( match( GREATERTHAN ) )
        {
            advance();
            tempvar2 = termp();
            printf("%s=%s > %s\n", tempvar, tempvar, tempvar2 );
            freename( tempvar2 );
            //freename(tempvar);
        }

        //if(flagg=1)continue;
       

        while( match( EQUALTO ) )
        {
            advance();
            //printf("match =");
            tempvar2 = termp();
            printf("%s= %s == %s\n", tempvar,tempvar, tempvar2 );
            freename( tempvar2 );
            //freename(tempvar);
        }
    }

//printf("returning expr\n");
return tempvar;
       
}






char    *term()
{

    /*
    term -> factor term'

    term' -> TIMES factor term' | DIVIDE factor term' | є
    */

        // printf("enter term %s", yytext);

    char  *tempvar, *tempvar2 ;

    tempvar = factor();
    //printf("return factor\n");
    while(1)
   {
        int flagp=0,flagm=0;
        if(match(TIMES))
            flagp=1;
       

        if(match(DIV))
            flagm=1;
       

        if(flagp==0&&flagm==0)break;

            while( match( TIMES ) )
            {
                advance();
                tempvar2 = factor();
                printf("%s *= %s\n", tempvar, tempvar2 );
                freename( tempvar2 );
            }

            

            while( match( DIV ) )
            {
                advance();
                tempvar2 = factor();
                printf("%s /= %s\n", tempvar, tempvar2 );
                freename( tempvar2 );
            }

    }

    //printf("returning from term\n");
    return tempvar;
}



char    *factor()
{
    char *tempvar;

         //printf("enter factor %s", yytext);


    if( match(NUM) || match(ID) )
    {
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */

        printf("%s = %0.*s\n", tempvar = newname(), yyleng, yytext );
        advance();
    }
    else if( match(LP) )
    {
        advance();
        tempvar = expression();
        if( match(RP) )
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    }
    else
	fprintf( stderr, "%c %d: Number or identifier expected\n", *yytext, yyleng );
	

	//printf("returning");
    return tempvar;
}
