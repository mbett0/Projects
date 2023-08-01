#include "Node.h"
#include <string>
using namespace std;

Node::Node(string str1) {
    str = str1;
    parent = nullptr;
    lftChld = nullptr;
    rghtChld = nullptr;
    balanceFactor = 0;
 //   height = 0;
}