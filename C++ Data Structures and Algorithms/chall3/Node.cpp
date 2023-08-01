#include "Node.h"
#include <string>
using namespace std;

Node::Node(string str1, int dupNum1) {
    str = str1;
    dupNum = dupNum1;
    lftChld = nullptr;
    rghtChld = nullptr;
    
}
