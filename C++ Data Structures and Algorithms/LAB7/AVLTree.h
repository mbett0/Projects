#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include "Node.h"
#include <string>
using namespace std;
class AVLTree {
private:
    Node* root;

    //helper functions
    
    Node* findUnbalancedNode(Node*);
    void rotate(Node*);
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void printBalanceFactors(Node*);
    void visualizeTree(ofstream&, Node*);
    void setBalanceFactors(Node*);
    int getHeight(Node*) const;
    void ReplaceChild(Node* parent,Node* currentChild,Node* newChild);
    void SetChild(Node* parent,string whichChild,Node* child);
 //   void deleteTree(Node* curr);
public:
 //   ~AVLTree();
    AVLTree();
   void insert(const string &);
    int balanceFactor(Node*);
    void printBalanceFactors();
    void visualizeTree(const string &);
};

#endif
