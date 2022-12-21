// mydeque.h

#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyDeque {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyDeque(int s = 10) : msize(s + 1), head(0), tail(0) {
        tab = new T[s + 1];
        assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other); // copy constructor
    MyDeque(MyDeque&& other); // move constructor
    MyDeque& operator=(const MyDeque& other); // copy assignment operator, return *this
    MyDeque& operator=(MyDeque&& other); // move assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize - 1; }
    void push_front(const T& item); // dodanie na początek O(1)
    void push_front(T&& item); // dodanie na początek O(1)
    void push_back(const T& item); // dodanie na koniec O(1)
    void push_back(T&& item); // dodanie na koniec O(1)
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop_front(); // usuwa początek kolejki O(1)
    void pop_back(); // usuwa koniec kolejki O(1)
    void clear(); // czyszczenie listy z elementow
    void display();
    // Operacje z indeksami.
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item); // inserts item before pos
    void insert(int pos, T&& item); // inserts item before pos
};

template <typename T>
MyDeque<T>::MyDeque(const MyDeque& other) : msize{other.msize}, head{other.head}, tail{other.tail} {
  tab = new T[msize];
  assert(tab != nullptr);

  if (tail != 0)
    for (int i = 0; i < tail; i++)
      tab[i] = other.tab[i];

  if (head != 0)
    for (int i = head; i < msize; i++)
      tab[i] = other.tab[i];
}

template <typename T>
MyDeque<T>& MyDeque<T>::operator=(const MyDeque& other) {
  MyDeque<T> temp(other);
  std::swap(msize, temp.msize);
  std::swap(head, temp.head);
  std::swap(tail, temp.tail);
  std::swap(tab, temp.tab);
  return *this;
}

template <typename T>
void MyDeque<T>::push_front(const T& item) {
    head = (head + msize - 1) % msize;
    tab[head] = item;
}

template <typename T>
void MyDeque<T>::push_front(T&& item) {
    head = (head + msize - 1) % msize;
    tab[head] = std::move(item);
}

template <typename T>
void MyDeque<T>::push_back(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::push_back(T&& item) {
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_front() {
  // tab[head] = T(); // Na Ubuntu wypluwa "free(): invalid pointer"
  head = (head + msize + 1) % msize;
}

template <typename T>
void MyDeque<T>::pop_back() {
  tail = (tail - 1 + msize) % msize;
  // tab[tail] = T(); // Na Ubuntu wypluwa "free(): invalid pointer"
}

template <typename T>
void MyDeque<T>::clear() {
  while (!empty()) pop_front();
}

template <typename T>
void MyDeque<T>::display() {
    for (int i = head; i != tail; i = (i + 1) % msize)
        std::cout << tab[i] << " ";

    std::cout << std::endl;
}

template <typename T>
T& MyDeque<T>::operator[](int pos) {
  assert(pos >= 0 && pos < size());
  return tab[(head + pos) % msize];
}

template <typename T>
const T& MyDeque<T>::operator[](int pos) const {
  assert(pos >= 0 && pos < size());
  return tab[(head + pos) % msize];
}

template <typename T>
void MyDeque<T>::erase(int pos) {
  assert(pos >= 0 && pos < size());

  for (size_t i = pos + 1; i < size(); i++) {
    tab[(head + i + msize - 1) % msize] = tab[(head + 1) % msize];
  }

  tail = (tail - 1 + msize) % msize;
  tab[tail] = T();
}

#endif
