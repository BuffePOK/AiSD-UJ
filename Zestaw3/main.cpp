#include "arraylist.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

bool empty_test() {
  ArrayList<int> list;
  return list.empty();
}

bool push_front_test() {
  ArrayList<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push_front(random);
    if (list.front() != random) return false;
  }

  return true;
}

bool back_test() {
  ArrayList<int> list;
  int random = rand();
  list.push_front(random);
  return list.back() == random;
}

bool push_back_test() {
  ArrayList<int> list;

  for (size_t i = 0; i < 16; i++) {
    int random = rand();
    list.push_back(random);
    if (list.back() != random) return false;
  }

  return true;
}

bool size_test() {
  ArrayList<int> list;
  unsigned random = rand() % 512;

  for (unsigned i = 0; i < random; i++)
    list.push_front(1);

  return list.size() == random;
}

bool max_size_test() {
  ArrayList<int> list(16);

  return list.max_size() == 16;
}

bool full_test() {
  ArrayList<int> list;

  for (unsigned i = 0; i < list.max_size(); i++)
    list.push_front(1);

  return list.full() == true;
}

bool pop_front_test() {
  ArrayList<int> list;
  unsigned size = 128;
  int randomVal[128];

  for (unsigned i = 0; i < 128; i++) {
    randomVal[i] = rand();
    list.push_back(randomVal[i]);
  }

  for (unsigned i = 0; i < 128; i++)
    if (list.pop_front() != randomVal[i] || list.size() != --size) return false;

  return true;
}

bool pop_back_test() {
  ArrayList<int> list;
  unsigned size = 128;
  int randomVal[128];

  for (unsigned i = 0; i < 128; i++) {
    randomVal[i] = rand();
    list.push_front(randomVal[i]);
  }

  for (unsigned i = 0; i < 128; i++)
    if (list.pop_back() != randomVal[i] || list.size() != --size) return false;

  return true;
}

bool clear_test() {
  ArrayList<int> list;

  for (size_t i = 0; i < 16; i++)
    list.push_back(i);

  list.clear();

  return list.size() == 0 ? true : false;
}

bool get_index_test() {
  ArrayList<int> list;
  int randomVal[128];

  for (size_t i = 0; i < 128; i++) {
    int random = rand();
    randomVal[i] = random;
    list.push_back(random);
  }

  for (size_t i = 0; i < list.size(); i++)
    if (randomVal[i] != list.get_index(i)) return false;

  return true;
}

bool insert_test() {
  ArrayList<int> list;
  unsigned size = 64;

  for (size_t i = 0; i < size; i++)
    list.push_back(1);

  for (size_t i = 0; i < 64; i++) {
    int random = rand(), randomIndex = rand() % size;
    list.insert(random, randomIndex);
    size++;
    if (list.get_index(randomIndex) != random) return false;
  }

  return true;
}

bool erase_test() {
  ArrayList<int> list;

  for (size_t i = 0; i < 128; i++)
    list.push_back(i);

  int random = rand() % 128;
  list.erase(random);

  if (list.size() != 127) return false;

  for (size_t i = 0; i < list.size(); i++)
    if (list.get_index(i) == random) return false;

  return true;
}

bool range_test() {
  ArrayList<int> list;

  for (size_t i = 0; i < 128; i++)
    list.push_back(rand());

  unsigned a = rand() % 128, b = rand() % 128;

  if (b < a) {
    a = a + b;
    b = a - b;
    a = a - b;
  }

  vector<int> v = list.range(a, b);

  for (size_t i = 0; i <= b - a; i++)
    if (v[i] != list.get_index(i + a)) return false;

  return true;
}

bool sort_test() {
  ArrayList<int> list;

  for (size_t i = 0; i < 128; i++)
    list.push_back(rand());

  list.sort();

  for (size_t i = 0; i < 127; i++)
    if (list.get_index(i) > list.get_index(i + 1)) return false;

  return true;
}

bool merge_test() {
  ArrayList<int> list, list2, list3, list4;
  unsigned size = 64 + rand() % 64, size2 = 64 + rand() % 64;

  for (size_t i = 0; i < size; i++)
    list.push_back(rand());

  for (size_t i = 0; i < size2; i++)
    list2.push_back(rand());

  list.sort();
  list2.sort();
  list.merge(list2);

  if (list.size() != size + size2) return false;

  for (size_t i = 0; i < list.size() - 1; i++)
    if (list.get_index(i) > list.get_index(i + 1)) return false;

  return true;
}

bool reverse_test() {
  ArrayList<int> list;
  vector<int> v;
  int random = rand() % 128;

  for (int i = 0; i < random; i++) {
    random = rand();
    list.push_back(random);
    v.push_back(random);
  }

  list.reverse();
  reverse(v.begin(),v.end());

  for (unsigned i = 0; i < list.size(); i++)
    if (list.get_index(i) != v[i]) return false;

  return true;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));

  cout<< boolalpha;
  cout << "empty() test: " << empty_test() << '\n';
  cout << "push_front() test: " << push_front_test() << '\n';
  // Zakladam, ze front() jest trywialne i poprawne w celu testowania innych metod
  cout << "back() test: " << back_test() << '\n';
  cout << "push_back() test: " << push_back_test() << '\n';
  cout << "size() test: " << size_test() << '\n';
  cout << "max_size() test: " << max_size_test() << '\n';
  cout << "full() test: " << full_test() << '\n';
  cout << "pop_front() test: " << pop_front_test() << '\n';
  cout << "pop_back() test: " << pop_back_test() << '\n';
  cout << "clear() test: " << clear_test() << '\n';
  cout << "get_index_test() test: " << get_index_test() << '\n';
  cout << "insert_test() test: " << insert_test() << '\n';
  cout << "erase_test() test: " << erase_test() << '\n';
  cout << "range_test() test: " << range_test() << '\n';
  cout << "sort_test() test: " << sort_test() << '\n';
  cout << "merge_test() test: " << merge_test() << '\n';
  cout << "reverse_test() test: " << reverse_test() << '\n';

  return 0;
}
