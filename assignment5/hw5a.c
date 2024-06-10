// name: Kaustubha Eluri 
// email: eluri.k@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT 200
#define RAND_RANGE 95  // 95 printing characters x20-x7E

// return random character
char randChar() {
  return ((char)((rand() % RAND_RANGE) + 0x20));
}

// return location mid way between left and right
int midPoint(int left, int right){
  return( left + (right-left)/2 );
}

// merge two sorted sub arrays
void mergeIt(
       char* data,
       int leftStart,
       int leftStop,
       int rightStart,
       int rightStop) {
  int leftSize = leftStop - leftStart + 1;
  int rightSize = rightStop - rightStart + 1;
  int totalSize = leftSize + rightSize;

  char* temp = (char*)malloc(totalSize * sizeof(char));
  int leftIndex = leftStart;
  int rightIndex = rightStart;
  int tempIndex = 0;

  // Merge the two subarrays
  while (leftIndex <= leftStop && rightIndex <= rightStop) {
    if (data[leftIndex] <= data[rightIndex]) {
      temp[tempIndex++] = data[leftIndex++];
    } else {
      temp[tempIndex++] = data[rightIndex++];
    }
  }

  // Copy remaining elements from left subarray, if any
  while (leftIndex <= leftStop) {
    temp[tempIndex++] = data[leftIndex++];
  }

  // Copy remaining elements from right subarray, if any
  while (rightIndex <= rightStop) {
    temp[tempIndex++] = data[rightIndex++];
  }

  // Copy merged elements back into original array
  for (int i = 0; i < totalSize; i++) {
    data[leftStart + i] = temp[i];
  }

  free(temp);
  return;
}

// break data array up into halves until down to single elements
// then merge them
void msort(char* data, int left, int right) {
  if (left >= right) {
    // base case of 1 element
    return;
  } else {
    // sort left half
    msort(data, left, midPoint(left,right));

    // sort right half
    msort(data, midPoint(left,right)+1, right);

    // merge left and right halves
    mergeIt(
        data,
        left, midPoint(left,right),
        midPoint(left,right)+1, right
        );
  }
  return;
}

int main(){

  char source[LIMIT]; // array to hold input data values

  int i;             // loop variable
  int j;             // loop variable

  //seed random numbers
  srand((unsigned)time(NULL));

  //initialize source array with random character
  for (i=0; i<LIMIT; i++) {
    source[i] = randChar();
  }

  //print out source array in rows of 20 elements
  printf("Source array:\n");
  for (i=0; i < ((LIMIT/20)+1); i++) {
    for (j=0; j<20; j++) {
      if (i*20+j < LIMIT) {
    printf("%c ",source[i*20+j]);
      }
    }
    printf("\n");
  }
  printf("\n");

  // do the sorting
  msort(source, 0, LIMIT-1);

  //print out sorted array in rows of 10
  printf("Destination array:\n");
  for (i=0; i < ((LIMIT/10)+1); i++) {
    for (j=0; j<10; j++) {
      if (i*10+j < LIMIT) {
    printf("%c ",source[i*10+j]);
      }
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}
