#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>
#include <sstream>

#define nl cout<<"\n"

map<int,set<string>> hash_map;

void printfMIPSCode(int index,string str) {

	vector <string> cds;
	string temp;
	stringstream s1 (str);
	while(s1>> temp)
		cds.push_back(temp);

	switch(index) {
		case 1:		//x := y op z
			cout << "load "<<cds[2]<<" into reg1\n";
			cout << "load "<<cds[4]<<" into reg2\n";
			cout << "opc reg3, reg1, reg2\n";
			cout << "store reg3 into "<<cds[0]<<endl;

		case 2:		//x := -y
			cout << "load "<<cds[2]<<" into reg1\n";
			cout << "neg reg2,reg1";
			cout << "reg2 into "<<cds[0];

 		case 3:		//x := y
 			cout << "load "<<cds[2]<<" into reg1\n";
 			cout << "reg1 into "<<cds[0];

		case 4:		//goto label
			cout<<"j "<<cds[1];

		case 5:		//if x relop val goto label
			cout << "load "<<cds[1]<<" into reg1\n";
			cout << "load "<<cds[3]<<" into reg2\n";
			cout << "bcc reg2, reg1 " << cds[5];nl;
 
		case 6:		//label L

		case 7:		//x := y[i]

		case 8:		//x[i] := y

		case 9:		//x := & y

		case 10:	//x := *y

		case 11:	//*x := y

		case 12:	//enter f
			cout << "sw $fp, -4($sp)";nl;
			cout << "sw $ra, -8($sp)";nl;
			cout << "la $fp, 0($sp)";nl;
			cout << "la $sp, -n($sp)";nl;
			cout << "save all registers used";

		case 13:	//leave f
			cout << "restore callee save registers";

		case 14:	//param x
			cout << "load "<<cds[1]<<" into reg1\n";
			cout << "sw reg1, -4($sp)";nl;
			cout << "la $sp, -4($sp)";nl;

		case 15:	//call p, n
			cout << "jal "<<cds[1];nl;
			cout << "la $sp, k($sp)";

		case 16:	//return
			cout << "la $sp, 0($fp)";nl;
			cout << "lw $ra, -8($sp)";nl;
			cout << "lw $fp, -4($sp)";nl;
			cout << "jr $ra";nl;

		case 17:	//return x
			cout << "load x into $v0";nl;
			cout << "la $sp, 0($fp)";nl;
			cout << "lw $ra, -8($sp)";nl;
			cout << "lw $fp, -4($sp)";nl;
			cout << "jr $ra";nl;

		case 18:	//retrieve x
			cout << "store $v0 into "<<cds[1];nl;

		default:
			cout<<"error\n";

	}	
}

int main() {
	ifstream fin("addr3.txt");
	ifstream indf("indices.txt");
	string str = getline(fin);
	string ind = geitline(indf);
	return 0;
}