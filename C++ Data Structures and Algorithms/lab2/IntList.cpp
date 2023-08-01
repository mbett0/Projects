

#include "IntList.h"

using namespace std;
 //Initializes an empty list with dummy head and dummy tail.
IntList::IntList(){
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    
    dummyHead->prev= 0;
    dummyHead->next = dummyTail;
    dummyTail->prev= dummyHead;
    dummyTail->next=0;
}

//Deallocates all remaining dynamically allocated memory (all remaining IntNodes).

IntList::~IntList(){
    while(dummyHead->next!=dummyTail){
        pop_front();
    }
}

//

void IntList::push_front(int value){
    IntNode* newHead = new IntNode(value);
    
    
    IntNode* currHead = dummyHead->next;
    currHead->prev= newHead;
    newHead->next= currHead;
    dummyHead->next = newHead;
    newHead->prev= dummyHead;
    return;
    
}


//

void IntList::pop_front(){
    
    if (dummyHead->next!=dummyTail){
        IntNode* currHead = dummyHead->next;
        IntNode* newHead= currHead->next;
        dummyHead->next= newHead;
        newHead->prev = dummyHead;
        delete currHead;
        return;
    }
    else {
        return;
    }
    
}


//

void IntList::push_back(int value){
    IntNode* newTail = new IntNode(value);
    
    IntNode* currTail= dummyTail->prev;
    currTail->next = newTail;
    newTail->prev = currTail;
    dummyTail->prev= newTail;
    newTail->next=dummyTail;
    return;
}

//

void IntList::pop_back(){
    
    if (dummyHead->next!=dummyTail){
    IntNode* currTail= dummyTail->prev;
    IntNode* newTail = currTail->prev;
    newTail->next = dummyTail;
    dummyTail->prev = newTail;
    delete currTail;
        
    
    }
    else{
        return;
    }
}

//



bool IntList::empty() const{
    if(dummyHead->next==dummyTail){
        return true;
    }
    else{
        return false;
    }
}

//

ostream &operator<<(ostream & out, const IntList &list){
    IntNode*i= list.dummyHead->next;
    if(list.empty()==true){
        return out;
    }
    else {
        
        while(i!=list.dummyTail){
            out<< i->data;
            i=i->next;
        if(i!=list.dummyTail){
            out<< " ";
        }
        
        }
            return out;
    }
            return out;
    
}

//

void IntList::printReverse() const{
    if(empty()==true){
        return;
    }
    IntNode* i = dummyTail->prev;
            while(i!=dummyHead){
            cout << i->data;
            i=i->prev;
            if(i!=dummyHead){
            cout<<" ";
            }
        }
            return;
}
