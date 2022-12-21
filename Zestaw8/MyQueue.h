// myqueue.h

#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <iostream>
#include <cassert>

template <typename T>
class MyQueue {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyQueue(int s = 10) : msize{s + 1}, head{0}, tail{0} {
        tab = new T[s + 1];
        assert( tab != nullptr );
    } // default constructor
    ~MyQueue() { delete [] tab; }
    MyQueue(const MyQueue& other); // copy constructor
    MyQueue(MyQueue&& other); // move constructor
    MyQueue& operator=(const MyQueue& other); // copy assignment operator, return *this
    MyQueue& operator=(MyQueue&& other); // move assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize - 1) % msize == tail; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize - 1; }
    void push(const T& item); // dodanie na koniec
    void push(T&& item); // dodanie na koniec
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize - 1) % msize]; } // zwraca koniec
    void pop(); // usuwa poczatek
    void clear(); // czyszczenie listy z elementow
    void display();
};

template <typename T>
MyQueue<T>::MyQueue(const MyQueue& other) : msize{other.msize}, head{other.head}, tail{other.tail} {
  tab = new T[msize];
  assert(tab != nullptr);

  for (int i = 0; i < other.size(); i++)
    tab[i] = other.tab[head + i];
}

template <typename T>
MyQueue<T>& MyQueue<T>::operator=(const MyQueue& other) {
  MyQueue<T> temp(other);
  std::swap(msize, temp.msize);
  std::swap(head, temp.head);
  std::swap(tail, temp.tail);
  std::swap(tab, temp.tab);
  return *this;
}

template <typename T>
void MyQueue<T>::push(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}

template <typename T>
void MyQueue<T>::push(T&& item) {
    tab[tail] = std::move(item);
    tail = (tail + 1) % msize;
}

template <typename T>
void MyQueue<T>::pop() {
  assert(!empty());
  tab[head++] = T();
}

template <typename T>
void MyQueue<T>::clear() {
  while (!empty()) pop();
}

template <typename T>
void MyQueue<T>::display() {
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}

#endif
