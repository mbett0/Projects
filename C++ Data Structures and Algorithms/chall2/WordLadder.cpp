#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
#include <list>
#include <queue>
#include <stack>

using namespace std;

#include "WordLadder.h"

WordLadder::WordLadder(const string& inputFile) {
    ifstream inFS(inputFile);
    string word;
    if(!inFS.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }
    while(inFS >> word) {
        if(word.length() != 5) {
            cout << "Invalid Word." << endl;
            return;
        }
        dict.push_back(word);
    }
}

bool WordLadder::offByOne(const string word, const string dictWord) {
    int counter = 0;
    for (int i = 0; i < 5; i++) {
        if (word.at(i) == dictWord.at(i)) {
            counter++;
        }
    }

    if(counter == 4 || word == dictWord) {
        return true;
    }

    return false;
}
void WordLadder::outputLadder(const string& start, const string& end, const string& outputFile) {

        queue<stack<string> > words;
        stack<string> ladder;
        ofstream outFS;

        outFS.open(outputFile);
        if(!outFS.is_open()) {
            cout << "Unable to read file" << endl;
            return;
        }

        if(start == end) {
            outFS << start;
            return;
        }

        ladder.push(start);
        words.push(ladder);

        while(!dict.empty() && !words.empty()) {
            for(list<string>::iterator i = dict.begin(); i != dict.end(); i++) {
                if(offByOne(*i, words.front().top())) {
                    if(*i == end) {
                        stack<string> copyLadder;
                        copyLadder.push(*i);
                        while(!words.front().empty()) { //reverses the stack order
                            copyLadder.push(words.front().top());
                            words.front().pop();
                        }

                        while(!copyLadder.empty()) { //outputs final stack to output file
                            outFS << copyLadder.top() << " ";
                            copyLadder.pop();
                        }
                        outFS.close();
                        return;
                    }

                    else {
                        stack<string>copyLadder;
                        copyLadder = words.front();
                        copyLadder.push(*i);
                        i = dict.erase(i); //after *i is removed, iterator must be set to the removed elements address to prevent seg fault
                        words.push(copyLadder);
                        i--; //list is reduced in size, so must do i-- to go through the list in order
                    }
                }
            }
            words.pop();
        }
        if(outFS.is_open() && words.empty()) {
            outFS << "No Word Ladder Found." << endl;
            outFS.close();
            return;
        }
    }
    
    
    
    /*        void FaceOff(vector<int>&stats){


        //vector<int> stats;
        double three;
double fg;

        for(int i=0; i<list.size(); i++){
                int a=0;
                for (int j=1; j<=list.at(i)->FGA-list.at(i)->threePA; j++){
                        three = list.at(i)->FGPercent*100;
                        if(rand()%100<=three)
                                a+=2;
                           }
                for (int j=1; j<=list.at(i)->threePA; j++){
                        fg = list.at(i)->threeP*100;
                        if(rand()%100<=fg)
                                a+=3;
                           }
        cout<< a<< endl;
                stats.push_back(a);

        }

}*/
    
    
    
    
 /*   // Open output file
    ofstream outFS(outputFile);
    if (!outFS.is_open()) {
        cout << "error opening file" << endl;
        return;
    }

    // Check if start and end are same word
    if (start == end) {
        outFS << start;
        return;
    }

    //list<string> dictcopy(dict);
    stack<string> copy;
    queue<stack<string> > ladder;
    ladder.push(stack<string>());
    ladder.front().push(start);

    // Erase start word from dictionary
    for (list<string>::iterator i = dict.begin(); i != dict.end(); ++i)
    {
        if (*i == start)
        {
            dict.erase(i);
            break;
        }
    }

    while (!ladder.empty())
    {
        string topword = ladder.front().top();

        // Search the entire dictionary for any words that are
        // similar to the topword
        for (list<string>::iterator i = dict.begin(); i != dict.end(); )
        {
            // If a similar word is found create a stack with that word on top, and
            // add the stack to the queue and also erase the similar word from the
            // dictionary.
            if (offByOne(*i, topword))
            {
                copy = ladder.front();
                copy.push(*i);

                if (*i == end)
                {
                    ladder = queue<stack<string> >();
                    ladder.push(stack<string>());
                    break;
                }
                else
                {
                    ladder.push(copy);
                    copy = stack<string>();
                    i = dict.erase(i);
                }
            }
            else {
                ++i;
            }
        }
        ladder.pop();
    }

    if (copy.empty())
    {
        outFS << "No Word Ladder Found." << endl;
    }
    else
    {
        // Print the solution
        stack<string> list;
        while (!copy.empty())
        {
            list.push(copy.top());
            copy.pop();
        }
        
        outFS << list.top();
        list.pop();
        
        while (!list.empty())
        {
            outFS << " " << list.top();
            list.pop();
        }
    }
}
  */

