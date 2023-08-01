#ifndef JOSEPHUS_H
#define JOSEPHUS_H

#include <string>

using namespace std;

struct Person {
	string personName;
	Person *next;
    Person *prev;
	Person(string name): personName(name), next(nullptr), prev(nullptr){
    }
};

class Josephus {
	private:
		Person* head;
		void add(string name);
	public:
		Josephus();
        Josephus(string name);
		void startKills(int numPeople, string fileName, int startPosition, int count);
};
#endif
