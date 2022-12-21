#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#ifndef ARRSIZE
#define ARRSIZE 5
#endif

using namespace std;

template <class Iterator>

void bubbleSort(Iterator begin, Iterator end) {
    for (Iterator i = begin; i < end; i++)
      for (Iterator j = begin; j < (end - 1); j++)
        if (*j > *(j + 1))
          iter_swap(j, j + 1);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  vector<int> v(ARRSIZE);

  generate(v.begin(), v.end(), []() {
    return rand() % 100;
  });

  bubbleSort(v.begin(), v.end());
  assert( is_sorted(v.begin(), v.end()) );

  return 0;
}
