#ifndef BSTREE_H_INCLUDED
#define BSTREE_H_INCLUDED
#include "Node.h"
#include <string>
using namespace std;
class BSTree {
private:
    Node* root;

    //helper functions
    int recursive_height(Node*);
    void recursive_remove(Node*, Node*, string);
    void recursive_preOrder(Node*);
    void recursive_inOrder(Node*);
    void recursive_postOrder(Node*);
public:
    BSTree();
    ~BSTree();
    void insert(const string &);
    bool search (const string &);
    string largest();
    string smallest();
    int height(const string &);
    void remove(const string &);

    void preOrder();
    void inOrder();
    void postOrder();
};

#endif // BSTREE_H_INCLUDED