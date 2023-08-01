#include "BSTree.h"
#include <string>
#include <iostream>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

BSTree::~BSTree() {
    while(root != nullptr)
        remove(root->str);
}

void BSTree::insert(const string& str) {
    if(root == nullptr) {
        root = new Node(str, 1);
        return;
    }
    Node* curr = root;
    while(curr != nullptr) {
        if(curr->str == str) {
            curr->dupNum++;
            return;
        }
        else if(curr->str < str) {
            if(curr->rghtChld == nullptr) {
                curr->rghtChld = new Node(str, 1);
                return;
            }
            else {
                curr = curr->rghtChld;
            }
        }
        else {
            //check if curr->lftChld is nullptr, and if so, insert
            if(curr->lftChld == nullptr) {
                curr->lftChld= new Node(str, 1);
                return;
            }
            else {
                curr = curr->lftChld;
            }
        }
    }
}

bool BSTree::search(const string& str) {
    Node* curr = root;
    while(curr != nullptr) {
        if(curr->str == str) {
            return true;
        }
        else if(curr->str < str) {
            curr = curr->rghtChld;
        }
        else {
            curr = curr->lftChld;
        }
    }
    //was not found
    return false;
}

string BSTree::largest() {
    //if tree is empty
    if(root == nullptr) {
        return "";
    }
    //go to right most node, and return its string
    Node* curr = root;
    while(curr->rghtChld != nullptr) {
        curr = curr->rghtChld;
    }
    return curr->str;
}

string BSTree::smallest() {
    //if tree is empty
    if(root == nullptr) {
        return "";
    }
    //go to left most node, and return its string
    Node* curr = root;
    while(curr->lftChld != nullptr) {
        curr = curr->lftChld;
    }
    return curr->str;
}

int BSTree::height(const string& str) {
    Node* curr = root;
    while(curr != nullptr) {
        if(curr->str == str) {
            return recursive_height(curr);
        }
        else if(curr->str < str) {
            curr = curr->rghtChld;
        }
        else {
            curr = curr->lftChld;
        }
    }
    //if node not found
    return -1;
}

int BSTree::recursive_height(Node* curr) {
    if(curr == nullptr)
        return -1;
    int lftHght = recursive_height(curr->lftChld);
    int rghtHght = recursive_height(curr->rghtChld);
    return 1 + max(lftHght, rghtHght);
}

void BSTree::remove(const string& str) {
    if(root == nullptr)
        return;
    //call recursive remove (can't access root->dupNum if root is nullptr)
    recursive_remove(nullptr, root, str);
}

void BSTree::recursive_remove(Node* parent, Node* curr, string str) {
    //2 steps
    // #1: find node
    //if not found then just return
    if(curr == nullptr)
        return;
    if(curr->str < str) {
        recursive_remove(curr, curr->rghtChld, str);
    }
    else if(curr->str > str) {
        recursive_remove(curr, curr->lftChld, str);
    }
    //if found (curr->str == str)
    else {
        //#2: remove node
        //4 cases
        //#1: dupNum > 1
        if(curr->dupNum > 1) {
            curr->dupNum--;
        }
        //#2: Node has no children
        else if(curr->lftChld == nullptr && curr->rghtChld == nullptr) {
            if(root == curr)
                root = nullptr;
            else if(parent->rghtChld == curr) {
                parent->rghtChld = nullptr;
            }
            else
                parent->lftChld = nullptr;
        }
        //#3: Node has NO left child
        //If the node has no left child,
        //replace the node to remove with the smallest value
        //larger than the current string to remove (i.e. find the
        //smallest value in the right subtree of the node to remove).
        else if(curr->lftChld == nullptr) {
            //find smallest node
            parent = curr;
            Node* smallNode = curr->rghtChld;
            while(smallNode->lftChld != nullptr) {
                parent = smallNode;
                smallNode = smallNode->lftChld;
            }
            string tempStr = smallNode->str;
            int tempNum = smallNode->dupNum;
            //reset smallNode dupNum to <= 1
            smallNode->dupNum = 1;
            recursive_remove(parent,smallNode, smallNode->str);
            curr->str = tempStr;
            curr->dupNum = tempNum;
        }
        //#4: Node has a left child
        else {
            //find smallest node
            parent = curr;
            Node* smallNode = curr->lftChld;
            while(smallNode->rghtChld != nullptr) {
                parent = smallNode;
                smallNode = smallNode->rghtChld;
            }
            string tempStr = smallNode->str;
            int tempNum = smallNode->dupNum;
            //reset smallNode dupNum to <= 1
            smallNode->dupNum = 1;
            recursive_remove(parent,smallNode, smallNode->str);
            curr->str = tempStr;
            curr->dupNum = tempNum;
        }
        return;
    }
}

void BSTree::preOrder() {
    recursive_preOrder(root);
}

void BSTree::recursive_preOrder(Node* node) {
    if(node == nullptr)
        return;
    cout << node->str << "(" << node->dupNum << "), ";
    recursive_preOrder(node->lftChld);
    recursive_preOrder(node->rghtChld);
}

void BSTree::inOrder() {
    recursive_inOrder(root);
}

void BSTree::recursive_inOrder(Node* node) {
    if(node == nullptr)
        return;
    recursive_inOrder(node->lftChld);
    cout << node->str << "(" << node->dupNum << "), ";
    recursive_inOrder(node->rghtChld);
}

void BSTree::postOrder() {
    recursive_postOrder(root);
}

void BSTree::recursive_postOrder(Node* node) {
    if(node == nullptr)
        return;
    recursive_postOrder(node->lftChld);
    recursive_postOrder(node->rghtChld);
    cout << node->str << "(" << node->dupNum << "), ";
}
