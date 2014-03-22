
#include "parser.hpp"
#include "lex.hpp"

extern string terminals[];

string tokenfile="token_list.txt";

int length(string* array)
{
	int i;
	while (!array[i].empty())
        ++i;
    return i;
}


void printMap(map<string, set<string> > List)
{
	 for(map<string, set<string> >::iterator iter = List.begin(); iter != List.end(); iter++ ) 
	 {
	 	       // cout << (*iter)->first << " is " << endl;

	 }
}


void printSet(set<string> List)
{
	 for(set<string>::iterator iter = List.begin(); iter != List.end(); iter++ ) 
	 {
	 	        cout << (*iter)<< " value in set"<< endl;

	 }
}



void Parser::getGrammar(string fname)
{
	ifstream cfgfile(fname.c_str());
	string line;
	if (cfgfile.is_open())
  	{
		while(getline(cfgfile, line))
		{
			istringstream iss(line);

			vector<string> tokens;
			copy(istream_iterator<string>(iss),
         		istream_iterator<string>(),
         		back_inserter<vector<string> >(tokens));

			set<string> productions;

			for(int i=1;i<tokens.size();i++)
				productions.insert(tokens[i]);

			grammar.insert( std::pair<string, set<string> >(tokens[0],productions) );

  
		}

		cfgfile.close();
	}
}



int main(int argc, char** argv)
{
	if(argc!=3)
	{
		cout<<"Input format: exec codefilename grammarfilename";
		exit(1);
	}

	// Parser p=Parser();
	// LexAnalyser l=LexAnalyser();

	// l.getTokens(argv[1],tokenfile);

	// p.getGrammar(argv[2]);

	// p.start();
}


 void Parser::start()
 {

 	/*
 	check for left recursion and remove it
 	*/
 	
 	/* loop through grammar and get first sets of each nonterminal */
 	getFirstSet("E");
 	//getFollowSet();
 	//createTable();
 	//parse();

 }



 void Parser::getFirstSet(string nonterm)
{

	set<string> productions = grammar[nonterm];

 	set<string> symbols;


   for (set<string>::iterator it=productions.begin(); it!=productions.end(); ++it)
	{
		if(strcmp((*it).c_str(),"e")==0)
			{
				symbols.insert("e");
				continue;
			}
 			// Check if the production string is a terminal
 			for(int i=0;i< length(terminals) ;i++)
 			{
 				if(strcmp((*it).c_str(),terminals[i].c_str())==0)
 					{
 						symbols.insert(*it);
 						continue;
 					}					

 			}

			int i=0;
 			int len= (*it).size();
			while(i<len)
 			{
 				string str= (*it);
				string s= str.substr(i,1);

				// check for terminals if found add and break
				if(i>=1)
				{
					for(int j=0;j< length(terminals) ;j++)
		 			{
		 				if(strcmp((s).c_str(),terminals[j].c_str())==0)
		 					{
		 						symbols.insert(s);
		 						break;
		 					}					

		 			}
				}


				
				map<string, set<string> >::iterator mapit = firstSet.find(s);

				// check if the prdtnfirstset has 'e'
				//  first check if the firstset is already computed else compute it

				if(mapit == firstSet.end())
 				{
					getFirstSet(s);
 				}	
 						set<string> prdfirstSet = firstSet[s];
 						set<string>::iterator setit= prdfirstSet.find("e");

 						if(setit == prdfirstSet.end())
						{
							/* 'e' not found so copy the first set of the prdtn to the nonterminal*/

							for (std::set<string>::iterator iter=prdfirstSet.begin(); iter!=prdfirstSet.end(); ++iter)
							{
								symbols.insert(*iter);
							}
 							break;

					  }

 						i++;
				symbols.insert("e");
				
			}

	}


	
 }



// void Parser::getFollowSet(string );
// void Parser::getFirstSet(string);
// void Parser::createTable();

// void Parser::parse();
