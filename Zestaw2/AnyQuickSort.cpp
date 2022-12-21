#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#ifndef ARRSIZE
#define ARRSIZE 20
#endif

using namespace std;

template <class Iterator>

void quickSort(Iterator begin, Iterator end) {
    if (end <= begin) return;

    Iterator pivot = begin, 
             middle = begin + 1;

    for (Iterator i = begin + 1; i < end; i++) {
        if (*i < *pivot) {
            iter_swap(i, middle);
            middle++;
        }
    }

    iter_swap(begin, middle - 1);

    quickSort(begin, middle - 1);
    quickSort(middle, end);
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  vector<int> v(ARRSIZE);

  generate(v.begin(), v.end(), []() {
    return rand() % 100;
  });

  quickSort(v.begin(), v.end());

  // cout << "Vector is sorted ";
  // is_sorted(v.begin(), v.end()) ? cout << "correctly" << '\n' : cout << "incorrectly" << '\n';
  assert( std::is_sorted(v.begin(), v.end()) );

  return 0;
}
