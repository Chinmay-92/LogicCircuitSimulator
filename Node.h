#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
using namespace std;

class Node {

public:
	string name;
	string type;
	vector<string> input;
	vector<string> output;
	bool state;					//logic value
public:
	Node(){

	}
    Node(string nm,string t)
	{
		name=nm;
		type=t;
	}
	inline std::string trim(std::string& str)
	{
    str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
    return str;
	}
	void deleteNode(){
	vector<string> output;

 	vector<string>().swap(output);			//delete all output wires
 }
 void setInput(string inputs){
	vector<string> input;

 	(*this).input.push_back(inputs);
 }
 void setInput2(string inputs1,string inputs2){
	vector<string> input;

 	(*this).input.push_back(inputs1);
 	(*this).input.push_back(inputs2);
 }
 void setOutput(string outputs){
	vector<string> output;

 	(*this).output.push_back(outputs);
 }
 string getOutput(){
 	return trim((*this).output[0]);
 }
 string getInput(){
 	if((*this).input.size() > 1)
 	return (*this).input[0] + ","+ (*this).input[1];
	else
 	return (*this).input[0] ;
 }
 bool generateStatus(map<string,bool> inputsMap,map<string,bool> outputsMap){
 	/*
	 	a | b = a or b
		a !| b = a nor b
		a & b = a and b
		a !& b = a nand b
		a ^ b = a xor b
		a !^ b = a xnor b
		!a = not a
	*/
 	//cout << type.find("NAND") << "\n";
	bool isOutput=false;
	
 	if(type.find("INPUT") != std::string::npos){
 		//cout << "here";
 		bool input;
 		string ip = (*this).input[0];
		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip.find(it->first)!= std::string::npos){
				input = it->second;
			}
		}
 		//istringstream(ip) >> input;
 		state = input;
 		//cout << " state: " <<state;
 	}
 	else if (type.find("NOT") != std::string::npos)
 	{
 		//cout <<"inside NOT";
 		bool input;
 		bool isInput=false;
 		string ip = (*this).input[0];
		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip.find(it->first)!= std::string::npos){
				input = it->second;
				isInput = true;
			}
		}
		if(isInput){
			state = !input;
		}
			{
				vector<string> v;
				for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
				v.push_back(it->first);
				if(ip.find(it->first)!= std::string::npos){
					input = it->second;
					isOutput = true;
				}
			}
			if(isOutput){
				state = !input;
			}
		}
		//cout << "state after NOT :: "<<state;
 		
 	}
 	else if (type.find("OR") == 0)
 	{
 		bool input1;
 		bool input2;
 		//cout << "inside OR \n";
 		string ip1=(*this).input[0];
		bool isInput=false;
 		string ip2=(*this).input[1];

 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isInput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isInput = true;
			}
		}

		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isOutput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isOutput = true;
			}
		}


 		state = input1 | input2;
 		//cout << "state :: "<<state;
 	}
 	else if (type.find("NOR") == 0)
 	{
 		bool input1;
 		bool input2;
 		//cout << "inside NAND \n";
 		string ip1=(*this).input[0];
		bool isInput=false;
 		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isInput = true;
			}
		}
		string ip2=(*this).input[1];

 		
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isInput = true;
			}
		}
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isOutput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isOutput = true;
			}
		}
		state = !(input1||input2);
		//cout << "state :: "<<state;
 	}else if (type.find("AND") == 0)
 	{
 		bool input1;
 		bool input2;
 		//cout << "inside NAND \n";
 		string ip1=(*this).input[0];
		bool isInput=false;
 		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isInput = true;
			}
		}
		string ip2=(*this).input[1];

 		
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isInput = true;
			}
		}
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isOutput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isOutput = true;
			}
		}
 		state = input1 & input2;
 		//cout << "state :: "<<state;
 	}else if (type.find("NAND") == 0)
 	{
 		bool input1;
 		bool input2;
 		//cout << "inside NAND \n";
 		string ip1=(*this).input[0];
		bool isInput=false;
 		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isInput = true;
			}
		}
		string ip2=(*this).input[1];

 		
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isInput = true;
			}
		}
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isOutput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isOutput = true;
			}
		}
 		state = !(input1 && input2);
 		//cout << "state :: "<<state;
 	}else if (type.find("XOR") == 0)
 	{
 		bool input1;
 		bool input2;
 		//cout << "inside NAND \n";
 		string ip1=(*this).input[0];
		bool isInput=false;
 		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isInput = true;
			}
		}
		string ip2=(*this).input[1];

 		
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isInput = true;
			}
		}
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isOutput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isOutput = true;
			}
		}
 		state = input1 ^ input2;
 	}else if (type.find("XNOR") != std::string::npos)
 	{
 		bool input1;
 		bool input2;
 		//cout << "inside NAND \n";
 		string ip1=(*this).input[0];
		bool isInput=false;
 		
 		vector<string> v;
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isInput = true;
			}
		}
		string ip2=(*this).input[1];

 		
		for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isInput = true;
			}
		}
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip1.find(it->first)!= std::string::npos){
				input1 = it->second;
				isOutput = true;
			}
		}
		
 		
		for(map<string,bool>::iterator it = outputsMap.begin(); it != outputsMap.end(); ++it) {
			v.push_back(it->first);
			if(ip2.find(it->first)!= std::string::npos){
				input2 = it->second;
				isOutput = true;
			}
		}
 		state = input1 == input2;
 	}
 	return state;
 }
};
