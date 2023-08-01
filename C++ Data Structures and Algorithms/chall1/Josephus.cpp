#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "Josephus.h"

Josephus::Josephus() {
    head = nullptr;
}

void Josephus::add(string name) {
    Person *newPerson = new Person(name);
    if (head == nullptr) {
        head = newPerson;
        head -> prev = newPerson;
    } 
    else if(head -> prev == nullptr) {
        head -> next = newPerson;
        head -> prev = newPerson;
    }

    else {
        Person *temp = head -> prev;
        temp -> next = newPerson;
        newPerson -> prev = temp;
        newPerson -> next = head;
        head -> prev = newPerson;
    }
}

void Josephus::startKills(int numPeople, string fileName, int startPosition, int count){
    ifstream inFS;
    string personName;
    bool works = false;
    inFS.open(fileName);
    if(!inFS.is_open()) {
        return;
        
    }
    for(int i = 0; i < numPeople; i++) {
        if(inFS >> personName){
            add(personName);
        }
    }
    inFS.close();

    Person *start = head;
    for(int i = 1; i < startPosition; i++) {
        start = start -> next;
    }
    
    Person *killed = start;
    while(killed -> next != killed) {
        int killCount = 1;
        while(killCount != count) {
            killed = killed -> next;
            killCount++;
        }
        
        Person *temp = killed -> prev;
        temp -> next = killed -> next;
        killed -> next -> prev = temp;
        delete killed;
        killed = temp -> next;
    }
    
    cout << killed -> personName << " survived." << endl;


}