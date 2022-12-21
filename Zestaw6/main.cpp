#include "MyDeque.h"
#include <iostream>

using namespace std;

bool empty_test() {
  MyDeque<int> list;
  return list.empty();
}

bool push_front_test() {
  MyDeque<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push_front(random);
    if (list.front() != random) return false;
  }

  return true;
}

bool back_test() {
  MyDeque<int> list;
  int random = rand();
  list.push_front(random);
  return list.back() == random;
}

bool push_back_test() {
  MyDeque<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push_back(random);
    if (list.back() != random) return false;
  }

  return true;
}

bool size_test() {
  int random = rand() % 512;
  MyDeque<int> list(random);

  for (int i = 0; i < random; i++)
    list.push_front(1);

  return list.size() == random;
}

bool pop_front_test() {
  int size = rand() % 128;
  MyDeque<int> list(size);

  for (int i = 0; i < size; i++)
    list.push_back(rand());

  for (int i = 0; i < size; i++) {
    list.pop_front();
    if (list.size() != --size) return false;
  }

  return true;
}

bool pop_back_test() {
  int size = rand() % 128;
  MyDeque<int> list(size);

  for (int i = 0; i < size; i++)
    list.push_front(rand());

  for (int i = 0; i < size; i++) {
    list.pop_back();
    if (list.size() != --size) return false;
  }

  return true;
}

bool clear_test() {
  MyDeque<int> list;

  for (size_t i = 0; i < 16; i++)
    list.push_back(i);

  list.clear();

  return list.size() == 0;
}


int main(int argc, char const *argv[]) {
  srand(time(NULL));

  cout<< boolalpha;
  cout << "empty() test: " << empty_test() << '\n';
  cout << "push_front() test: " << push_front_test() << '\n';
  // cout << "front() test: " << front_test() << '\n';
  cout << "back() test: " << back_test() << '\n';
  cout << "push_back() test: " << push_back_test() << '\n';
  cout << "size() test: " << size_test() << '\n';
  cout << "pop_front() test: " << pop_front_test() << '\n';
  cout << "pop_back() test: " << pop_back_test() << '\n';
  cout << "clear() test: " << clear_test() << '\n';

  return 0;
}
