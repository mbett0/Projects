#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <string>
using namespace std;
struct Node {
    string str;
    int dupNum;
    Node* lftChld;
    Node* rghtChld;
    Node(string, int); // also sets lftChld and rghtChld to nullptr
    
};

#endif // NODE_H_INCLUDED
