#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
using namespace std;

struct AVLNode {
    string data;
    int counter;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    AVLNode(string data1 = "") {
        data = data1;
        counter = 1;
        left = right = parent = NULL;
    }
};

class AVLTree {
    public:
        AVLTree();
        ~AVLTree();
        void searchWord(string word);
	void insertWord(string word, bool start);
        void rangeSearch(string start, string end);
        void preOrderTraversal();
        void printHeight();
    private:
        int nodeCount;
        AVLNode* root;
	int height(AVLNode* node);
	int heightDifference(AVLNode* node);
	void balance(AVLNode* node);
	void rotateLeftLeft(AVLNode* node);
	void rotateLeftRight(AVLNode* node);
	void rotateRightLeft(AVLNode* node);
	void rotateRightRight(AVLNode* node);
        bool exists(string word);
        AVLNode* getNode(string word);
        void rangeSearchHelper(AVLNode* node, string start, string end);
        void destructorHelper(AVLNode* node);
};

#endif
