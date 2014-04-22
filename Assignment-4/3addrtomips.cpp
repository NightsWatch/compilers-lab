#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>

#define nl cout<<"\n"

using namespace std;

//map< int,set<string> > hash_map;

bool isParam(string line){
    if(line[0]-'0'>=0 && line[0]-'0'<=9) return true;
    return false;
}   

void printfMIPSCode(int index,string str) {

	vector <string> cds;
	string temp;
	stringstream s1 (str);
	while(s1>> temp)
		cds.push_back(temp);

	switch(index) {
		case 1:		//x := y op z
		{
			//cout<<"sadad: "<<cds[3];nl;
			if(isParam(cds[2])) {
				cout << "li "<<"$r, "<<cds[2];nl;
			} else {
				cout << "lw "<<"$r, "<<cds[2];nl;
			}
			if(isParam(cds[4])) {
				cout << "li "<<"$v0, "<<cds[4];nl;
			} else {
				cout << "lw "<<"$v0, "<<cds[4];nl;
			}
			if(cds[3]=="+") {
				cout << "add $v0, $r, $v0";nl;
			} else if(cds[3]=="-") {
				//cout<<"sada";
				cout << "sub $v0, $r, $v0";nl;
			} else if(cds[3]=="*") {
				cout << "mul $v0, $r, $v0";nl;
			} else if(cds[3]=="/") {
				cout << "div $v0, $r, $v0";nl;
			}
			cout << "sw $v0, "<<cds[0];nl;
			return;
		}
		//break;

		case 2:		//x := -y
		{
			string str=cds[2].substr(1,cds[2].size()-1);
			if(isParam(str)) {
				cout << "li "<<"$r, "<<str;nl;
			} else {
				cout << "lw "<<"$r, "<<str;nl;
			}
			cout << "neg $v0, $r";nl;
			cout << "sw $v0, "<<cds[0];nl;
			return;
		}
		//break;
 		case 3:		//x := y
 		{
 			//cout<<cds[2];nl;
 			if(isParam(cds[2])) {
				cout << "li "<<"$r, "<<cds[2];nl;
			} else {
				cout << "lw "<<"$r, "<<cds[2];nl;
			}
 			cout << "sw $r, "<<cds[0];nl;
 			return;
 		}
 		//break;
		case 4:		//goto label
		{
			cout<<"j "<<cds[1];
			return;
		}

		case 5:		//if x relop val goto label
		{
			if(isParam(cds[1])) {
				cout << "li "<<"$r, "<<cds[1];nl;
			} else {
				cout << "lw "<<"$r, "<<cds[1];nl;
			}
			//cout << "load "<<cds[1]<<" into reg1\n";
			if(isParam(cds[3])) {
				cout << "li "<<"$v0, "<<cds[3];nl;
			} else {
				cout << "lw "<<"$v0, "<<cds[3];nl;
			}
			//cout << "load "<<cds[3]<<" into reg2\n";
			string ccd=cds[2];
			//switch(ccd) {
			if(ccd.compare("<=")==0) {
				cout << "ble $r, $v0, "<<cds[5];nl;
			}
			else if(ccd.compare("==")==0) {
				cout << "beq $r, $v0, "<<cds[5];nl;
			}
			else if(ccd.compare("<")==0) {
				cout << "blt $r, $v0, "<<cds[5];nl;
			}
			else if(ccd.compare(">")==0) {
				cout << "bgt $r, $v0, "<<cds[5];nl;
			}
			else if(ccd.compare("!=")==0) {
				cout << "bne $r, $v0, "<<cds[5];nl;
			}
			else if(ccd.compare(">=")==0) {
				cout << "bge $r, $v0, "<<cds[5];nl;
			}
			//}
			//cout << "bcc reg2, reg1 " << cds[5];nl;
			return;
		}
 
		case 6:		//label L
			cout<<"L:";nl;
		case 7:		//x := y[i]

		case 8:		//x[i] := y

		case 9:		//x := & y

		case 10:	//x := *y

		case 11:	//*x := y

		case 12:	//enter f
		{
			cout << cds[1]<<"_entry:";nl;
			cout << "sw $fp, -4($sp)";nl;
			cout << "sw $ra, -8($sp)";nl;
			cout << "la $fp, 0($sp)";nl;
			//cout << "la $sp, -n($sp)";nl;
			//cout << "save all registers used";
			return;
		}

		case 13:	//leave f
			//cout << "restore callee save registers";
			return;

		case 14:	//param x
		{
			if(isParam(cds[1])) {
				cout << "li "<<"$r, "<<cds[1];nl;
			} else {
				cout << "lw "<<"$r, "<<cds[1];nl;
			}
			//cout << "load "<<cds[1]<<" into reg1\n";
			cout << "sw $r, -4($sp)";nl;
			cout << "la $sp, -4($sp)";nl;
			return;
		}

		case 15:	//call p, n
		{
			cout << "jal "<<cds[1];nl;
			cout << "la $sp, "<<4*atoi(cds[2].c_str())<<"($sp)";nl;
			//cout << "la $sp, -n($sp)";nl;
			return;
		}

		case 16:	//return
		{
			cout << "la $sp, 0($fp)";nl;
			cout << "lw $ra, -8($sp)";nl;
			cout << "lw $fp, -4($sp)";nl;
			cout << "jr $ra";nl;
			return;
		}

		case 17:	//return x
		{
			//cout << "load x into $v0";nl;
			cout << "lw $v0, " <<cds[1];nl;
			cout << "la $sp, 0($fp)";nl;
			cout << "lw $ra, -8($sp)";nl;
			cout << "lw $fp, -4($sp)";nl;
			cout << "jr $ra";nl;
			return;
		}

		case 18:	//retrieve x
		{
			cout << "sw $v0, " <<cds[1];nl;
			return;
		}

		default:
			cout<<"error\n";

	}	
}

int main() {
	ifstream fin("mips");
	ifstream indf("indices.txt");
	string str;
	while(getline(fin,str)) {
		 
		//getline(fin,str);
		int ind;
		indf>>ind;
		//cout<<ind;nl;
		//cout<<str;nl;

		//int index=atoi(ind.c_str());

		printfMIPSCode(ind,str);
	}
	return 0;
}