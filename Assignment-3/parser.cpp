#include "parser.hpp"
#include "lex.hpp"

extern string terminals[];

string tokenfile="token_list.txt";

int main(int argc, char** argv)
{
	if(argc!=3)
	{
		cout<<"Input format: exec codefilename grammarfilename";
		exit(1);
	}

	Parser p=Parser();
	LexAnalyser l=LexAnalyser();

	l.getTokens(argv[1],tokenfile);

	p.getGrammar(argv[2]);

	p.eliminateLRecurse();

	p.createTable();

	//p.start();
}


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

void printTable(map < string, map < string,string > > table) {
	for(tab_it it=table.begin();it!=table.end();it++) {
		cout << "For non-T "<<it->first<<":\n";
		for(map<string,string>::iterator m_it=(it->second).begin();m_it!=(it->second).end();m_it++) {
			cout << m_it->first <<" " <<m_it->second<<endl;
		}
	}

}


void printMap(map < string, set<string> > List)
{

	 for(map<string, set<string> >::iterator iter = List.begin(); iter != List.end(); iter++ ) 
	 {
	 	set <string> value = iter->second;
	 	        for (sit iter2= value.begin(); iter2 != value.end(); iter2++)
	 	      {  cout << (iter)->first << " is "<< (*iter2) << endl;} 
	 	        //
	 }
	 return;
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
	cout<<"Grammar is:"<<endl;
	printMap(grammar);
	cout<<endl;
}



set<string> Parser::appendSets(set<string> first,set<string> second) {
	set<string> result;
	for(sit it=first.begin();it!=first.end();it++) {
		result.insert(*it);
	}

	for(sit it=second.begin();it!=second.end();it++) {
		result.insert(*it);
	}
	return result;
}

set<string> Parser::giveFirst(string prod) {
	int j=0;
	set<string> result;
	for(int i=0;i<prod.size();i++) {
		if(terminals.find(prod.substr(j,i-j+1))!=terminals.end()) {
			result.insert(prod.substr(j,i-j+1));
			return result;
		}

		else if (nonterminals.find(prod.substr(j,i-j+1))!=nonterminals.end())
		{
			string nont=prod.substr(j,i-j+1);
			if(firstSet[nont].find("e")!=firstSet[nont].end()) {
				result=appendSets(firstSet[nont],giveFirst(prod.substr(i+1,prod.size()-i)));
			} else {
				return firstSet[nont];
			}
		} 

		else {
			continue;
		}
	}
	return result;
}


void Parser::createTable() {
	for(pit iter = grammar.begin(); iter != grammar.end(); iter++ ) {
 		
 		for(sit it=(iter->second).begin();it!=(iter->second).end();it++) {
 			set<string> firstSymbols=giveFirst(*it);
 			for(sit fs=firstSymbols.begin();fs!=firstSymbols.end();fs++) {
 				//map<string , map<string,string> > parsing_table;
 				//parsing_table[iter->first]=
 				  /*pair<sit, bool> pr =*/ 
 				parsing_table[iter->first].insert(make_pair(*fs,*it));
 				  // if(!pr.second)
 				  // {	
 				  // 	printf("Grammar is not LL(1). Exiting parsing.\n");
 				  // 	exit(0);

 				  // }

 				//someStorage["key"].insert(std::make_pair("key2", "value2")));
 			}

 			if(firstSymbols.find("e")!=firstSymbols.end()) 
 			{
 				for(sit fs=followSet[iter->first].begin(); fs!=firstSet[iter->first].end(); fs++)
 				{	
 					parsing_table[iter->first].insert(make_pair(*fs,*it));
 					// if(!pr.second)
 					// {	
	 				//  	printf("Grammar is not LL(1). Exiting parsing.\n");
	 				//  	exit(0);

 				 // 	}

 				}
 			}
 		}
 	}
 	cout<<"Created Table:\n";
 	printTable(parsing_table);
}

