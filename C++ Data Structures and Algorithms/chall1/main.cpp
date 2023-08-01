#include <iostream>
#include <fstream>

using namespace std;

#include "Josephus.h"

int main() {
	Josephus list = Josephus();
	string fileName;
	int numContestants;
	int startIndex;
	int numSkips;
	cout << "Number of contestants: ";
	cin >> numContestants;
	cout << "Starting position: ";
	cin >> startIndex;
	cout << "Number to skip: ";
	cin >> numSkips;
	cout << "Enter file name: ";
	cin >> fileName;
	list.startKills(numContestants, fileName, startIndex, numSkips);
}