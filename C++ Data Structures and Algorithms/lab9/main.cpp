

#include <iostream>
#include <time.h>
using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds


int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void InsertionSort(int numbers[], int numbersSize){

    
    for (int i = 1; i < NUMBERS_SIZE; i++) {
        int j = i;
   // Insert numbers[i] into sorted part
   // stopping once numbers[i] in correct position
        
           while (j > 0 && numbers[j] < numbers[j - 1]) {
         
      // Swap numbers[j] and numbers[j - 1]
          int temp = numbers[j];
        numbers[j] = numbers[j - 1];
          numbers[j - 1] = temp;
         --j;
           }
    }
}
    
int Partition(int numbers[], int lowIndex, int highIndex) {
   // Pick middle element as pivot
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    int pivot = numbers[midpoint];
    int temp =  0;
    bool done = false;
   while (!done) {
      // Increment lowIndex while numbers[lowIndex] < pivot
      while (numbers[lowIndex] < pivot) {
          lowIndex += 1;
      }
      
      // Decrement highIndex while pivot < numbers[highIndex]
      while (pivot < numbers[highIndex]) {
          highIndex--;
      }
      
      // If zero or one elements remain, then all numbers are
      // partitioned. Return highIndex.
      if (lowIndex >= highIndex) {
          done = true;
      }
      else {
         // Swap numbers[lowIndex] and numbers[highIndex]
          temp = numbers[lowIndex];
          numbers[lowIndex] = numbers[highIndex];
          numbers[highIndex] = temp;
         
         // Update lowIndex and highIndex
          lowIndex += 1;
          highIndex -= 1;
      }
   }
   
    return highIndex;
}

void Quicksort_midpoint(int numbers[], int lowIndex, int highIndex) {
   if (lowIndex >= highIndex) {
       return;
   }

    int lowEndIndex = Partition(numbers, lowIndex, highIndex);
    Quicksort_midpoint(numbers, lowIndex, lowEndIndex);
    Quicksort_midpoint(numbers, lowEndIndex + 1, highIndex);
}

       
    
int Partition_medianOfThree(int numbers[], int lowIndex, int highIndex) {
   // Pick middle element as pivot
    int midpoint = lowIndex + (highIndex - lowIndex) / 2;
    int pivot = 0;
    int temp =  0;
    bool done = false;
    
    if ((numbers[midpoint] >= numbers[lowIndex] && numbers[midpoint] <= numbers[highIndex]) || (numbers[midpoint] <= numbers[lowIndex] && numbers[midpoint] >= numbers[highIndex])){
        pivot= numbers[midpoint];
    }
    
    else if ((numbers[midpoint] <= numbers[lowIndex] && numbers[lowIndex] <= numbers[highIndex])|| (numbers[midpoint] >= numbers[lowIndex] && numbers[lowIndex] >= numbers[highIndex])) {
        pivot = numbers[lowIndex];
    }
    
    else {
        pivot = numbers[highIndex];
    }
    
   while (!done) {
      // Increment lowIndex while numbers[lowIndex] < pivot
      while (numbers[lowIndex] < pivot) {
          lowIndex += 1;
      }
      
      // Decrement highIndex while pivot < numbers[highIndex]
      while (pivot < numbers[highIndex]) {
          highIndex--;
      }
      
      // If zero or one elements remain, then all numbers are
      // partitioned. Return highIndex.
      if (lowIndex >= highIndex) {
          done = true;
      }
      else {
         // Swap numbers[lowIndex] and numbers[highIndex]
          temp = numbers[lowIndex];
          numbers[lowIndex] = numbers[highIndex];
          numbers[highIndex] = temp;
         
         // Update lowIndex and highIndex
          lowIndex += 1;
          highIndex -= 1;
      }
   }
   
    return highIndex;
}

void Quicksort_medianOfThree(int numbers[], int lowIndex, int highIndex) {
   if (lowIndex >= highIndex) {
       return;
   }

    int lowEndIndex = Partition_medianOfThree(numbers, lowIndex, highIndex);
    Quicksort_medianOfThree(numbers, lowIndex, lowEndIndex);
    Quicksort_medianOfThree(numbers, lowEndIndex + 1, highIndex);
}

int main(){
    int arr1[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];
    fillArrays(arr1, arr2, arr3);
    clock_t Start1 = clock();
    Quicksort_midpoint(arr1, 0, NUMBERS_SIZE);
    clock_t End1 = clock();
    int elapsedTimeMidpoint = (End1 - Start1)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    clock_t Start2 = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    clock_t End2 = clock();
    int elapsedTimeMedian = (End2 - Start2)/CLOCKS_PER_MS;
    clock_t Start3 = clock();
    InsertionSort(arr3, NUMBERS_SIZE);
    clock_t End3 = clock();
    int elapsedTimeInsert = (End3 - Start3)/CLOCKS_PER_MS;
    cout << "midpoint sort: " << elapsedTimeMidpoint << endl;
    cout << "median sort: " << elapsedTimeMedian << endl;
    cout << "insertion sort: " << elapsedTimeInsert << endl;
}



/*
 void InsertionSort(int numbers[], int numbersSize){

     
     for (int i = 1; i < numbersSize; i++) {
         int value = numbers[i];
         for (int j=i-1; numbers[j] > value || j!=0; j--){
             
                 swap(numbers[j], numbers[j+1]);
             
            
         }
 }
 }
 */
