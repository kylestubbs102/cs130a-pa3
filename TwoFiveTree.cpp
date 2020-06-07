#include "TwoFiveTree.h"
#include <iostream>
#include <string>
using namespace std;

TwoFiveTree::TwoFiveTree() {
    nodeCount = 0;
    maxLevel = 0;
    root = new NodeGroup();
}

TwoFiveTree::~TwoFiveTree() {
    destructorHelper(root);
}

void TwoFiveTree::destructorHelper(NodeGroup* nodeGroup) {
    for (int i = 0; i < 5; i++) {
        if (nodeGroup->childGroups[i] != NULL)
            destructorHelper(nodeGroup->childGroups[i]);
    }
    delete [] nodeGroup->nodes; 
    delete [] nodeGroup->childGroups;
}

void TwoFiveTree::searchWord(string word) {
    NodeGroup* group = root;
    while (true) {
        for (int i = 0; i < 4; i++) {
            if (word.compare(group->nodes[i].data) == 0) {
                cout << word << " found, count = " << group->nodes[i].counter << endl;
                return;
            }
        }
        if (group->childGroups[0] == NULL)
            break;
        int counter = 0;
        while (counter < 4) {
            if (word.compare(group->nodes[counter].data) < 0)
                break;
            if (group->nodes[counter].data == "") {
                break;
            }
            counter++;
        }
        group = group->childGroups[counter];
    }
    cout << word << " not found" << endl;
}

void TwoFiveTree::insertWord(Node word, bool start) {
    if (nodeCount == 0) {
        nodeCount++;
        maxLevel++;
        root->nodes[0].counter = word.counter;
        root->nodes[0].data = word.data;
        if (!start) {
            cout << word.data << " inserted, new count = 1" << endl;
        }
        return;
    }

    NodeGroup* group = root;
    while (true) {
        for (int i = 0; i < 4; i++) {
            if (word.data.compare(group->nodes[i].data) == 0) {
                group->nodes[i].counter++;
                if (!start) {
                    cout << word.data << " inserted, new count = " << group->nodes[i].counter << endl;
                }
                return;
            }
        }
        if (group->childGroups[0] == NULL)
            break;
        int counter = 0;
        while (counter < 4) {
            if (word.data.compare(group->nodes[counter].data) < 0)
                break;
            if (group->nodes[counter].data == "") {
                break;
            }
            counter++;
        }
        group = group->childGroups[counter];
    }

    if (!start) {
        cout << word.data << " inserted, new count = 1" << endl;
    }

    NodeGroup* tempGroup = NULL;

    group = root;
    while (group->childGroups[0] != NULL) {
        bool end = false;
        int counter = 0;
        while (counter < 4) {
            if (word.data.compare(group->nodes[counter].data) < 0)
                break;
            if (group->nodes[counter].data == "") {
                break;
            }
            counter++;
        }
        group = group->childGroups[counter];
    }
    while (true) {
        if (group->nodes[3].data == "") {
            if (tempGroup) {
                for (int i = 0; i < 5; i++) {
                    if (group->childGroups[i] == NULL) {
                        group->childGroups[i] = tempGroup;
                        group->childGroups[i]->parentGroup = group;
                        break;
                    }
                    else if (tempGroup->nodes[0].data.compare(group->childGroups[i]->nodes[0].data) < 0) {
                        for (int j = 3; j >= i; j--) {
                            if (group->childGroups[j])
                                group->childGroups[j+1] = group->childGroups[j];
                        }
                        group->childGroups[i] = tempGroup;
                        group->childGroups[i]->parentGroup = group;
                        break;
                    }
                }
                tempGroup = NULL;
                delete tempGroup;
            }
            int count = 0;
            while (count < 4) {
                if (count == 3 || group->nodes[count].data == "") {
                    group->nodes[count].data = word.data;
                    group->nodes[count].counter = 1;
                    return;
                }
                else if (word.data.compare(group->nodes[count].data) < 0) {
                    for (int i = 2; i >= count; i--) {
                        group->nodes[i+1] = group->nodes[i];
                    }
                    group->nodes[count].data = word.data;
                    group->nodes[count].counter = 1;
                    return;
                }
                count++;
            }
        }
        else {
            Node* arr = new Node[5];
            int i = 0;
            while (i < 5) {
                if (i == 4) {
                    arr[4] = word;
                    break;
                }
                if (word.data.compare(group->nodes[i].data) < 0) {
                    arr[i] = word;
                    break;
                }
                else {
                    arr[i] = group->nodes[i];
                }
                i++;
            }
            while (i < 4) {
                arr[i+1] = group->nodes[i];
                i++;
            }
            
            group->nodes[0] = arr[0];
            group->nodes[1] = arr[1];
            group->nodes[2].data = "";
            group->nodes[3].data = "";

            word = arr[2];
            NodeGroup* nodeGroup = new NodeGroup;
            nodeGroup->nodes[0] = arr[3];
            nodeGroup->nodes[1] = arr[4];

            Node tempNode;
            for (int i = 0; i < 5; i++)
                arr[i] = tempNode;
            delete [] arr;

            

            if (group->parentGroup == NULL && !tempGroup) {
                NodeGroup* newRoot = new NodeGroup;
                newRoot->nodes[0] = word;
                newRoot->childGroups[0] = group;
                newRoot->childGroups[1] = nodeGroup;
                group->parentGroup = newRoot;
                nodeGroup->parentGroup = newRoot;
                root = newRoot;
                newRoot = NULL;
                delete newRoot;
                nodeGroup = NULL;
                delete nodeGroup;
                maxLevel++;
                return;
            }
            else if (tempGroup) {
                NodeGroup** childArr = new NodeGroup*[6];
                int childIndex = 0;
                while (childIndex < 6) {
                    if (childIndex == 5) {
                        childArr[5] = tempGroup;
                        break;
                    }
                    if (tempGroup->nodes[0].data.compare(group->childGroups[childIndex]->nodes[0].data) < 0) {
                        childArr[childIndex] = tempGroup;
                        break;
                    }
                    else {
                        childArr[childIndex] = group->childGroups[childIndex];
                    }
                    childIndex++;
                }
                while (childIndex < 5) {
                    childArr[childIndex+1] = group->childGroups[childIndex];
                    childIndex++;
                }
                group->childGroups[0] = childArr[0];
                group->childGroups[1] = childArr[1];
                group->childGroups[2] = childArr[2];
                group->childGroups[0]->parentGroup = group;
                group->childGroups[1]->parentGroup = group;
                group->childGroups[2]->parentGroup = group;
                group->childGroups[3] = NULL;
                group->childGroups[4] = NULL;

                nodeGroup->childGroups[0] = childArr[3];
                nodeGroup->childGroups[1] = childArr[4];
                nodeGroup->childGroups[2] = childArr[5];
                nodeGroup->childGroups[0]->parentGroup = nodeGroup;
                nodeGroup->childGroups[1]->parentGroup = nodeGroup;
                nodeGroup->childGroups[2]->parentGroup = nodeGroup;

                for (int i = 0; i < 6; i++)
                    childArr[i] = NULL;
                delete [] childArr;

                tempGroup = NULL;
                delete tempGroup;

                if (group->parentGroup == NULL) {
                    NodeGroup* newRoot = new NodeGroup;
                    newRoot->nodes[0] = word;
                    newRoot->childGroups[0] = group;
                    newRoot->childGroups[1] = nodeGroup;
                    group->parentGroup = newRoot;
                    nodeGroup->parentGroup = newRoot;
                    root = newRoot;
                    newRoot = NULL;
                    delete newRoot;
                    nodeGroup = NULL;
                    delete nodeGroup;
                    maxLevel++;
                    return;
                }
            }
            tempGroup = new NodeGroup;
            tempGroup = nodeGroup;
            nodeGroup = NULL;
            delete nodeGroup;
            group = group->parentGroup;
        }
    }
}

