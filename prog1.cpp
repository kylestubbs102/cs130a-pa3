#include <iostream>
#include <fstream>
#include <string>
#include "AVLTree.h"
#include "2to5Tree.h"
using namespace std;

int main(int argv, char** argc) {

	ifstream wordList;
	string line;
	wordList.open("/autograder/submission/PA3_dataset.txt");
	if (!wordList) {
		cout << "could not open file";
		return 1;
	}

	while (getline (wordList, line) && (line.length() > 0)) {
		
	}
}