#include "singlelist.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool empty_test() {
  SingleList<int> list;
  return list.empty();
}

// Zakladam, ze front() jest poprawne w celu testowania innych metod

bool push_front_test() {
  SingleList<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push_front(random);
    if (list.front() != random) return false;
  }

  return true;
}

bool back_test() {
  SingleList<int> list;
  int random = rand();
  list.push_front(random);
  return list.back() == random;
}

bool push_back_test() {
  SingleList<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push_back(random);
    if (list.back() != random) return false;
  }

  return true;
}

bool size_test() {
  SingleList<int> list;
  int random = rand() % 512;

  for (int i = 0; i < random; i++)
    list.push_front(1);

  return list.size() == random;
}

bool pop_front_test() {
  SingleList<int> list;
  int size = rand() % 128;

  for (int i = 0; i < size; i++)
    list.push_back(rand());

  for (int i = 0; i < size; i++) {
    list.pop_front();
    if (list.size() != --size) return false;
  }

  return true;
}

bool pop_back_test() {
  SingleList<int> list;
  int size = rand() % 128;

  for (int i = 0; i < size; i++)
    list.push_front(rand());

  for (int i = 0; i < size; i++) {
    list.pop_back();
    if (list.size() != --size) return false;
  }

  return true;
}

bool clear_test() {
  SingleList<int> list;

  for (size_t i = 0; i < 16; i++)
    list.push_back(i);

  list.clear();

  return list.size() == 0 ? true : false;
}

bool get_index_test() {
  SingleList<int> list;
  int randomVal[128];

  for (size_t i = 0; i < 128; i++) {
    int random = rand();
    randomVal[i] = random;
    list.push_back(random);
  }

  for (int i = 0; i < list.size(); i++)
    if (randomVal[i] != list.get_index(i)) return false;

  return true;
}

bool reverse_test() {
  SingleList<int> list;
  vector<int> v;
  int size = rand() % 128;
  int random;

  for (int i = 0; i < size; i++) {
    random = rand();
    list.push_back(random);
    v.push_back(random);
  }

  list.reverse();
  reverse(v.begin(),v.end());

  for (int i = 0; i < size; i++)
    if (list.get_index(i) != v[i]) return false;

  return true;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  cout<< boolalpha;
  cout << "empty() test: " << empty_test() << '\n';
  cout << "push_front() test: " << push_front_test() << '\n';
  cout << "back() test: " << back_test() << '\n';
  cout << "push_back() test: " << push_back_test() << '\n';
  cout << "size() test: " << size_test() << '\n';
  cout << "pop_front() test: " << pop_front_test() << '\n';
  cout << "pop_back() test: " << pop_back_test() << '\n';
  cout << "clear() test: " << clear_test() << '\n';
  cout << "get_index_test() test: " << get_index_test() << '\n';
  cout << "reverse_test() test: " << reverse_test() << '\n';

  return 0;
}
