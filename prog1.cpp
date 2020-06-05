#include <iostream>
#include <fstream>
#include <string>
#include "AVLTree.h"
#include "TwoFiveTree.h"
using namespace std;

int main(int argv, char** argc) {

	ifstream wordList;
	string line;
	//wordList.open("/autograder/submission/PA3_dataset.txt");
	wordList.open("PA3_dataset.txt");
	if (!wordList) {
		cout << "could not open file";
		return 1;
	}

	TwoFiveTree tft;
	while (getline (wordList, line) && (line.length() > 0)) {
		tft.insertWord(line, true);
	}
	tft.searchWord("asdfadfa");
	tft.searchWord("pickaxing");
	tft.insertWord(Node("pickaxing"), false);
	tft.insertWord(Node("adadssdf"), false);
	tft.rangeSearch("dog", "drag");
}
