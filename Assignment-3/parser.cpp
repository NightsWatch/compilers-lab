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


std::vector<std::string> tokenize(std::string s, std::string sep){
	// Skip delimiters at beginning.
	std::string::size_type lastPos = s.find_first_not_of(sep, 0);	
	// Find first "non-delimiter", which will be between lastPos and pos
	std::string::size_type pos = s.find_first_of(sep, lastPos); 
	std::vector<std::string> tokens;
	while(pos != std::string::npos || lastPos != std::string::npos){
		tokens.push_back(s.substr(lastPos,(pos - lastPos)));
		// Skip delimiters
		lastPos = s.find_first_not_of(sep, pos);	
		// Find "non-delimiter", which will be between lastPos and pos
		pos = s.find_first_of(sep, lastPos); 
	}
	return tokens;
}


void printMap(map<string, set<string> > List)

{
	 for(map<string, set<string> >::iterator iter = List.begin(); iter != List.end(); iter++ ) 
	 {
	 	        cout << (iter)->first << " is " << endl;

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
  		int linenum=0;
		while(getline(cfgfile, line))
		{
			istringstream iss(line);

			vector<string> tokens;
			copy(istream_iterator<string>(iss),
         		istream_iterator<string>(),
         		back_inserter<vector<string> >(tokens));

			set<string> productions;
			if(linenum==0)
			{
  				/* finding the list of terminals */
  				// if(strcmp(tokens[0],"t:")!=0) break;
				for(int i=1;i<tokens.size();i++)
				{
				  terminals.insert(tokens[i]);
				}
				linenum++;
				continue;

			}

			// Adding the list of nonterminals
			nonterminals.insert(tokens[0]);

		/* adding productions to the grammar -*/

			for(int i=1;i<tokens.size();i++)
				{

				  productions.insert(tokens[i]);
				}
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


 	/* loop through the grammar to find firtsets for all the nonterminals */
 	for(map<string, set<string> >::iterator iter = grammar.begin(); iter != grammar.end(); iter++ ) 
	{
 		getFirstSet(iter->first);
 	}

 	for(map<string, set<string> >::iterator iter = grammar.begin(); iter != grammar.end(); iter++ ) 
	{
 		getFollowSet(iter->first);
 	}

	for(map<string, string >::iterator iter = followOverlap.begin(); iter != followOverlap.end(); iter++ ) 
	{
		/* check if iter is A check if followOverlap[something]=A so that you update follw(A) before adding everything 
		 in follw(A) to B */

		for(map<string, string>::iterator iter2 = followOverlap.begin(); iter2 != followOverlap.end(); iter2++ ) 
		{
			if((iter->first)==(iter2->second))
			{
				// copy everything in follow of iter2 to follow of iter
				string temp= iter2->first;
				set<string> fromset= followSet[temp];
				set<string> tempset;
				for (std::set<string>::iterator iter3=fromset.begin(); iter3!=fromset.end(); ++iter3)
					tempset.insert(*iter3);
				followSet.insert(std::pair<string, set<string> >(iter->first, tempset));
			}
		}


		// Adding followset(iter) to followset(B) B=followoverlap(a)
	string temp2= iter->first;

	set<string> copyset= followSet[temp2];
		set<string> toset;		
		for (std::set<string>::iterator iter2=copyset.begin(); iter2!=copyset.end(); ++iter2)
								toset.insert(*iter2);

		string b=followOverlap[temp2];
				followSet.insert(std::pair<string, set<string> >(b, toset));

	}	

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
 			// for(int i=0;i< length(terminals) ;i++)
 			// {
 			// 	if(strcmp((*it).c_str(),terminals[i].c_str())==0)
 			// 		{
 			// 			symbols.insert(*it);
 			// 			continue;
 			// 		}					
 			// }


			if(terminals.find(*it) != terminals.end())
			{
				symbols.insert(*it);
				continue;

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
					if(terminals.find(s) != terminals.end())
					{
						symbols.insert(s);
						break;
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



	firstSet[nonterm]=symbols;


	

 }




void Parser::getFollowSet(string nonterm)
{
	set<string> symbols;
	// if the non-term is the start symbol add $ & return

	if(strcmp(nonterm.c_str(),"S")==0)
	{
		symbols.insert("$");
		return;
	}

	set<string> productions = grammar[nonterm];


	// iterarte through all the productions
	for (set<string>::iterator it=productions.begin(); it!=productions.end(); ++it)
	{

		int i=0;
 		int len= (*it).size();
 		i=len;

 		
 		string str= (*it);
		string s= str.substr(i-1,1);
		string prev= str.substr(i-2,1);

				//  first check if the firstSet is already computed else compute it

/*		map<string, set<string> >::iterator mapit = firstSet.find(s);
		if(mapit == firstSet.end())
 		{
				getFirstSet(s);
 		}	
*/

 		// X-> GhB so first calcluate the firstSet(B) and add it to followSet(h) AND IF first(B) has 'e' 
 		// then set followOverlap to add follow of A to follow of(h)
 				set<string> prodfirstSet = firstSet[s];
						
 				set<string> followseth;  //
				for (std::set<string>::iterator iter=prodfirstSet.begin(); iter!=prodfirstSet.end(); ++iter)
					{
						string temp=(*iter);
						if(strcmp(temp.c_str(),"e")!=0)
						followseth.insert(*iter);
						else
							followOverlap[nonterm]=prev; // set the followOverlap value of nonterm as e is found in the firstSet(B)
					}


					followSet.insert(std::pair<string, set<string> > (prev,followseth) );
					  
					
 		
	}

}

//// void Parser::getfollowSet(string);
// void Parser::createTable();

// void Parser::parse();

