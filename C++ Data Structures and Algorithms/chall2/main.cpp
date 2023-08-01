#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
#include <list>
#include <queue>
#include <stack>

using namespace std;

#include "WordLadder.h"

int main() {
    string fileName;
    string startWord;
    string endingWord;
    string outputFile;

    cout << "Enter file name: " << endl;
    cin >> fileName;
    cout << "Enter starting word: " << endl;
    cin >> startWord;
    cout << "Enter ending word: " << endl;
    cin >> endingWord;
    cout << "Enter output file: " << endl;
    cin >> outputFile;
    WordLadder startGame(fileName);
    cout << "workds";
    startGame.outputLadder(startWord, endingWord, outputFile);

}