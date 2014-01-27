#include <stdio.h>
#include  <string.h>

int main(int argc, char **argv)
{
	if(argc!=3)
	{
		printf("Please enter file names as argument.\n");
		return 1;
	}
	char c;
	FILE* fin=fopen(argv[1], "r");
	FILE* fout=fopen(argv[2], "w");
	c = getc(fin) ;
	while(c!=EOF)
	{

		putc(c, fout);
		c=getc(fin);
	}

	fclose(fin);
	fclose(fout);

	return 0;

}