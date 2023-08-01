#ifndef WORDLADDER_H
#define WORDLADDER_H

#include <iostream>
#include <string>
#include<cstdlib>
#include <list>

using namespace std;

class WordLadder {
private:
    list<string>dict;
    bool offByOne(const string word, const string dictWord);
public:
    WordLadder(const string &inputFile);
    void outputLadder(const string &start, const string &end, const string &outputFile);
};

#endif