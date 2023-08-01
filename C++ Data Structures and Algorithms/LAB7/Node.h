#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <string>
using namespace std;
struct Node {
    string str;
    int balanceFactor;
 //   int height;
    Node* parent;
    Node* lftChld;
    Node* rghtChld;
    Node(string); // also sets lftChld and rghtChld to nullptr
};

#endif // NODE_H_INCLUDED