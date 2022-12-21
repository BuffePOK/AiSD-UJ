#include <iostream>

#ifndef ARRSIZE
#define ARRSIZE 20
#endif

using namespace std;

void insertionSort(int arr[], unsigned left, unsigned right) {
  for (unsigned i = left + 1; i < right; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = key;
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
  insertionSort(arr, 0, ARRSIZE);
  printArr(arr, ARRSIZE);

  return 0;
}
