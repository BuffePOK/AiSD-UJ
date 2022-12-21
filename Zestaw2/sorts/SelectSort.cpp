#include <iostream>

#ifndef ARRSIZE
#define ARRSIZE 20
#endif

using namespace std;

void selecSort(int arr[], unsigned left, unsigned right) {
  for (unsigned i = left; i < right - 1; i++) {
    unsigned minId = i;

    for (unsigned j = i; j < right; j++) {
      if (arr[j] < arr[minId]) {
        minId = j;
      }
    }

    unsigned temp = arr[i];
    arr[i] = arr[minId];
    arr[minId] = temp;
  }
}

void printArr(int arr[], unsigned size) {
    for (unsigned i = 0; i < size; i++) {
      cout << arr[i] << ' ';
    }

    cout << '\n';
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int arr[ARRSIZE];

  for (size_t i = 0; i < ARRSIZE; i++) {
    arr[i] = rand() % 100;
  }

  printArr(arr, ARRSIZE);
  selecSort(arr, 0, ARRSIZE);
  printArr(arr, ARRSIZE);
  
  return 0;
}
