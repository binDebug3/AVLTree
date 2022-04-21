#include "AVL.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;
static const string INT = "INT";

string boolToStr(bool print) {
	if (print) return "true";
	return "false";
}
string findToStr(bool print) {
	if (print) return "found";
	return "not found";
}

int main(int argc, char* argv[]) {
	VS_MEM_CHECK

	//open files
	if (argc < 3) {
		cerr << "Please provide name of input and output files";
		return 1;
	}
	ifstream in(argv[1]);
	if (!in.is_open()) {
		cout << "Uh oh there was an inputFile error..." << endl;
		return 2;
	}
	ofstream out(argv[2]);
	if (!out.is_open()) {
		cout << "Uh oh there was an outputFile error..." << endl;
		return 3;
	}

	//instantiate objects
	string command;
	string dataType;
	int iValue;
	string sValue;
	AVL<int> intAVL;
	AVL<string> stringAVL;

	while (in >> command) {
		if (command == "INT") {				//INT
			dataType = command;
			out << dataType << " true" << endl;
		}
		else if (command == "STRING") {		//STRING
			dataType = command;
			out << command << " true " << endl;
		}
		else if (command == "add") {		//ADD
			if (dataType == INT) {
				in >> iValue;
				out << command << " " << iValue << " " << boolToStr(intAVL.addNode(iValue)) << endl;
			}
			else {
				in >> sValue;
				out << command << " " << sValue << " " << boolToStr(stringAVL.addNode(sValue)) << endl;
			}
		}
		else if (command == "remove") {		//REMOVE
			if (dataType == INT) {
				in >> iValue;
				out << command << " " << iValue << " " << boolToStr(intAVL.removeNode(iValue)) << endl;
			}
			else {
				in >> sValue;
				out << command << " " << sValue << " " << boolToStr(stringAVL.removeNode(sValue)) << endl;
			}
		}
		else if (command == "print") {		//PRINT
			if (dataType == INT) {
				out << command << ":" << intAVL << endl;
			}
			else {
				out << command << ":" << stringAVL << endl;
			}
		}
		else if (command == "clear") {		//CLEAR
			if (dataType == INT) {
				out << command << " " << boolToStr(intAVL.clearTree()) << endl;
			}
			else {
				out << command << " " << boolToStr(stringAVL.clearTree()) << endl;
			}
		}
		else if (command == "size") {		//SIZE
			if (dataType == INT) {
				out << command << " " << intAVL.size() << endl;
			}
			else {
				out << command << " " << stringAVL.size() << endl;
			}
		}
		else if (command == "find") {		//FIND
			if (dataType == INT) {
				in >> iValue;
				out << command << " " << iValue << " " << findToStr(intAVL.find(iValue)) << endl;
			}
			else {
				in >> sValue;
				out << command << " " << sValue << " " << findToStr(stringAVL.find(sValue)) << endl;
			}
		}
		else if (command == "tree") {		//TREE
			out << command << ": ";
			if (dataType == INT) {
				if (intAVL.size() > 0) {
					AVL<int>::Iterator iter = intAVL.begin();
					for (; iter != intAVL.end(); ++iter) {
						if (iter == intAVL.begin())
							out << *iter;
						else
							out << "," << *iter;
					}
				}
				else out << "Empty ";
				out << endl;
			}
			else {
				if (stringAVL.size() > 0) {
					AVL<string>::Iterator iter = stringAVL.begin();
					for (; iter != stringAVL.end(); ++iter) {
						if (iter == stringAVL.begin())
							out << *iter;
						else
							out << "," << *iter;
					}
				}
				else out << "Empty ";
				out << endl;
			}
		}
	}

	intAVL.clearTree();
	stringAVL.clearTree();
	in.close();
	out.close();
	return 0;
}