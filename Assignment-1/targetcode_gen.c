#include <stdio.h>
#include  <string.h>

char lookup[8][5]={'BL', 'BH', 'CH', 'CL', 'DH', 'DL', 'SI', 'BP'};


void add_function(char** line, FILE* fout);


int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("Please enter file names as argument.\n");
		return 1;
	}
	char c;
	int nbytes = 10;
	FILE* fin=fopen(argv[1], "r");
	FILE* fout=fopen(argv[2], "w");
	printf("start");
	char *line=NULL;
	int a = getline(&line, &nbytes, fin);
	printf("sdsadsad");
	while(a!=-1)
	{
		int eq_count=0;

		int i=0;

		for(i=0; line[i]!='\0'; i++)
		{

			printf("%c", line[i]);

			if(line[i]=='+')
			{
				add_function(line, fout);
				break;
			}
			if(line[i]=='-')
			{
				//sub_function(line, fout);
				break;
			}
			if(line[i]=='*')
			{
				//mul_function(line, fout);
				break;
			}
			if(line[i]=='/')
			{
				//div_function(line, fout);
				break;
			}
			if(line[i]=='*')
			{
				//mul_function(line, fout);
				break;
			}
			if(line[i]=='=')
			{
				eq_count++;
			}



		}
		if(eq_count==1)
		{
			//move_function(line, fout);
		}
		a=getline(&line, &nbytes, fin);
		//getchar();

	}


	//printf("%s", line);
	
	/*c = getc(fin) ;
	while(c!=EOF)
	{

		putc(c, fout);
		c=getc(fin);
	}
*/
	fclose(fin);
	fclose(fout);

	return 0;

}

void add_function(char** line, FILE* fout)
{
	printf("ADD\n");
	char *first;
	int f1;
	char *second;
	int i;
	printf("%d\n", atoi(line[0]));
	if(line[0]=='t')
	{
		printf("jsdjsajd");
		printf("%c\n", line[1]);
		f1=atoi(line[1])-48;
		printf("%d\n", f1);
		first = lookup[f1];
		
	}

	printf("%s", first);
	return;



}