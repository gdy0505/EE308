#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <string>
#include<stack>

using namespace std;

bool checkOpen(ifstream &filename){
 	if (filename.fail()) // check for successful open
 	{
		 cout << "\nThe file was not successfully opened"
			  << "\nPlease check that the file currently exists."
	 		  << endl;
 	return false;
 	}
 	return true;
}


int count_total_num(ifstream &filename,int total_num){
	string line;
	while(getline(filename, line)){
		if(((line.find("auto"))!=string::npos)||((line.find("break"))!=string::npos)||((line.find("case"))!=string::npos)||((line.find("char"))!=string::npos)
				||((line.find("const"))!=string::npos)||((line.find("continue"))!=string::npos)||((line.find("default"))!=string::npos)||((line.find("do"))!=string::npos)
				||((line.find("double"))!=string::npos)||((line.find("else"))!=string::npos)||((line.find("enum"))!=string::npos)||((line.find("extern"))!=string::npos)
				||((line.find("float"))!=string::npos)||((line.find("for"))!=string::npos)||((line.find("goto"))!=string::npos)||((line.find("if"))!=string::npos)
				||((line.find("int"))!=string::npos)||((line.find("long"))!=string::npos)||((line.find("register"))!=string::npos)||((line.find("return"))!=string::npos)
				||((line.find("short"))!=string::npos)||((line.find("signed"))!=string::npos)||((line.find("sizeof"))!=string::npos)||((line.find("static"))!=string::npos)
				||((line.find("struct"))!=string::npos)||((line.find("switch"))!=string::npos)||((line.find("typedef"))!=string::npos)||((line.find("union"))!=string::npos)
				||((line.find("unsigned"))!=string::npos)||((line.find("void"))!=string::npos)||((line.find("volatile"))!=string::npos)||((line.find("while"))!=string::npos))
				{
					total_num++;
				}
				if(((line.find("else"))!=string::npos)&&((line.find("if"))!=string::npos)){
					total_num++;
				}
		}
		cout << "total num : " << total_num << endl;
		
		//Clear the result of this read, so that the pointer back to the beginning
		filename.clear();
		filename.seekg(0,ios::beg);	
		
		return total_num;		
}

int count_switch_num(ifstream &filename,int switch_num){
	string line;
   	while(getline(filename, line)){
        if(line.find("switch")!=string::npos){
        	switch_num++;
		}
	}
    cout << "switch num : " << switch_num << endl;
	//Clear the result of this read, so that the pointer back to the beginning 
    filename.clear();
	filename.seekg(0,ios::beg);	
    return switch_num;
}

int count_case_num(ifstream &filename,int case_num){
	string line;
	int count_switch_num = 0;
	cout << "case num : ";
   	while(getline(filename, line)){
        if(line.find("switch")!=string::npos){
        	count_switch_num++;
        	case_num = 0;
        	while(getline(filename, line)){
        		if(line.find("case")!=string::npos){
	        		case_num++;
				}else if (line.find("default")!=string::npos){
					cout << case_num << " ";
					break;
				}
			}
		}
	}
	
    //Clear the result of this read, so that the pointer back to the beginning
    filename.clear();
	filename.seekg(0,ios::beg);	
	
    return case_num;
}

int count_if_elseif_if_num(ifstream &filename, int if_else_num, int if_elseif_if_num){
	//define a stack
	stack<int> s;
	string line;
   	while(getline(filename, line)){
   		if(line.find("else if")!=string::npos){
   			s.push(2);
   		}else if(line.find("if")!=string::npos){
   			s.push(1);
   		}else if(line.find("else")!=string::npos){
            if(s.top() == 1){
                s.pop();
                if_else_num++;
                continue;
            }
            while(s.top() == 2) {
                s.pop();
            }
            s.pop();
            if_elseif_if_num++;
		}
	}
	cout << endl;
	cout << "if else num : " << if_else_num << endl;
	cout << "if else-if else num : " << if_elseif_if_num << endl;
	
	//Clear the result of this read, so that the pointer back to the beginning
	filename.clear();
	filename.seekg(0,ios::beg);
}


int main()
{
	//open the file
	ifstream readfile; 
	string file_load;
 	cout << "\nplease input the load of the file : ";
 	cin >> file_load;
 	readfile.open(file_load.c_str()); 
	
	
	//define the level
	cout << "please input the level of task ( from level: 1--4 )"  << endl;
 	int num;
	cin >> num;
	
	//define the total number
	int total_num = 0;

	//define the switch number
	int switch_num = 0;

	//define the case number
	int case_num = 0;
	
	//define the if-else number
	int if_else_num = 0;
	
	//define the if-elseif-else number
	int if_elseif_if_num = 0;
 	
 	//check the file is opened successfully or not
 	int a = checkOpen(readfile);
 	
 	
 	//Perform different operations according to different levels
 	switch(num){
 		//If the program is in level 1 state
 		case 1:
 			total_num = count_total_num(readfile, total_num); 		
 			break;
 		//If the program is in level 2 state
 		case 2:
 			total_num = count_total_num(readfile, total_num);
 			switch_num = count_switch_num(readfile, switch_num);
 			case_num = count_case_num(readfile, case_num);
 			break;
 		//If the program is in level 3 state
 		case 3:
 			total_num = count_total_num(readfile,total_num);
 			switch_num = count_switch_num(readfile, switch_num);
 			case_num = count_case_num(readfile, case_num);
 			break;
 		//If the program is in level 4 state
 		case 4:
 			total_num = count_total_num(readfile,total_num);
 			switch_num = count_switch_num(readfile, switch_num);
 			case_num = count_case_num(readfile, case_num);
 			count_if_elseif_if_num(readfile, if_else_num, if_elseif_if_num);
 			break;
 		default:
 			cout << "sorry, the level you have input is not exist" << endl;
 	}
 	return 0;
 	
} 
