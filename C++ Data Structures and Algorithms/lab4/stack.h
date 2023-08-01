#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

const int MAX_SIZE = 20;

template <class T>
class stack {
    private:
        T data[MAX_SIZE];
        unsigned size;
    public:
        stack<T>() {
            size = 0;
        }
        
        void push(T val) {z
            try {
                if(size >= MAX_SIZE) {
                    throw overflow_error("Called push on full stack.");
                }
                data[size] = val;
                size++;
            }
            catch(overflow_error& excpt) {
                cout << excpt.what();
            }
        }

        void pop() {
            try {
                if(size == 0) {
                    throw out_of_range("Called pop on empty stack.");
                }
                size--;
            }
            catch(out_of_range& excpt) {
                cout << excpt.what();
            }
        }

        T top() {
            try {
                if(size == 0) {
                    throw underflow_error("Called top on empty stack.");
                }
            }
            catch(underflow_error& excpt) {
                cout << excpt.what() << endl;
                exit(0);
            }
            return data[size-1];
        }

        bool empty() {
            if(size == 0) {
                return true;
            }

            return false;
        }
};

#endif
