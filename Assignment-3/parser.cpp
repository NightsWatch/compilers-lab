#include "parser.hpp"
#include "lex.hpp"

string tokenfile="token_list.txt";
string codefile;

int main(int argc, char** argv)
{
	if(argc!=3)
	{
		cout<<"Input format: exec codefilename grammarfilename";
		exit(1);
	}
	codefile = argv[1];

	Parser p=Parser();
	LexAnalyser l=LexAnalyser();

	l.getTokens(argv[1],tokenfile);

	p.getGrammar(argv[2]);

	p.eliminateLRecurse();

	p.start();

	p.createTable();

	p.parse(tokenfile);

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

void printTable(map < pair<string, string>, string > table) {
	
	for(tab_it it=table.begin();it!=table.end();it++) 
	{

		cout<<(it->first).first<<"\t"<<(it->first).second<<"\t" << it->second<<"\n";
	}
	cout<<endl;
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

void Parser::printFollowMap(map < string, set<string> > List)
{

	 for(map<string, set<string> >::iterator iter = List.begin(); iter != List.end(); iter++ ) 
	 {
	 	if(terminals.find(iter->first) == terminals.end())
	 		{	set <string> value = iter->second;
	 	        for (sit iter2= value.begin(); iter2 != value.end(); iter2++)
	 	     		 {  cout << (iter)->first << " is "<< (*iter2) << endl;} 
	 	        //
	 		}
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


void printStack(stack<string> parserstack)
{
	stack <string> temp = parserstack;

	while(!temp.empty())
	{
		cout<<temp.top()<<" ";
		temp.pop();
	}
	cout<<endl;
	return;

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
	//cout<<"prod"<<prod;

	int j=0;
	set<string> result; 

	int firstloc = 0;
	int secloc = getNextDotLocation(firstloc,prod);
	//if(secloc<0)
		//cout<<"error"<<endl;
	string token = getStringBetweenTwoDots(firstloc,secloc,prod);

	if(token=="" || secloc<0)
	{
		result.insert("e");
		return result;
	}
	
	//cout<<"token"<<token<<endl;
	firstloc = secloc;
	
	if(terminals.find(token)==terminals.end())
	{
		if(firstSet[token].find("e")!=firstSet[token].end())
		{
			//cout << "sdasd" << endl;

			result = appendSets(firstSet[token], giveFirst(prod.substr(secloc, prod.length()-secloc)));
			
			return result;
		}
		else
		{
			return firstSet[token];
		}
	}	

	else{
		result.insert(token);
		return result;
	}

}


void Parser::createTable() {
	for(pit iter = grammar.begin(); iter != grammar.end(); iter++ ) {
 		
 		for(sit it=(iter->second).begin();it!=(iter->second).end();it++) {
 			//cout<<*it<<":\n";
 			set<string> firstSymbols=giveFirst(*it);
 			//printSet(firstSymbols);
 			for(sit fs=firstSymbols.begin();fs!=firstSymbols.end();fs++) {
 				//cout<<*it<<"adding"<<endl;
 				if(*fs=="e")
 					continue;
 				if(parsing_table.find(make_pair(iter->first,*fs))==parsing_table.end())
 				parsing_table[make_pair(iter->first,*fs)]=*it;
 				else
 					{
 						cout << iter->first << " " << *fs << "  " << endl;
 						cout << "New prod " << *it << endl;
 						cout << "Old prod" << parsing_table[make_pair(iter->first,*fs)] <<endl;
 						cout << "Grammar is not LL(1)." << endl;
 						exit(1);
 					}
 			}

 			if(firstSymbols.find("e")!=firstSymbols.end()) 
 			{
 				for(sit fs=followSet[iter->first].begin(); fs!=followSet[iter->first].end(); fs++)
 				{	
 					//cout<<*it<<"adding2"<<endl;
 					if(parsing_table.find(make_pair(iter->first,*fs))==parsing_table.end())
 					parsing_table[make_pair(iter->first,*fs)]=*it;
 					else
 					{
 						cout << iter->first << " " << *fs << "  " << endl;
 						cout << "New prod " << *it << endl;
 						cout << "Old prod" << parsing_table[make_pair(iter->first,*fs)] <<endl;
 						cout << "Grammar is not LL(1)." << endl;
 						exit(1);
 					}
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
	//for(int i=1;i<=2;i++) {
		//cout << ind[i]<<" ";
	//}
	//cout<<"\n";
	for(int i=1;i<=nonterminals.size();i++) {
		for(int j=1;j<i;j++) {
			for(sit it=grammar[ind[i]].begin();it!=grammar[ind[i]].end();it++) {
				int len=ind[j].size()+2;
				string str=*it;
				if(str.substr(0,len)==("."+ind[j]+".")) {
					grammar[ind[i]].erase(it);
					for(sit it2=grammar[ind[j]].begin();it2!=grammar[ind[j]].end();it2++) {
						string temp=(*it2)+str.substr(len,str.size()-len);
						grammar[ind[i]].insert(temp);
					}
				}
			}
		}
		//printMap(grammar);cout<<"\n";
		//check if Ai has left recursion
		int len=ind[i].size()+2;
		for(sit it=grammar[ind[i]].begin();it!=grammar[ind[i]].end();it++) {
			string str=*it;
			if(str.substr(0,len)==("."+ind[i]+".")) {
				goto lr_eliminate;
			}
		}
		continue;

		lr_eliminate:
		//eliminate left-recursion from among the Ai productions
		string newNonTerm="."+ind[i]+"1"+".";
		//int len=ind[i].size()+2;
		set<string> upr,lpr;
		bool flag=true;
		for(sit it=grammar[ind[i]].begin();it!=grammar[ind[i]].end();it++) {
			string str=*it;
			if(str.substr(0,len)==("."+ind[i]+".")) {
				lpr.insert("."+str.substr(len,str.size()-len)+ind[i]+"1"+".");
			} else {
				upr.insert(str+ind[i]+"1"+".");
			}
		}
		lpr.insert(".e.");

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
		//cout<<"calling "<<iter->first<<endl;
 		getFirstSet(iter->first);
 		//cout<<endl;
 	}

 	for(sit iter = terminals.begin(); iter != terminals.end(); iter++ ) 
	{
		//cout<<"calling "<<*iter<<endl;
 		getFirstSet(*iter);
 		//cout<<endl;
 	}
 	cout<<"Firstset is:"<<endl;
	printMap(firstSet);
	cout<<endl;

 	

 	for(map<string, set<string> >::iterator iter = grammar.begin(); iter != grammar.end(); iter++ ) 
	{
 		getFollowSet(iter->first);

 	}

 	
	/*for debuggin*/
	//cout<<"follow overlap printing"<<endl;
 	//printMap(followOverlap);

	for(pit iter = followOverlap.begin(); iter != followOverlap.end(); iter++ ) 
	{
		//cout<<"iter first"<<iter->first<<endl;
		//printSet(iter->second);
		/* check if iter is A check if followOverlap[something]=A so that you update follow(A) before adding everything 
		 in follw(A) to B */
		
		if((iter->second).empty())
			continue;

		//cout<<"fololow ovcerlap\n";

		//printMap(followOverlap);
		for(pit iter2 = followOverlap.begin(); iter2 != followOverlap.end(); iter2++ ) 
		{
			set<string> overlapset = followOverlap[(iter2)->first];

			// iterate through the set to check if iter is present i.e if followOverlap[C]=A
			for (sit iter4=overlapset.begin(); iter4!=overlapset.end(); ++iter4)
			{
				if((iter->first)==(*iter4))
				{
					// copy everything in follow of iter2 to follow of iter i.e from folow of C to A
					string temp= iter2->first;
					//cout<<"iter2:"<<iter2->first<<endl;
					//cout<<"iter:"<<iter->first<<endl;
					set<string> fromset= followSet[temp];
					// set<string> tempset;
					// for (std::set<string>::iterator iter3=fromset.begin(); iter3!=fromset.end(); ++iter3)
					// 	tempset.insert(*iter3);
					//cout<<"inserting"<<endl;
					//cout<<"iter first: "<<iter->first<<endl;
					//cout<<"fromset: ";
					//cout << "ser" <<endl;
					//pit it4=followSet.find(iter->first);
					pit iter10=followSet.find(iter->first);
					if(iter10!=followSet.end())
					iter10->second.insert(fromset.begin(), fromset.end());
					//cout << "iter->secondset" << endl;
					//printSet(iter10->second);
					//followSet.insert(std::pair<string, set<string> >(iter->first, fromset));
				}

			}

		}

		string temp2= iter->first;

		set<string> copyset= followSet[temp2];
		set<string> overlapset= followOverlap[temp2];		
		//cout << "copyset" << iter->first << endl;
		//printSet(copyset);

		// loop through overlapset of A and insert followset of A into each element
		for(sit iter4=overlapset.begin(); iter4!=overlapset.end(); ++iter4)
			{		
				pit it5=followSet.find(*iter4);
				//cout << "iter4 " <<  *iter4 << endl;

				//sit inserter = followSet[*iter4];
			/*if(it5!=followSet.end())
				printSet(it5->second);*/
			
				//cout <<  *iter4 << "Not found" << endl;
				if(it5!=followSet.end())
					(it5->second).insert(copyset.begin(), copyset.end());
				//followSet.insert(std::pair<string, set<string> >((*iter4), copyset));

					//cout<<"iter first: "<<iter->first<<endl;
					//cout<<"copyset: ";
					//printSet(copyset);
				//printSet(prodnfollowset);
			}

	}

	cout<<"Followset is:"<<endl;
	printFollowMap(followSet);
	cout<<endl;



	 return;


 }


void Parser::getFirstSet(string nonterm)
{
	set<string> productions = grammar[nonterm];
 	set<string> symbols;

	if(terminals.find(nonterm) != terminals.end())
			{
				symbols.insert(nonterm);
				firstSet[nonterm]=symbols;
				//cout<<"added "<<nonterm<<endl;
				return;

			}

	
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
				//cout<<"added "<<term<<endl;
				continue;

			}


			int i=0;
 			int len= (*it).size();
 			int prevdot = 0;
 			int seconddot;
			while(i<len)
 			{
 				//cout<<"i:"<<i<<endl;
 				string str= (*it);
 				//cout<<"string is:"<<str<<endl;

 				//cout<<"prevdot is:"<<prevdot<<endl;

 				//int seconddot = str.find(".",prevdot+1);
 				seconddot = getNextDotLocation(prevdot,str);
 				if(seconddot<0)
 					break;


 				//cout<<"second dot:"<<seconddot<<endl;
 				//cout<<"dotsplit"<<endl;


 				string s= getStringBetweenTwoDots(prevdot,seconddot, str);
 				//str.substr(prevdot+1,seconddot-prevdot-1);
 				//cout<<"split string is:"<<s<<endl;

				// check for terminals if found add and break
				if(terminals.find(s) != terminals.end())
				{
					symbols.insert(s);
					//cout<<"foudn in terminals so added: "<<s<<endl;
					break;
				}				
				

				//  first check if the firstset is already computed else compute it
				map<string, set<string> >::iterator mapit = firstSet.find(s);
				//cout<<"Searching for:"<<s<<"in already computed"<<endl;
				if(mapit == firstSet.end())
 					{
						getFirstSet(s);
	 				}	
	 				//cout<<"reached"<<endl;
 					set<string> prdfirstSet = firstSet[s];
 					//printSet(prdfirstSet);
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
					//cout<<"added e to symbols"<<endl;

			}
	}

	firstSet[nonterm]=symbols;

 }


void Parser::getFollowSet(string nonterm)
{
	//cout<<"nonterminal: "<<nonterm<<endl;

	set<string> symbols;
	// if the non-term is the start symbol add $ & return

	if(nonterm=="S")
	{
		symbols.insert("$");
	}

	set<string> productions = grammar[nonterm];
	//printSet(productions);
	//cout<<endl;

	set<string> overlap;


	// iterarte through all the productions
	for (set<string>::iterator it=productions.begin(); it!=productions.end(); ++it)
	{

		int i=0;
 		int len= (*it).size();
 		i=len-1;

 		//  ex: take prdtn X-> GhB
 		string str= (*it);
 		//cout<<"consider prdtn: " <<str<<endl;

 		while(i>=0)
 		{
 			
 			//cout<<"i:"<<i<<endl;
 			int pos= getNextDotReverse(i,str);
 			//cout<<"nextdotrev(pos): "<<pos<<endl;


 			if(pos < 0)
 				break;

 			string s= getStringBetweenTwoDots(pos,i,str); // get B
			int flag = 1;

			//cout<<" Adding firstsets to :"<<s<<endl;

			int curdot=i;
			while(flag==1)
			{
				flag=0;
				int nextdot= getNextDotLocation(curdot,str);
				//cout<<"nextdot"<<nextdot<<endl;
		
				if(nextdot<0)
					break;

				string next= getStringBetweenTwoDots(curdot,nextdot,str);
				//cout<<"adding firstsets of following"<<endl;
				//cout<<"next: "<<next<<endl;

				set<string> prodfirstSet = firstSet[next];
				//printSet (prodfirstSet);

	 			set<string> followseth;  //
					for (std::set<string>::iterator iter=prodfirstSet.begin(); iter!=prodfirstSet.end(); ++iter)
						{
							string temp=(*iter);
							//cout<<"Temp: "<<temp<<endl;
							if(strcmp(temp.c_str(),"e")!=0)
								followseth.insert(*iter);
							else
								flag=1;
						}

				curdot=nextdot;//

				set<string> temp = followSet[s];
				temp = appendSets(temp, followseth);
				pit it2=followSet.find(s);
				it2->second=temp;
				//followSet.insert(std::pair<string, set<string> > (s,temp) );

			}					  
			i=pos;		
	 	}

	 	i=len-1;
	 	int curpos= getNextDotReverse(i,str);
	 	string last= getStringBetweenTwoDots(curpos,i,str); // get B
	 	
	 	if(terminals.find(last) == terminals.end() && last!="e")
		{
			//cout<<"last is"<<last<<endl;
			overlap.insert(last);
		}
	 		

	 	int prevdot= getNextDotReverse(curpos,str);
	 	string prev = getStringBetweenTwoDots(prevdot,curpos,str);
	 	curpos= prevdot;

	 	while(checkepsfirst(last))
	 	{
	 		//cout<<"prev is"<<prev<<endl;
	 		overlap.insert(prev);
	 		last=prev;
	 		prevdot= getNextDotReverse(curpos,str);
	 		if(prevdot<0) break;
	 		prev = getStringBetweenTwoDots(prevdot,curpos,str);
	 		curpos=prevdot;
	 	}
	}
	//cout<<"printint set overlap "<<nonterm<<endl;
	//printSet(overlap);
	

	set<string> temp = followOverlap[nonterm];
	//cout<<"old temp: "<<endl;
	//printSet(temp);
	//cout<<"overlap:"<<endl;
	//printSet(overlap);

	temp.insert(overlap.begin(), overlap.end());
	//temp = appendSets(temp, overlap);
	//cout<<"new temp: "<<endl;
	//printSet(temp);
	pit it3=followOverlap.find(nonterm);
	it3->second=temp;

	//followOverlap.insert(std::pair<string, set<string> > (nonterm,temp) );
	//followOverlap.insert(std::pair<string, set<string> > (nonterm, overlap));








	temp = followSet[nonterm];
	//temp = appendSets(temp, symbols);
	//cout<<"oldtemp"<<endl;
	//printSet(temp);
	//cout<<"symbols:"<<endl;
	//printSet(symbols);
	temp.insert(symbols.begin(), symbols.end());
	//cout<<"newtemp";
	//printSet(temp);
	pit it1=followSet.find(nonterm);
	it1->second=temp;
	//followSet.insert(std::pair<string, set<string> > (nonterm,temp) );
	//followSet.insert(std::pair <string, set<string> > (nonterm, symbols));


	//cout<<"printing aftert inserting:"<<endl;
	//printMap(followSet);
	//cout<<"done"<<endl;
}


void Parser::parse(string tokensfile)
{

	parserstack.push("$");
	parserstack.push("S");

	//printStack(parserstack);
	cout<<"Stack contents:"<<endl;

	string x,a;

	ifstream tokensfilestream(tokensfile.c_str());
	
	if (tokensfilestream.is_open())
  	{
  		getline(tokensfilestream, a);
		while (!parserstack.empty())
		{
			printStack(parserstack);

			x = parserstack.top();
			//cout << x<< endl;
			parserstack.pop();

			
			//cout << a << endl;
			//cout << x << " " <<   a << endl;
			if (tokensfilestream.eof())
				a = "$";

			if(terminals.find(x)!=terminals.end() || !strcmp(x.c_str(),"$"))
			{
				if(x==a)
				{
					//cout << "a: " << a << endl;
					getline(tokensfilestream, a);

					continue;
				}
				else
				{
					cout << "Syntax error at " << a << endl;
					return ;
				}
			}
			else
			{
				string value = parsing_table[make_pair(x,a)];

				if(parsing_table.find(make_pair(x,a)) == parsing_table.end()) {
					
					cout << "Syntax error at " << a  << endl;
				 	return ;
				} else {
					string value = parsing_table[make_pair(x,a)];
					vector<string> nterms = tokenize(value,".");
					for(int i=nterms.size()-1;i>=0;i--) 
					{
						parserstack.push(nterms[i]);
					}
				}
			}

		}
		
		if (!tokensfilestream.eof())
		{
			cout << "Syntax error" << endl;
			return ;
		}
		cout << codefile<< " has been parsed successfully." << endl;
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
	int newnextdot = str.find(".",newcurdot+1);
	if(newnextdot == -1)
		return -1;
	else
		{int oldnextdot = str.length() - str.find(".",newcurdot+1) -1;
		return oldnextdot;}

}

bool Parser::checkepsfirst(string nonterm)
{
	set<string> prdfirstSet = firstSet[nonterm];
 						set<string>::iterator setit= prdfirstSet.find("e");

 						if(setit == prdfirstSet.end())
							return false;
						else
							return true;
}
