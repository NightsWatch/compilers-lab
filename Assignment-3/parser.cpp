
#include "parser.hpp"
#include "lex.hpp"

string tokenfile="token_list.txt";


int main(int argc, char* argv)
{
	if(argc!=3)
	{
		cout<<"Input format: exec codefilename grammarfilename";
	}

	Parser p;
	Lex l;

	l.getTokens(argv[1],tokenfile);

	p.getGrammar(argv[2]);

	p.start();

}


void Parser::getGrammar(string)
{

}

void Parser::start()
{
	
}


void Parser::getFollowSet(string );
void Parser::getFirstSet(string);
void Parser::createTable();

void Parser::parse();