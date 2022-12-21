#include <iostream>

#ifndef ARRSIZE
#define ARRSIZE 20
#endif

using namespace std;

void bubbleSort(int arr[], unsigned left, unsigned right) {
  int temp;

  for (unsigned i = left; i < right; i++) {
    for (unsigned j = left; j < right; j++) {
      if (arr[i] < arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }

  return;
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
  bubbleSort(arr, 0, ARRSIZE);
  printArr(arr, ARRSIZE);

  return 0;
}
