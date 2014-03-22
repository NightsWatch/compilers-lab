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

term' -> TIMES factor term' | DIVIDE term term' | є

factor -> NUM_OR_ID | LP expr RP

expr'' -> LESSTHAN termp expr'' | GREATERTHAN termp expr'' | EQUALTO termp expr'' | є


*/

#include <stdio.h>
#include "lex.h"
#include <string.h>
#include <stdlib.h>

char    *factor     ( void );
char    *term       ( void );
char    *expression ( void );

char lookup[8][3]={"BL", "BH", "CH", "CL", "DH", "DL", "SI", "BP"};

extern char *newname( void       );
extern void freename( char *name );

int count=0;
char label[7];

opt_statement()
{
    /*  opt_stmts → stmt_list |є 
    stmt_list  → stmt_list; stmt | stmt

    equivalent to

    stmt_list ->stmt stmt'
    stmt' -> ; stmt stmt'| e

    */

     statements();
    //printf("enter optstat\n");

    // printf("\n" );
    while(match(SEMI))
    {       


       // printf("enter optstat match\n");
        
            advance();
            statements();
            //printf("\n");
                        //continue;
             

    }


}

void id_check(char* id)
{
    //printf("IN ID CHECK %c\n", id);
    FILE* fin=fopen("variables.txt", "r");       
    char *line=NULL;
    int nbytes = 10;
    int a = getline(&line, &nbytes, fin);
    int flag=0;
     int len = strlen(line);
    line[len-1] = '\0';
    while(a!=-1)
    {

        if(strcmp(id, line)==0)
        {
           
            flag=1;
            break;
        }

        a=getline(&line, &nbytes, fin);
        len = strlen(line);
        line[len-1] = '\0';
    }
    fclose(fin);
    if(flag!=1)
    {
       FILE* fin=fopen("variables.txt", "a");
       fprintf(fin, "%s\n", id);
       fclose(fin);    

    }

    return;
}


