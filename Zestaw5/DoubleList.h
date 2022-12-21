// doublelist.h

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct DoubleNode {
// the default access mode and default inheritance mode are public
    T value;
    DoubleNode *next, *prev;
    // konstruktor domyslny (niepotrzebny)
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr = nullptr, DoubleNode *pptr = nullptr) : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *nil;
    int _size;
public:
    DoubleList() : nil(nullptr), _size(0) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly
    DoubleList(const DoubleList& other); // copy constructor
    DoubleList(DoubleList&& other); // move constructor
    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    bool empty() const { return _size == 0; }
    int size() const { return _size; }; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1)
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1)
    T& front() const { return nil->next->value; } // zwraca poczatek, nie usuwa
    T& back() const { return nil->prev->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
DoubleList<T>::~DoubleList() {
  while (!empty()) pop_front();
  delete nil;
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) : nil{nullptr}, _size{0} {
  DoubleNode<T> *node = other.nil->next;

  do {
    push_back(node->value);
    node = node->next;
  } while (node != other.nil->next);
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList<T>& other) {
  DoubleList<T> temp(other);
  std::swap(nil, temp.nil);
  std::swap(_size, temp._size);
  return *this;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {

  if (empty()) {
    DoubleNode<T> *node = new DoubleNode<T>(item);
    nil = new DoubleNode<T>(T(), node, node);
    node->prev = nil;
    node->next = nil;
  } else {
    DoubleNode<T> *node = new DoubleNode<T>(item, nil->next, nil);
    nil->prev->prev = node;
    nil->next = node;
  }

  _size++;
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {

  if (empty()) {
    DoubleNode<T> *node = new DoubleNode<T>(std::move(item));
    nil = new DoubleNode<T>(T(), node, node);
    node->prev = nil;
    node->next = nil;
  } else {
    DoubleNode<T> *node = new DoubleNode<T>(item, nil->next, nil);
    nil->prev->prev = node;
    nil->next = node;
  }

  _size++;
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {

  if (empty()) {
    DoubleNode<T> *node = new DoubleNode<T>(item);
    nil = new DoubleNode<T>(T(), node, node);
    node->prev = nil;
    node->next = nil;
  } else {
    DoubleNode<T> *node = new DoubleNode<T>(item, nil, nil->prev);
    nil->prev->next = node;
    nil->prev = node;
  }

  _size++;
}

template <typename T>
void DoubleList<T>::push_back(T&& item) {

  if (empty()) {
    DoubleNode<T> *node = new DoubleNode<T>(std::move(item));
    nil = new DoubleNode<T>(T(), node, node);
    node->prev = nil;
    node->next = nil;
  } else {
    DoubleNode<T> *node = new DoubleNode<T>(std::move(item), nil->next, nil->prev);
    nil->prev->next = node;
    nil->prev = node;
  }

  _size++;
}

template <typename T>
void DoubleList<T>::pop_front() {
  assert(!empty());
  DoubleNode<T> *node = nil->next;

  if (nil->next == nil->prev)
    delete nil;
  else
    nil->next = nil->next->next;

  _size--;
  delete node;
}

template <typename T>
void DoubleList<T>::pop_back() {
  assert(!empty());
  DoubleNode<T> *node = nil->prev;

  if (nil->next == nil->prev)
    delete nil;
  else
    nil->prev = nil->prev->prev;

  _size--;
  delete node;
}

template <typename T>
void DoubleList<T>::clear() {
  while (!empty()) { pop_front(); }
}

template <typename T>
void DoubleList<T>::display() {
  DoubleNode<T> *node = nil->next;

  for (int i = 0; i < _size; i++) {
    std::cout << node->value << " ";
    node = node->next;
  }

  std::cout << '\n';
}

template <typename T>
void DoubleList<T>::display_reversed() {
  DoubleNode<T> *node = nil->prev;

  for (int i = _size; i > 0; i--) {
    std::cout << node->value << " ";
    node = node->prev;
  }

  std::cout << '\n';
}

template <typename T>
T& DoubleList<T>::operator[](int pos) {
  assert(pos >= 0 && pos < _size);

  DoubleNode<T> *node = nil->next;

  for (int i = 0; i < pos; i++)
    node = node->next;

  return node->value;
}

template <typename T>
const T& DoubleList<T>::operator[](int pos) const {
  assert(pos >= 0 && pos < _size);

  DoubleNode<T> *node = nil->next;

  for (int i = 0; i < pos; i++)
    node = node->next;

  return node->value;
}

#endif

// EOF
