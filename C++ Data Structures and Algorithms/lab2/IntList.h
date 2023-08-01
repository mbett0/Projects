

#ifndef IntList_h
#define IntList_h

#include <iostream>
#include <stdio.h>

using namespace std;

struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

class IntList{
private:
    IntNode* dummyHead;
    IntNode* dummyTail;
public:
    IntList();
    ~IntList();
    bool empty() const;
    void push_front(int);
    void pop_front();
    void push_back(int);
    void pop_back();
    void printReverse() const;
    friend ostream &operator<<(ostream &, const IntList &);

};




#endif 
