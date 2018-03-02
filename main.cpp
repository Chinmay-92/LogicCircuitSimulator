#include <algorithm>
#include <sstream>
#include <iterator>
#include "Wire.h"
#include "netlist.h"
using namespace std;

int main(){
	netlist* nl;
	nl = new netlist();
	const char* fname="c17.bench";
	const char* ipfname="c17.in";
	(*nl).updateNetlist(fname,ipfname);
	(*nl).evaluate();
}