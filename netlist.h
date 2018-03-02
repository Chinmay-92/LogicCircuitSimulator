#include <algorithm>
#include <sstream>
#include <iterator>
#include <map>
using namespace std;

class netlist {
map<string,bool> inputsMap;
map<string,bool> outputsMap;
vector<string>inputValues;
public:
	vector<Node*> nodes;	    

	netlist(){

	}

public:
	int CountWords(string myString)
	{
	    int numspaces = 0;
	    char nextChar;
	    // checks each character in the string
	    for (int i = 0; i < int(myString.length()); i++) {
	        nextChar = myString.at(i); // gets a character
	        if (isspace(myString[i]))
	            numspaces++;
	    }
	    // cout << "\nThere are " << numspaces << " words in this string.";
	    return numspaces;
	};
	inline std::string trim(std::string& str)
	{
	   str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
	    str.erase(str.find_last_not_of(' ')+1);         //surfixing spaces
	    return str;
	};

	bool ValueCmp(Node* a, Node* b)
	{
	    return !(*a).getInput().compare( (*b).getInput());
	};
	int updateNetlist(const char* fname,const char* ipfname)
	{
	    //const char* fname = "c17.bench";
	    ifstream file(fname);
	    ifstream infile(ipfname);
		

	    vector<string> inputVectors;
	    vector<string> outputVectors;
	    vector<string> inputs;
	    vector<string> outputs;

	    string result;
	    string line;
	    string benchFileName;
	    
		while (infile.peek() != EOF) {
	        getline(infile, line);
	        inputValues.push_back(trim(line));
	        /*
	        for(int i=0;i<line.size();i++){
	        	char ip=line.at(i);
	        	inputValues.push_back(ip);
	        	cout << ip << "::";
	    	}
	    	*/
		}

	    while (file.peek() != EOF) {
	        getline(file, line);
	        // cout << line << '\n';
	        result = result + line;

	        int index = 0;
	        std::stringstream ss(line);
	        std::string item;
	        if (line.length() == 0) {
	            continue;
	        }
	        while (std::getline(ss, item, '#') && item.size() > 0) {
	            if (line[0] == '#') {
	                int count = CountWords(item);
	                if (count == 1) {
	                    benchFileName = item;
	                }
	                else if (count == 2 && item.find("inputs") != std::string::npos) {
	                    string delimiter = "inputs";
	                    string token = item.substr(0, item.find(delimiter)); // token is "scott"
	                }
	                else if (count == 2 && item.find("outputs") != std::string::npos) {
	                    string delimiter = "outputs";
	                    string token = item.substr(0, item.find(delimiter)); // token is "scott"
	                    outputs.push_back(token);
	                }
	            }
	            else {

	                if (item.find("INPUT") != std::string::npos) {
	                    string ips1 = item.substr(item.find('(') + 1);
	                    ips1 = ips1.substr(0, ips1.find(")"));

	                    //cout << ips1 + '\n';
	                    //string type="INPUT";
	                    //Node* n = new Node(benchFileName, type);
	                    //(*n).state=0;
	                    inputVectors.push_back(ips1);
	                      // first insert function version (single parameter):
  						inputsMap.insert ( std::pair<string,bool>(ips1,0) );			//default value here
	                    //nodes.push_back(n);
	                }
	                else if (item.find("OUTPUT") != std::string::npos) {
	                    string ips1 = item.substr(item.find('(') + 1);
	                    ips1 = ips1.substr(0, ips1.find(")"));

	                    // cout << ips1 + '\n';
	                    outputVectors.push_back(ips1);
	                }
	                else if (item.find("=") != std::string::npos) {
	                    string op = item.substr(0, item.find('='));

	                    string gate = item.substr(item.find('=') + 1);
	                    string gatetype = gate.substr(0, gate.find('('));
	                    //cout << trim(gatetype) << "\n";
	                    Node* n = new Node(benchFileName, trim(gatetype));
	                    bool detected = false;
	                    for(int i=0;i<outputVectors.size();i++)
	                    {	
	                    	
	                		string str1 = trim(op);
	                		string str2 = trim(outputVectors[i]);
	                		if( str1.find(str2) != std::string::npos ) {
	                			//cout << "detected: " << trim(op) << '\n';
	                			i=outputVectors.size();
	                			detected = true;
	                    	}
	                    	else{
	                    		
	                    	}
	                    	
	                    }
	                    if ( !detected ){
	                    		//cout << "adding output: " << trim(op) << '\n';
	                			outputs.push_back(trim(op));
	                			(*n).setOutput(trim(op));

	            		}else{
	            			//OUTPUT
	            			(*n).setOutput(trim(op));
	            			outputs.push_back(trim(op));		//comment this
	                			
	            		}
	                    		

	                    if (item.find(",") != std::string::npos) {
	                        string ips1 = gate.substr(gate.find('(') + 1);
	                        ips1 = ips1.substr(0, ips1.find(","));
	                        // cout << ips1 +',';
	                        string ips2 = gate.substr(gate.find(",") + 1);
	                        ips2 = ips2.substr(0, ips2.find(")"));
	                        // cout << ips2 +'\n';

	                        inputs.push_back(trim(ips1));
	                        inputs.push_back(trim(ips2));
	                        (*n).setInput2(trim(ips1), trim(ips2));
	                    }
	                    else {
	                    	string ips1 = gate.substr(gate.find('(') + 1);
	                        
	                        
	                        ips1 = ips1.substr(0, ips1.find(")"));
							inputs.push_back(ips1);
	                        
	                        (*n).setInput(ips1);
	                        // cout << ips1  + '\n';
	                    }
	                    nodes.push_back(n);
							                        
	                }
	            }
	        }
	    }

		
		//std::sort(nodes.begin(), nodes.end(), ValueCmp);
	    
		//std::sort(nodes.begin(), nodes.end(), ValueCmp);
		vector<Wire*> wires;
		int index=0;
		//cout << nodes.size();
	    for (int i = 0; i < nodes.size(); ++i)
	    {    	
	    	
	    	//if(! (*nodes[i]).type.find("INPUT") != std::string::npos)
	    	//{}
	    	Wire* w;
	    		//if (std::find(inputs.begin(), inputs.end(), (*nodes[i]).getOutput() ) != inputs.end())
	    		{

	    			w = new Wire();
	    			Node* toNode;
	    			Node* fromNode;

	    			string ip = (*nodes[i]).getInput();

					if(ip.find(",") != std::string::npos){

	    				std::vector<std::string> tokens;
						std::string token;
						std::istringstream tokenStream(ip);

	    				while (std::getline(tokenStream, token, ','))
	   					{

	   						if(std::find(inputVectors.begin(), inputVectors.end(), trim(token) ) != inputVectors.end())
	   						continue; 
	      					//tokens.push_back(token);
	   						for (int j=0; j<nodes.size(); j++){
	   						//cout<<(*nodes[i]).getOutput() ;
	   						//cout << " = "<<token<<"\n";
	   						if( (*nodes[j]).getOutput().compare(trim(token)) == 0)
	   							{
	   							toNode=nodes.at(i);
	   							//cout << "toNode:" << toNode << "\n";
	   							(*w).setTonode(toNode);
	   							//cout<< outputs.size();
	   							ptrdiff_t  it = std::find(outputs.begin(), outputs.end(), token) - outputs.begin();
								if (it >= outputs.size())
								{
									//cout << "token:" << token <<"is not in vector";
								  // name not in vector
								} else
								{
								  //auto index = std::distance(outputs.begin(), it);
								  //cout<< "fromIndex is::"<<it<<'\n';
								  if(it == 0)
								  {
								  fromNode=nodes.at(it);
								  }
								  else
								  fromNode=nodes.at(it-1);
								  (*w).setFromnode(fromNode);
								  //cout << "fromNode:" << fromNode << "\n";
								  //cout<< "toIndex is::"<<i<<'\n';							
								  wires.push_back(w);
								}

								
	   							//cout << (*nodes[i]).getOutput() <<"=" <<token <<"\n" ;
	   							//cout <<"fromNode: "<< fromNode;
	   							}
	   						}
	   					}
	   					
	    			}
	    			else{
						
	    				//cout <<ip;
	    				string token = trim(ip);

	    				if(std::find(inputVectors.begin(), inputVectors.end(), trim(token) ) != inputVectors.end())
	   						continue; 
	      					//tokens.push_back(token);
	   						for (int j=0; j<nodes.size(); j++){
	   						//cout<<(*nodes[i]).getOutput() ;
	   						//cout << " = "<<token<<"\n";
	   						if( (*nodes[j]).getOutput().compare(trim(token)) == 0)
	   							{
	   							toNode=nodes.at(i);
	   							//cout << "toNode:" << toNode << "\n";
	   							(*w).setTonode(toNode);
	   							
	   							ptrdiff_t  it = std::find(outputs.begin(), outputs.end(), token) - outputs.begin();
								if (it >= outputs.size())
								{
								  // name not in vector
								} else
								{
								  //auto index = std::distance(outputs.begin(), it);
								  //cout<< "fromIndex is::"<<it-1<<'\n';
	   							
								  fromNode=nodes.at(it);
								  (*w).setFromnode(fromNode);
								  //cout << "fromNode:" << fromNode << "\n";
								  //cout<< "toIndex is::"<<i<<'\n';							
								  wires.push_back(w);
								}

								
	   							//cout << (*nodes[i]).getOutput() <<"=" <<token <<"\n" ;
	   							//cout <<"fromNode: "<< fromNode;
	   							}
	   						}
	    			}
	    			//cout << " we found: " << (*nodes[i]).getOutput();
	    	
	    		}
	    		
		    //	( inputs[j].find( (*nodes[i]).getOutput() ) != std::string::npos ){
			//		*w = new Wire();
	    	//	}

	    	//}
	    	
	    }

		for (int i = 0; i < inputVectors.size(); ++i)
	    {
			string type="INPUT";
            Node* n = new Node(benchFileName, type);
            //(*n).state=0;
            (*n).setInput(inputVectors[i]);				// set input values to 0 default
            nodes.push_back(n);
	    }
	    for (int i = 0; i < nodes.size(); ++i)
	    {
	    	if((*nodes[i]).type!="INPUT"){
			    string ip = (*nodes[i]).getInput();
				string op = (*nodes[i]).getOutput();
				//cout << op <<": " << ip <<'\n';
	    	}
		}
		for (int i = 0; i < wires.size(); ++i)
	    {
	    	//cout << "driving nodes" <<(*wires[i]).drivingNode <<"\n";
	    	//cout << "driven nodes" <<(*wires[i]).drivenNode <<"\n";
	    }

	    return 0;
	};
	void evaluate(){
		for (int i=0  ; i< inputValues.size() ; i++)
		{
			int index=0;
			for(int j=0;j<inputValues[i].size();j++){
	        	char ip=inputValues[i].at(j);
	        	for(map<string,bool>::iterator it = inputsMap.begin(); it != inputsMap.end(); ++it) {

					if(j==index){
						it->second=ip;
						//cout << "here:"<< it->second;
					}
					index=index+1;

				}		
	        	
	        	//cout << ip << "::";
	    	}
			for (int i = 0; i < nodes.size(); ++i)
		    {
		    	if((*nodes[i]).type=="INPUT"){
		    		bool value=(*nodes[i]).generateStatus(inputsMap,outputsMap);
		    	}
			}
			for (int i = 0; i < nodes.size(); ++i)
		    {
		    	if((*nodes[i]).type!="INPUT"){
		    		bool value=(*nodes[i]).generateStatus(inputsMap,outputsMap);
		    		outputsMap.insert( std::pair<string,bool>((*nodes[i]).getOutput(),value) );
		    	}
			}

		}
	}
};
