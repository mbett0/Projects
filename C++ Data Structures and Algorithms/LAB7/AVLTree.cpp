#include "AVLTree.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
}

// AVLTree::~AVLTree(){
//     deleteTree(root);
// }

// void AVLTree::deleteTree(Node* curr){
//     if(curr == nullptr){
//         return;
//     }
//     deleteTree(curr->lftChld);
//     deleteTree(curr->lftChld);
//     delete curr;
// }

void AVLTree::insert(const string &str) {
    Node *newNode = new Node(str);
   if (root == nullptr) {
      root = newNode;
      root->parent = nullptr;
      return;
   }
   //atleast one node already
   //search for place to insert, and ....
   Node* curr = root;
   while (curr != nullptr) {
      if (newNode->str == curr->str) {
          //curr->count++;
          curr = nullptr;
      }
      else if (newNode->str < curr->str) {
         if (curr->lftChld   == nullptr) {
            curr->lftChld    = newNode;
            newNode->parent = curr;
            curr = nullptr;
         }
         else
            curr = curr->lftChld;
      }
      else {
         if (curr->rghtChld  == nullptr) {
            curr->rghtChld   = newNode;
            newNode->parent = curr;
            curr = nullptr;
         }
         else
            curr = curr->rghtChld;
      }
   }
  //rotate nodes around for AVL Tree properties
  newNode = newNode->parent;
  //cout << "after first while" << endl;
  while(newNode != nullptr) {
    //cout << "in second while" << endl;
      rotate(newNode);
      newNode = newNode->parent;
  }
 // cout << "after second while" << endl;
}
Node* AVLTree::findUnbalancedNode(Node* node) {
    while (node != 0) {
        if (balanceFactor(node) >= 2 || balanceFactor(node) <= -2) {
            return node;
        }
        else {
            node = node->parent;
        }
    }
    return nullptr;
}

int AVLTree::balanceFactor(Node* node) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (node == 0) {
        return -1;
    }
    
    if (node->lftChld!=0) {
        leftHeight = getHeight(node->lftChld);
    }
    else {
        leftHeight = -1;
    }
    
    if (node->rghtChld!=0) {
        rightHeight = getHeight(node->rghtChld);
    }
    else {
        rightHeight = -1;
    }
    
    return leftHeight - rightHeight;
}



int AVLTree::getHeight(Node* curr) const{
    if(curr == nullptr)
        return -1;
    int lftHght = getHeight(curr->lftChld);
    int rghtHght = getHeight(curr->rghtChld);
    return 1 + max(lftHght, rghtHght);
}

void AVLTree::setBalanceFactors(Node* node) {
    if (node != 0) {
        node->balanceFactor = balanceFactor(node);
        setBalanceFactors(node->lftChld);
        setBalanceFactors(node->rghtChld);
    }
}


void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->lftChld){
            visualizeTree(outFS,n->lftChld);
            outFS<<n->str <<" -> " <<n->lftChld->str<<";"<<endl;
        }

        if(n->rghtChld){
            visualizeTree(outFS,n->rghtChld);
            outFS<<n->str <<" -> " <<n->rghtChld->str<<";"<<endl;
        }
    }
}

// void AVLTree::updateHeight(Node* curr){
//     curr->height = getHeight(curr);
// }

void AVLTree::rotate(Node* node){
 //  AVLTreeUpdateHeight(node)        
   if (balanceFactor(node) == -2) {
      if (balanceFactor(node->rghtChld) == 1) {
         // Double rotation case.
         rotateRight(node->rghtChld);
      }
      return rotateLeft(node);
   }
   else if (balanceFactor(node) == 2) {
      if (balanceFactor(node->lftChld) == -1) {
         // Double rotation case.
         rotateLeft(node->lftChld);
      }
      return rotateRight(node);
   }        
   return;
}


void AVLTree::rotateLeft(Node* node){
   Node* rightLeftChild  = node->rghtChld->lftChld;
   if (node->parent != nullptr){
      ReplaceChild(node->parent, node, node->rghtChld);
   }
   else { // node is root
      root = node->rghtChld;
      root->parent = nullptr;
   }
   SetChild(node->rghtChld, "left", node);
   SetChild(node, "right", rightLeftChild);
}

void AVLTree::rotateRight(Node* node) {
   Node* leftRightChild  = node->lftChld->rghtChld;
   if (node->parent != nullptr){
      ReplaceChild(node->parent, node, node->lftChld);
   }
   else { // node is root
      root = node->lftChld;
      root->parent = nullptr;
   }
   SetChild(node->lftChld, "right", node);
   SetChild(node, "left", leftRightChild);
}


void AVLTree::ReplaceChild(Node* parent,Node* currentChild,Node* newChild) {
   if (parent->lftChld  == currentChild){
      return SetChild(parent, "left", newChild);
   }
   else if (parent->rghtChld  == currentChild){
      return SetChild(parent, "right", newChild);
   }
}

void AVLTree::SetChild(Node* parent,string whichChild,Node* child) {
   if (whichChild != "left" && whichChild != "right"){
      return;
   }

   if (whichChild == "left"){
      parent->lftChld  = child;
   }
   else{
      parent->rghtChld  = child;
   }
   if (child != nullptr){
      child->parent = parent;
   }

   //AVLTreeUpdateHeight(parent);
   return ;
}

void AVLTree::printBalanceFactors(){
    setBalanceFactors(root);
    printBalanceFactors(root);
}
    
void AVLTree::printBalanceFactors(Node* node) {
    // setBalanceFactors(node);
    if(node == 0){
        return;
    }
    else {
        
        printBalanceFactors(node->lftChld);
        cout << node->str << "(" << node->balanceFactor << "), ";
        printBalanceFactors(node->rghtChld);
            
    }
}
