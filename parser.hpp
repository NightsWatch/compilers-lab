#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stack>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Parser
{

public:
        map< string, set<string> > grammar;

        map< string, set<string> > first;

		map< string, set<string> > follow;

		map<string , map<string,string> > parsing_table;


		void getGrammar(string);
		void start();
		void getFollowSet(string );
		void getFirstSet(string);
		void createTable();

		void parse();
		
};