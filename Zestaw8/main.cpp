#include "MyQueue.h"
#include <iostream>
#include <time.h>

using namespace std;

bool empty_test() {
  MyQueue<int> list;
  return list.empty();
}

bool push_test() {
  MyQueue<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push(random);
    if (list.back() != random) return false;
  }

  return true;
}

bool back_test() {
  MyQueue<int> list;
  int random = rand();
  list.push(random);
  return list.back() == random;
}

bool size_test() {
  int random = rand() % 512;
  MyQueue<int> list(random);

  for (int i = 0; i < random; i++)
    list.push(1);

  return list.size() == random;
}

bool pop_test() {
  int msize = rand() % 128;
  int size = rand() % msize;
  MyQueue<int> list(msize);

  for (int i = 0; i < size; i++)
    list.push(rand());

  int initialSize = size;

  for (int i = 0; i < initialSize; i++) {
    list.pop();
    if (list.size() + 1 != size--) return false;
  }

  return true;
}

bool clear_test() {
  MyQueue<int> list;

  for (size_t i = 0; i < 16; i++)
    list.push(i);

  list.clear();

  return list.size() == 0;
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));

  cout<< boolalpha;
  cout << "empty() test: " << empty_test() << '\n';
  cout << "push() test: " << push_test() << '\n';
  cout << "back() test: " << back_test() << '\n';
  cout << "size() test: " << size_test() << '\n';
  cout << "pop() test: " << pop_test() << '\n';
  cout << "clear() test: " << clear_test() << '\n';
  return 0;
}
