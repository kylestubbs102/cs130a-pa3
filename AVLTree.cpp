#include "AVLTree.h"
#include <iostream>
using namespace std;

AVLTree::AVLTree() {
    nodeCount = 0;
    root = NULL;
}

AVLTree::~AVLTree() {
    destructorHelper(root);
}

void AVLTree::destructorHelper(AVLNode* node) {
    if (node) {
        destructorHelper(node->left);
        destructorHelper(node->right);
        delete node;
    }
}

void AVLTree::searchWord(string word) {
    AVLNode* temp = getNode(word);
    if (temp) {
        cout << word << " found, count = "
                << temp->counter << endl;
	    temp = NULL;
        delete temp;
    }
    else {
        cout << word << " not found" << endl;
    }
}

bool AVLTree::exists(string word) {
    AVLNode* temp = getNode(word);
    if (temp) {
    	temp = NULL;
        delete temp;
        return true;
    }
    else
        return false;
}

AVLNode* AVLTree::getNode(string word) {
    AVLNode* temp = new AVLNode;
    temp = root;
    while (temp) {
        if (word.compare(temp->data) < 0)
            temp = temp->left;
        else if (word.compare(temp->data) > 0)
            temp = temp->right;
        else if (word.compare(temp->data) == 0) {
            return temp;
        }
    }
    return NULL;
}

void AVLTree::insertWord(string word, bool start) {
    if (root == NULL) {
        root = new AVLNode(word);
        nodeCount = 1;
		if (!start)
      		cout << word << " inserted, new count = 1" << endl;
        return;
    }
    AVLNode* temp = getNode(word);
    if ( temp ) {
        temp->counter++;
		if (!start)
        	cout << word << " inserted, new count = " << 
                 	   temp->counter << endl;
		temp = NULL;
        delete temp;
        return;
    }
    temp = root;
    while (temp) {
        if (word.compare(temp->data) < 0) {
            if (temp->left) {
                temp = temp->left;
            }
            else {
                temp->left = new AVLNode(word);
                temp->left->parent = temp;
                break;
            }
        }
        else {
            if (temp->right) {
                temp = temp->right;
            }
            else {
                temp->right = new AVLNode(word);
                temp->right->parent = temp;
                break;
            }
        }
    }
    while (temp != NULL) {
    	balance(temp);
    	temp = temp->parent;
    }
    temp = NULL;
    delete temp;
    if (!start)
    	cout << word << " inserted, new count = 1" << endl;
    nodeCount++;
}

int AVLTree::height(AVLNode* node) {
	if (node) {
		int leftHeight = height(node->left);
		int rightHeight = height(node->right);
		if (leftHeight > rightHeight)
			return 1 + leftHeight;
		else
			return 1 + rightHeight;
	}
	return 0;
}

int AVLTree::heightDifference(AVLNode* node) {
	int leftHeight = height(node->left);
	int rightHeight = height(node->right);
	return leftHeight - rightHeight;
}

void AVLTree::balance(AVLNode* node) {
	int difference = heightDifference(node);
	if (difference > 2) {
		if (heightDifference(node->left) > 0)
			rotateLeftLeft(node);
		else
			rotateLeftRight(node);
	}
	else if (difference < -2) {
		if (heightDifference(node->right) > 0)
			rotateRightLeft(node);
		else
			rotateRightRight(node);
	}
	int x;
}

void AVLTree::rotateLeftLeft(AVLNode* node) {
	if (node == root) {
		root = node->left;
	}
	else {
		if (node->data.compare(node->parent->data) < 0)
			node->parent->left = node->left;
		else
			node->parent->right = node->left;
	}
	node->left->parent = node->parent;
	AVLNode* temp = new AVLNode;
	temp = node->left;
	node->left = temp->right;
	if (node->left)
		node->left->parent = node;
	node->parent = temp;
	temp->right = node;
	temp = NULL;
	delete temp;
}

void AVLTree::rotateLeftRight(AVLNode* node) {
	rotateRightRight(node->left);
	rotateLeftLeft(node);
}

void AVLTree::rotateRightLeft(AVLNode* node) {
	rotateLeftLeft(node->right);
	rotateRightRight(node);
}

void AVLTree::rotateRightRight(AVLNode* node) {
	if (node == root) {
		root = node->right;
	}
	else {
		if (node->data.compare(node->parent->data) < 0)
			node->parent->left = node->right;
		else
			node->parent->right = node->right;
	}
	node->right->parent = node->parent;
	AVLNode* temp = new AVLNode;
	temp = node->right;
	node->right = temp->left;
	if (node->right)
		node->right->parent = node;
	node->parent = temp;
	temp->left = node;
	temp = NULL;
	delete temp;
}

void AVLTree::rangeSearch(string start, string end) {
    rangeSearchHelper(root, start, end);
}

void AVLTree::rangeSearchHelper(AVLNode* node, string start, string end) {
    if (node == NULL)
        return;
    rangeSearchHelper(node->left, start, end);
    if ( node->data.compare(start) >= 0 && node->data.compare(end) <= 0 ) 
        cout << node->data << endl;
    rangeSearchHelper(node->right, start, end);
}

void AVLTree::preOrderTraversal() {
	preOrderTraversalHelper(root);
	cout << endl;
}

void AVLTree::preOrderTraversalHelper(AVLNode* node) {
	if (!node) {
		cout << "()";
		return;
	}
	cout << "(" << node->data << ":" << node->counter;
	preOrderTraversalHelper(node->left);
	preOrderTraversalHelper(node->right);
	cout << ")";
}

void AVLTree::printHeight() {
	cout << "Height = " << height(root) << endl;
}
