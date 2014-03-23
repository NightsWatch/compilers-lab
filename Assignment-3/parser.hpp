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

using namespace std;

class Parser
{

public:
        map< string, set<string> > grammar;

        map< string, set<string> > firstSet;

		map< string, set<string> > followSet;

		map<string , map<string,string> > parsing_table;

		map<string, string> followOverlap;

		set<string> nonterminals;


		set<string> terminals;

		void getGrammar(string);
		void start();
		void getFollowSet(string);
		void getFirstSet(string);
		void createTable();

		void parse();
		
};