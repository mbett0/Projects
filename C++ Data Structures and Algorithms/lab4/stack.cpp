//
//  stack.cpp
//  
//
//  Created by Rahul Katwala on 4/20/20.
//
using namespace std;

#define MAX_SIZE 20;

template<typename T>
class stack{
private:
    T data[MAX_SIZE];
    int size;
    
public:
    stack(){
        size=0;
    }
    
    void push(T val){
        try{
            if (size==MAZ_SIZE){
                throw overflow_error("std::overflow_error");
            }
        }
        catch(overflow_error &except){
            cout << "Called push on full stack.";
        }
        
        data[size] = val;
        size++;
    }
    
    void pop(){
        try{
            if(size==0){
                throw out_of_range("std::out_of_range");
            }
        }
        catch(out_of_range & except){
            cout << "Called pop on empty stack.";
        }
        size--;
    }
    
    T top(){
      
        try{
            if(size == 0){
                throw underflow_error("std::underflow_error");
            }
           
           
        }
        catch( underflow_error& except ){
            cout << "Called top on empty stack." << endl;
            return;
        }
    return data[size -1];
    }
    
    bool empty(){
        if (size==0){
            return true;
        }
        return false;
    }
};
