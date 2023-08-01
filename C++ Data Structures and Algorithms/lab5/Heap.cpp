//
//  Heap.cpp
//  Heap
//
//  Created by Rahul Katwala, Michael Bettencourt, Nathanael Shin on 4/30/20.
//  Copyright © 2020 Rahul Katwala. All rights reserved.
//

#include "Heap.h"

#include <iostream>
#include <ostream>

#include "PrintJob.h"


 
Heap::Heap(){
    numItems=0;
}

  /*Inserts a PrintJob to the heap without
  violating max-heap properties.*/
void Heap::enqueue (PrintJob* print){
    
    if(numItems < MAX_HEAP_SIZE){
        //checks if head is empty
        if(numItems == 0){
            arr[0] = print;
            numItems++;
        }
        
        
        else {
            //set to total amount in queue
            int position = numItems;
            arr[position]= print;
            numItems++;
            //while node isnt 0, and while parent is less than new one
            while(position>0 && (arr[(position-1)/2]->getPriority() < arr[position]->getPriority())) {
                //swaps node
                PrintJob* temp = arr[position];
                arr[position]= arr[(position)/2];
                arr[position/2]= temp;
                
                position = (position)/2;
            }
                  
                  
        }
    }
}
                  

  /*Removes the node with highest priority from the heap.
  Follow the algorithm on priority-queue slides. */
void Heap::dequeue() {
    if(numItems==0){
        return;
    }
        arr[0] = arr[numItems -1];
        numItems--;
        trickleDown(0);
                
}
  /*Returns the node with highest priority.*/
PrintJob* Heap::highest(){
 
    return arr[0];
}

  /*Prints the PrintJob with highest priority in the following format:
  Priority: priority, Job Number: jobNum, Number of Pages: numPages
  (Add a new line at the end.)*/
void Heap::print() {

    if(numItems!=0) {
        cout << "Priority: " << highest()->getPriority()<< ", Job Number: " << highest()->getJobNumber() << ", Number of Pages: "<< highest()->getPages()<< endl;
    }
}
                  

  /*This function is called by dequeue function
  to move the new root down the heap to the
  appropriare location.*/
void Heap::trickleDown(int index){
                
    PrintJob* temp = arr[index];
        if(2*index+1 > (numItems-1)){
            return;
        }
        if(2*index+1 == (numItems-1)){
          if(arr[index]->getPriority() > arr[2*index+1]->getPriority()){
            return;
          }
          else{
            arr[index] = arr[2*index+1];
            arr[2*index+1] = temp;
            return;
          }
        }
        if(arr[index]->getPriority() >= arr[2*index+1]->getPriority() && arr[index]->getPriority() >= arr[2*index+2]->getPriority() ){
            return;
        }
        else{
            if(arr[2*index+1]->getPriority() >= arr[2*index+2]->getPriority()){
                arr[index] = arr[2*index+1];
                arr[2*index+1]= temp;
                trickleDown(2*index+1);
            }
            else{
                arr[index] = arr[2*index+2];
                arr[2*index+2]= temp;
                trickleDown(2*index+2);
            }
      }
    
}




