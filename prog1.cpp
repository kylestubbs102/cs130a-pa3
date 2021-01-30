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
	AVLTree avl;
	while (getline (wordList, line) && (line.length() > 0)) {
		tft.insertWord(line, true);
		avl.insertWord(line, true);
	}

	//****************************************************************
	//tft.preOrderTraversal();
	//tft.printHeight();
	//avl.preOrderTraversal();
	//avl.printHeight();
	//****************************************************************
	//These are the functions with the words from the data set

	int i = 0; 
	while ( argc[1] && (int)argc[1][i] != 78 ) {
		if ( argc[1][i] == 's' ) {
			i += 2;
			if ( argc[1][i] == 'a')
				i += 5;
			else
				break;
			string str = "";
			while ( (int)argc[1][i] > 96 )
				str += argc[1][i++];
			tft.searchWord(str);
			avl.searchWord(str);
		}
		else if ( argc[1][i] == 'i' ) {
			i += 7;
			string str = "";
			while ( (int)argc[1][i] > 96 )
				str += argc[1][i++];
			tft.insertWord(str, false);
			avl.insertWord(str, false);
		}
		else if ( argc[1][i] == 'r' ) {
			i += 13;
			string start = "";
			while ( (int)argc[1][i] > 96 )
				start += argc[1][i++];
			i += 4;
			string end = "";
			while ( (int)argc[1][i] > 96 )
				end += argc[1][i++];
			tft.rangeSearch(start, end);
			avl.rangeSearch(start, end);
		}
		if ( argc[1][i] == ',' )
			i++;
		i++;
	}

	//TwoFiveTree testTwoFive;
	//testTwoFive.insertWord((Node)"dog",true);
	//testTwoFive.preOrderTraversal();
	//testTwoFive.printHeight();
	//
	//This is how you would insert into a 2-5 tree if
	//you wanted to input your own numbers to test it out.
	//It's necessary to include (Node) with my implementation.
	
	//AVLTree testAVL;
	//testAVL.insertWord("dog", true);
	//testAVL.printHeight();
	//avl.preOrderTraversal();
	//
	//And this is how you would do it with the AVL tree.
}
