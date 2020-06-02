#ifndef TWOFIVETREE_H
#define TWOFIVETREE_H
#include <iostream>
using namespace std;

struct Node {
    string data;
    int counter;
    Node* left;
    Node* right;
    Node* parent;
    Node(string data1 = "") {
        data = data1;
        counter = 1;
        left = right = parent = NULL;
    }
};

class {
    public:
        TwoFiveTree();
        ~TwoFiveTree();
        void searchWord(string word);
		void insertWord(string word, bool start);
        void rangeSearch(string start, string end);
        void preOrderTraversal();
        void printHeight();
    private:
        int nodeCount;
        Node* root;
        bool exists(string word);
        Node* getNode(string word);
        void rangeSearchHelper(Node* node, string start, string end);
        void destructorHelper(Node* node);
}

#endif