//Team with Nathanael Shin, Rahul Katwala, Michael Bettencourt
//used main and createVector provided by Prof. LePendu
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index);

template <typename T>
void selection_sort(vector<T> &vals);

template <typename T>
T getElement(vector<T> vals, int index);

vector<char> createVector();

int main() {
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    //try and catch
    // try {
        while(--numOfRuns >= 0){
            cout << "Enter a number: " << endl;
            cin >> index;
            try {
                if(index >= (int)vals.size()) {
                    throw out_of_range("out of range exception occured");
                }
                curChar = getElement(vals,index);
                cout << "Element located at " << index << ": is " << curChar << endl;
            }
            catch (out_of_range& excpt) {
                cout << excpt.what() << endl;
            }
        }
    //}

    // catch (out_of_range& excpt) {
    //     cout << excpt.what() << endl;
    // }

    //test selection sort
    vector<string> s = {"Hi", "a", "a", "be", "tail", "Mad", "zoo"};
    selection_sort(s);
    vector<int> b = {4,4,3,1,2,5,7,3,2,8,9};
    selection_sort(b);

    for(unsigned i = 0; i < s.size(); i++) {
        cout << s.at(i) << " ";
    }
    cout << endl;
    for(unsigned j = 0; j < b.size(); j++) {
        cout << b.at(j) << " ";
    }

    return 0;
}

template <typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minLoc = index;
    for(unsigned i = index + 1; i < vals.size(); i++) {
        if(vals.at(minLoc) > vals.at(i)) {
            minLoc = i;
        }
    }
    return minLoc;
}

template <typename T>
void selection_sort(vector<T> &vals) {
    unsigned minIndex;
    for(unsigned i = 0; i < vals.size(); i++) {
        minIndex = min_index(vals, i);
        swap(vals.at(i), vals.at(minIndex));
    }
}

template <typename T>
T getElement(vector<T> vals, int index){
    return vals.at(index);
}

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}
