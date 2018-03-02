#include "Node.h"
class Wire{
public:
	Node *drivingNode;
	Node *drivenNode;
	Wire(){

	}
	Wire(Node *fromNode, Node *toNode){
		drivingNode=fromNode;
		drivenNode=toNode;
	}
	void test();
	void setFromnode(Node *fromNode){
		(*this).drivingNode=fromNode;
	}
	void setTonode(Node *toNode){
		(*this).drivenNode=toNode;
	}
	
};