statements()
{
    /*  
    stmt → id := expr 
        | if expr then stmt
        | while expr do stmt
        | begin opt_stmts end 

    */
       // int flag=0;
    char *tempvar;

    while( !match(EOI) )
    {
        //stmt → id := expr; 

    	//printf("enter st while\n");
        if( match( SEMI ) )
           {
             // if(flag==1)
             // {
             //    freename(tempvar2);
             //    freename(tempvar3);
             // }
             break;
           }


        if(match(ID))
        { 
        	char* id;
            id =malloc(sizeof(char)*yyleng);
            int comp;
            for( comp = 0;comp<yyleng;comp++)
                 {      
                     id[comp]=yytext[comp];      
                     
                }
            id[comp]='\0';
          
           
           	advance();
        
            if(match(COLE))
            {
            	//printf("match cole\n");
                advance();
                //advance();
                //expression();
	

                tempvar = expression();
		       printf("%s = %s\n\n", id, tempvar );
               id_check(id);
                 int f1=tempvar[1]-'0';
            
                //printf("%d %d", f1, f2);
                FILE* file1=fopen("8086.txt", "a");
                fprintf(file1, "mov %s , %s \n", id, lookup[f1]);
                fclose(file1);
               

                   //  int f1=tempvar[1]-'0';
                    
         
              //  printf("mov \n", lookup[f2], lookup[f1]);
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
                 int f1=tempvar[1]-'0';
                 int f2=0;
                 if(tempvar[2]=='=')
                 {
                    f2=tempvar[5]-'0';
                    FILE* file1=fopen("8086.txt", "a");
                    fprintf(file1, "cmp %s , %s \n", lookup[f1], lookup[f2]);
                    char lab[7]="labelx";
                    
                    lab[5]=(char)(count+48);
                    strcpy(label, lab);
                    count++;
                    fprintf(file1, "jne %s\n", lab);
                    fclose(file1);



                    
                 }
                 else if(tempvar[2]=='<')
                 {
                    //printf("gerer");
                    f2=tempvar[4]-'0';
                     FILE* file1=fopen("8086.txt", "a");
                    fprintf(file1, "cmp %s , %s \n", lookup[f1], lookup[f2]);
                    char lab[7]="labelx";
                    
                    lab[5]=(char)(count+48);
                    strcpy(label, lab);
                    count++;
                    fprintf(file1, "jnbe %s\n", lab);
                    fclose(file1);


                 
                 }
                 else
                 {

                    f2=tempvar[4]-'0';
                     FILE* file1=fopen("8086.txt", "a");
                    fprintf(file1, "cmp %s , %s \n", lookup[f2], lookup[f1]);
                    char lab[7]="labelx";
                    
                    lab[5]=(char)(count+48);
                    strcpy(label, lab);
                    count++;
                    fprintf(file1, "jnbe %s\n", lab);
                    fclose(file1);


                 }
                    
                 //printf("IFIFIF %s, %s \n", lookup[f1], lookup[f2]);
            }



        else if(match(WHILE))
            {   
            	//printf("match while\n");
                advance();
                //flag=1;

                tempvar = expression();


                if(match(DO))
                    advance();
                // char *tempvar2=newname();
                // char *tempvar3=newname();
                // printf("%s=%c%c",tempvar2,tempvar[0],tempvar[1]);
                // if(tempvar[2]=='=')
                // {
                //     printf("%s=%c%c",tempvar3,tempvar[4],tempvar[5]);
                //     printf("while %s==%s do ", tempvar2,tempvar3);

                // }

                // else if(tempvar[2]=='<'|| tempvar[2]=='>')
                // {
                //     printf("%s=%c%c",tempvar3,tempvar[3],tempvar[4]);
                //     printf("while %s%c%s do", tempvar2, tempvar[2], tempvar3);

                // }

                printf("while %s do\n", tempvar );


                
            }
        
        else if(match(BEGIN))
            {   
                advance();
                        printf("begin\n");

                tempvar = opt_statement();

                if(match(END))
                   {
                   printf("end ");
                   
                   {
                     FILE* file1=fopen("8086.txt", "a");
                    fprintf(file1, "%s:\n", label);
                    fclose(file1);
                   }

                   freename( tempvar ); advance() ;break;}// advance();
            }

            
               else if(match(END))
                   {
                     printf("end ");
                     {
                     FILE* file1=fopen("8086.txt", "a");
                    fprintf(file1, "%s:\n", label);
                    fclose(file1);
                   }

                   
                   //printf("begin end1 ");
                   freename( tempvar );advance();break;
               }



         freename( tempvar );
    }
}


char    *termp()
{
     /* termp -> term expr'

    expr' -> PLUS term expr' | MINUS term expr' | є
*/
     
  
        // printf("enter termp %s", yytext);

    char  *tempvar, *tempvar2;

    tempvar=term();
    //printf("in termp %c\n", *yytext );

    while(match(MINUS) || match(PLUS))
   {
        
        //printf("looping %c ", *yytext);
        while( match( PLUS ) )
        {
            advance();
            tempvar2 = term();
            printf("%s += %s\n", tempvar, tempvar2 );
            int f1=tempvar[1]-'0';
            int f2=tempvar2[1]-'0';
            //printf("%d %d", f1, f2);
            FILE* file1=fopen("8086.txt", "a");
            fprintf(file1, "add %s , %s \n", lookup[f1], lookup[f2]);
            fclose(file1);
            freename( tempvar2 );
        }

       // if(flagp==1)continue;
       
         while( match( MINUS ) )
        {
            advance();
            tempvar2 = term();
            printf("%s -= %s\n", tempvar, tempvar2 );
             int f1=tempvar[1]-'0';
            int f2=tempvar2[1]-'0';
            FILE* file1=fopen("8086.txt", "a");
            fprintf(file1, "sub %s , %s \n", lookup[f1], lookup[f2]);
            fclose(file1);
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

                char* longone;
                longone =malloc(sizeof(char)*(strlen(tempvar)+strlen(tempvar2)+4));
                memset(longone, '\0', sizeof(char)*(strlen(tempvar)+strlen(tempvar2)+4));
                 
         
                 strcat(longone,tempvar);        
                 strcat(longone,"<");        
                 strcat(longone,tempvar2);
                //printf("%s= %s < %s\n", tempvar,tempvar, tempvar2 );
                freename( tempvar2 );
                freename(tempvar);
                return longone;
            }

        //if(flagl=1)continue;
       

        while( match( GREATERTHAN ) )
        {
            advance();
            tempvar2 = termp();
            char* longone;
            longone =malloc(sizeof(char)*(strlen(tempvar)+strlen(tempvar2)+4));
            memset(longone, '\0', sizeof(char)*(strlen(tempvar)+strlen(tempvar2)+4));

             strcat(longone,tempvar);        
             strcat(longone,">");        
             strcat(longone,tempvar2);
            //printf("%s=%s > %s\n", tempvar, tempvar, tempvar2 );
            freename( tempvar2 );
            freename(tempvar);
            return longone;
        }

        //if(flagg=1)continue;
       

        while( match( EQUALTO ) )
        {
            advance();
            //printf("match =");
            tempvar2 = termp();
            char* longone;
         longone =malloc(sizeof(char)*(strlen(tempvar)+strlen(tempvar2)+4));
             memset(longone, '\0', sizeof(char)*(strlen(tempvar)+strlen(tempvar2)+4));   

     
             // //strcat()       
         
             strcat(longone,tempvar);        
             strcat(longone,"==");       
             strcat(longone,tempvar2);
            //printf("%s= %s == %s\n", tempvar,tempvar, tempvar2 );
            freename( tempvar2 );
            freename(tempvar);
            return longone;
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
                 int f1=tempvar[1]-'0';
                int f2=tempvar2[1]-'0';
                FILE* file1=fopen("8086.txt", "a");
                fprintf(file1, "mov AL , %s \nmul %s\n", lookup[f2], lookup[f1]);
                fclose(file1);
                freename( tempvar2 );
            }

            

            while( match( DIV ) )
            {
                advance();
                tempvar2 = term();
                printf("%s /= %s\n", tempvar, tempvar2 );
                 int f1=tempvar[1]-'0';
                int f2=tempvar2[1]-'0';
                FILE* file1=fopen("8086.txt", "a");
                fprintf(file1, "mov AL , %s \ndiv %s\n", lookup[f1], lookup[f2]);
                fclose(file1);
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
         int f1=tempvar[1]-'0';
            FILE* file1=fopen("8086.txt", "a");
          fprintf(file1, "mov %s ,  %0.*s \n", lookup[f1], yyleng, yytext);
                fclose(file1);
        advance();
    }
    // else if( match(LP) )
    // {
    //     advance();
    //     tempvar = expression();
    //     if( match(RP) )
    //         advance();
    //     else
    //         fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno );
    // }
    else
	fprintf( stderr, "%c %d: Number or identifier expected\n", *yytext, yyleng );
	

	//printf("returning");
    return tempvar;
}


void declare_variables()
{
   
    FILE* fin=fopen("8086.txt", "r");
    int nbytes = 10;
    char *line=NULL;

    FILE* fout = fopen("output.txt", "w");
    fprintf(fout, "jmp start \n\n" );
    FILE* var = fopen("variables.txt", "r");
    int a = getline(&line, &nbytes, var);
    int len = strlen(line);
    line[len-1] = '\0';
    while(a!=-1)
    {

        fprintf(fout, "%s db 0\n", line);

        a=getline(&line, &nbytes, var);
        int len = strlen(line);
        line[len-1] = '\0';


    }
    fclose(var);
    fprintf(fout, "start:  ");
    a=getline(&line, &nbytes, fin);
     while(a!=-1)
    {
        fprintf(fout, "%s\n", line);

        a=getline(&line, &nbytes, fin);


    }
    fprintf(fout, "ret\n");
    fclose(fin);
    fclose(fout);

    return;




}


void clear_files(void)
{

    FILE* fin=fopen("variables.txt", "w");
    fclose(fin);
    FILE* fin2=fopen("8086.txt", "w");
    fclose(fin2);
    FILE* fin3=fopen("output.txt", "w");
    fclose(fin3);

}