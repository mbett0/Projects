//
//  ArithmeticExpression.cpp
//  ArithmeticExpression
//
//  Created by Rahul Katwala and Michael Bettencourt on 5/6/20.
//  Copyright © 2020 Rahul Katwala. All rights reserved.
//

#include "arithmeticExpression.h"
#include <stack>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;



    /* Initializes an empty tree and sets the infixExpression
    to the value of parameter passed in. */
    arithmeticExpression::arithmeticExpression(const string & sent){
        root = new TreeNode(' ', ' ');
        infixExpression = sent;
    }

    /* Implementation of destrucor is optional.
       The destructor should deallocate all the nodes in the tree. */
    //~arithmeticExpression();

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree(){
    
    string postExpression = infix_to_postfix();
    stack <TreeNode*> s;

    for (unsigned i = 0; i < postExpression.size(); i++) {
        TreeNode *newNode = new TreeNode(postExpression.at(i), 'a' + i);
        //if letter
        if (priority(postExpression.at(i)) == 0) {
            s.push(newNode);
        }
        //else operator
        else {
            newNode->right = s.top();
            s.pop();
            newNode->left = s.top();
            s.pop();
            s.push(newNode);
            root = newNode;
        }
    }
}

    /* Calls the recursive infix function. */
void arithmeticExpression::infix(){
    infix(root);
}

    /* Calls the recursive prefix function. */
void arithmeticExpression::prefix(){
    prefix(root);
}

    /* Calls the recursive postfix function. */
void arithmeticExpression::postfix(){
    postfix(root);
}

    /* Calls the recursive visualizeTree function and generates the .png file using system call. */
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
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


    /* Helper function that returns an integer according to
       the priority of the given operator. */
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

    /* Helper function that returns the postfix notation equivalent
       to the given infix expression */
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

    /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the
       beginning and ending of each expression. */
void arithmeticExpression::infix(TreeNode * node){
    
    if( node->left  && node->right ){
           cout << "(";

           infix(node->left);
           cout << node->data;
           
           infix( node->right);
           cout << ")";
          
       }

       else {
           cout << node->data;
       }
}

    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
void arithmeticExpression::prefix(TreeNode *node){
    if( node){
          cout << node->data;
          prefix(node->left);
          prefix( node->right);
      }
}

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
void arithmeticExpression::postfix(TreeNode *node){
    
    if( node){
        postfix(node->left);
        postfix( node->right);
        cout << node->data;
    }

}

    /* Helper function for generating the dotty file. This is a recursive function. */
void arithmeticExpression::visualizeTree(ofstream &OS, TreeNode *node){
    if (node) {
          OS << node->key << " [ label=\"" << node->data << "\"];" << endl;
         visualizeTree(OS, node->left);
         visualizeTree(OS, node->right);
         if(node->right) {
             OS << node->key << " -> " << node->right->key << ";" << endl;
         }
         if(node->left) {
             OS << node->key << " -> " << node->left->key << ";" << endl;
         }
     }
}
