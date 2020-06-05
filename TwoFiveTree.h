#ifndef TWOFIVETREE_H
#define TWOFIVETREE_H
#include <iostream>
using namespace std;

struct Node {
    string data;
    int counter;
    //string* values;
    //Node** nodes;
    Node(string data1 = "") {
        data = data1;
        counter = 1;
    }
};

struct NodeGroup {
    Node* nodes;
    //Node** children; //dont know if necessary
    //NodeGroup* parent;
    //NodeGroup* left;
    //NodeGroup* right;
    NodeGroup* parentGroup;
    NodeGroup** childGroups;
    NodeGroup() {
        nodes = new Node[4];
        //children = new Node*[5];
        parentGroup = NULL;
        childGroups = new NodeGroup*[5];
    };
    ~NodeGroup() {
        delete [] nodes;
        //delete [] childGroups;
    }
};

class TwoFiveTree {
    public:
        TwoFiveTree();
        ~TwoFiveTree();
        void searchWord(string word);
		void insertWord(Node word, bool start);
        void rangeSearch(string start, string end);
        void preOrderTraversal();
        void printHeight();
    private:
        int maxLevel;
        int nodeCount;
        int nodeGroupCount;
        NodeGroup* root;
        //bool hasChild;
        Node*& exists(string word); //do this next
        Node* getNode(string word);
        void rangeSearchHelper(NodeGroup* nodeGroup, string start, string end);
        void destructorHelper(NodeGroup* nodeGroup);
};

#endif