void Parser::eliminateLRecurse() {
	map<int,string> ind;
	int i=1;
	for(sit it=nonterminals.begin();it!=nonterminals.end();it++) {
		ind[i]=*it;
		i++;
	}

	for(int i=1;i<=nonterminals.size();i++) {
		for(int j=1;j<i;j++) {
			for(sit it=grammar[ind[i]].begin();it!=grammar[ind[i]].end();it++) {
				int len=ind[j].size();
				string str=*it;
				if(str.substr(0,len)==ind[j]) {
					grammar[ind[i]].erase(it);
					for(sit it2=grammar[ind[j]].begin();it2!=grammar[ind[j]].end();it2++) {
						string temp=(*it2)+str.substr(len,str.size()-len);
						grammar[ind[i]].insert(temp);
					}
				}
			}
		}

		//eliminate left-recursion from among the Ai productions
		string newNonTerm="."+ind[i]+"1"+".";
		int len=ind[i].size()+2;
		set<string> upr,lpr;
		for(sit it=grammar[ind[i]].begin();it!=grammar[ind[i]].end();it++) {
			string str=*it;
			if(str.substr(0,len)==("."+ind[i]+".")) {
				lpr.insert(str.substr(len,str.size()-len)+newNonTerm);
			} else {
				upr.insert(str+newNonTerm);
			}
		}
		lpr.insert("e");

		grammar[ind[i]]=upr;
		grammar[ind[i]+"1"]=lpr;
	
	}

	cout<<"Eliminated Grammar is:"<<endl;
	printMap(grammar);
	cout<<endl;
}


 void Parser::start()
 {

 	/*
 	check for left recursion and remove it
 	*/


 	/* loop through the grammar to find firtsets for all the nonterminals */
 	for(map<string, set<string> >::iterator iter = grammar.begin(); iter != grammar.end(); iter++ ) 
	{
		cout<<"calling "<<iter->first<<endl;
 		getFirstSet(iter->first);
 		cout<<endl;
 	}

 	cout<<"Firstset is:"<<endl;
	  printMap(firstSet);
	 cout<<endl;

 	 return;
	/*for debuggin*/

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
		if(strcmp((*it).c_str(),".e.")==0)
			{
				symbols.insert("e");
				continue;
			}

			//takes care of the case A -> .a.
			string term = (*it).substr(1,((*it).length())-2);

			if(terminals.find(term) != terminals.end())
			{

				symbols.insert(term);
				cout<<"added "<<term<<endl;
				continue;

			}


			int i=0;
 			int len= (*it).size();
 			int prevdot = 0;
 			int seconddot;
			while(i<len)
 			{
 				cout<<"i:"<<i<<endl;
 				string str= (*it);
 				cout<<"string is:"<<str<<endl;

 				cout<<"prevdot is:"<<prevdot<<endl;

 				//int seconddot = str.find(".",prevdot+1);
 				seconddot = getNextDotLocation(prevdot,str);
 				if(seconddot<0)
 					break;


 				cout<<"second dot:"<<seconddot<<endl;
 				//cout<<"dotsplit"<<endl;


 				string s= getStringBetweenTwoDots(prevdot,seconddot, str);
 				//str.substr(prevdot+1,seconddot-prevdot-1);
 				cout<<"split string is:"<<s<<endl;

				// check for terminals if found add and break
				if(terminals.find(s) != terminals.end())
				{
					symbols.insert(s);
					cout<<"foudn in terminals so added: "<<s<<endl;
					break;
				}				
				

				//  first check if the firstset is already computed else compute it
				map<string, set<string> >::iterator mapit = firstSet.find(s);
				cout<<"Searching for:"<<s<<"in already computed"<<endl;
				if(mapit == firstSet.end())
 					{
						getFirstSet(s);
	 				}	
	 				cout<<"reached"<<endl;
 					set<string> prdfirstSet = firstSet[s];
 					printSet(prdfirstSet);
 					/*debug
 					cout<<"Printing set "<<s<<endl;
 					printSet(prdfirstSet);
					/**/

 					for (set<string>::iterator it=prdfirstSet.begin(); it!=prdfirstSet.end(); ++it)
					  {
					  	symbols.insert(*it);
					  }

 					set<string>::iterator setit= prdfirstSet.find("e");
 					// check if the prdtnfirstset has 'e'
 					if(setit == prdfirstSet.end())
					{
 						break;

					 }
 					i++;
 					prevdot = seconddot;
					symbols.insert("e");	
					cout<<"added e to symbols"<<endl;

			}
	}



	firstSet[nonterm]=symbols;


	

 }




void Parser::getFollowSet(string nonterm){
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



void Parser::parse(string tokensfile)
{

	parserstack.push("$");
	parserstack.push("S");

	string x,a;

	ifstream tokensfilestream(tokensfile.c_str());

	if (tokensfilestream.is_open())
  	{
		while (!parserstack.empty())
		{
			x = parserstack.top();
			parserstack.top();
			getline(tokensfilestream, a);
			if (tokensfilestream.eof())
				a = "$";

			if(terminals.find(x)!=terminals.end() || !strcmp(x.c_str(),"$"))
			{
				if(x==a)
					continue;
				else
					return ;
			}
			else
			{
				string value = parsing_table[x][a];

				if ( parsing_table.find(x) == parsing_table.end() ) 
				{
				 	return ;
				} 
				else 
				{
				 	if ( parsing_table[x].find(a) == parsing_table[x].end()  ) 
				 	{
						  return ;
					} 
					else 
					{
						  string value = parsing_table[x][a];
						  vector<string> nterms = tokenize(value,".");
						  for(int i=nterms.size()-1;i>0;i--) 
						  {
						  	parserstack.push(nterms[i]);
						  }
					}

				}

			}
		}
		
		if (!tokensfilestream.eof())
			return ;

		return ;
	}
	tokensfilestream.close();
}


int Parser::getNextDotLocation(int currdot, string s)
{
	return s.find(".",currdot+1);
}

string Parser::getStringBetweenTwoDots(int prevdot, int nextdot, string str )
{
	if(prevdot<nextdot)
 		return str.substr(prevdot+1,nextdot-prevdot-1);
 	else
 		return str.substr(nextdot+1, prevdot - nextdot -1);
}

int Parser::getNextDotReverse(int currdot, string str)
{

	std::reverse(str.begin(), str.end());
	int newcurdot= str.length() - currdot -1;
	
	return str.find(".",newcurdot+1);

}