void TwoFiveTree::rangeSearch(string start, string end) {
    rangeSearchHelper(root, start, end);
}

void TwoFiveTree::rangeSearchHelper(NodeGroup* nodeGroup, string start, string end) {
    if (nodeGroup == NULL)
        return;
    int startingI = 0;
    bool arr[5] = {false};
    for (int i = 0; i < 5; i++) {
        if (nodeGroup->childGroups[0] != NULL && nodeGroup->childGroups[i] && !arr[i]) {
            rangeSearchHelper(nodeGroup->childGroups[i], start, end);
            arr[i] = true;
        }
        for (int j = 0; j < 4; j++) {
            if (i != startingI)
                break;
            if (nodeGroup->childGroups[j] != NULL && !arr[j]) {
                rangeSearchHelper(nodeGroup->childGroups[j], start, end);
                arr[j] = true;
            }
            if (nodeGroup->nodes[j].data == "")
                break;
            if (nodeGroup->nodes[j].data.compare(start) >= 0 &&
                    nodeGroup->nodes[j].data.compare(end) <= 0) {
                cout << nodeGroup->nodes[j].data << endl;
                startingI = i;
            }
        }
    }
}

void TwoFiveTree::preOrderTraversal() {
    preOrderTraversalHelper(root, 1);
    cout << endl;
}

void TwoFiveTree::preOrderTraversalHelper(NodeGroup* nodeGroup, int level) {
    if (nodeGroup == NULL)
        return;
    cout << "(";
    if (level == maxLevel) {
        int i;
        for (i = 0; i < 4 && nodeGroup->nodes[i].data != ""; i++) {
            cout << nodeGroup->nodes[i].data << ":" << nodeGroup->nodes[i].counter;
            if (nodeGroup->nodes[i+1].data == "" || i == 3) {
                i++;
                break;
            }
            cout << ",";
        }
        for (int j = 0; j <= i; j++) {
            cout << "()";
        }
    }
    else {
        int i;
        for (i = 0; i < 4 && nodeGroup->nodes[i].data != ""; i++) {
            cout << nodeGroup->nodes[i].data << ":" << nodeGroup->nodes[i].counter;
            if (nodeGroup->nodes[i+1].data == "" || i == 3) {
                i++;
                break;
            }
            cout << ",";
        }
        for (int i = 0; i < 5; i++) {
                preOrderTraversalHelper(nodeGroup->childGroups[i], level+1);
        }
    }
    cout << ")";
}

void TwoFiveTree::printHeight() {
    cout << "Height = " << maxLevel << endl;
}