#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <iterator>
#include <map>

#define map<string, set<string> >::iterator pit
#define set<string>::iterator sit

using namespace std;

class Parser
{

public:
        map< string, set<string> > grammar;

        map< string, set<string> > firstSet;

		map< string, set<string> > followSet;

		map<string , map<string,string> > parsing_table;

<<<<<<< HEAD
		map<string, string> followOverlap;

		set<string> nonterminals;


		set<string> terminals;
=======
		stack <string> parserstack;

		string terminals[];
>>>>>>> d5eb594dbd411e7b7421e2fde0876a795c70130b

		void getGrammar(string);
		void start();
		void getFollowSet(string);
		void getFirstSet(string);
		void createTable();
		set<string> giveFirst(string);
		void appendSets(set<string>,set<string>);

		void parse();
		
};