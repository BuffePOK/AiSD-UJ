// singlelist.h

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>     // deklaracje strumieni cout, cin, cerr
#include <cassert>    // assert()

template <typename T>
struct SingleNode {
  // the default access mode and default inheritance mode are public
  T value;
  SingleNode *next;
  SingleNode() : value(T()), next(nullptr) {} // konstruktor domyslny
  SingleNode(const T& item, SingleNode *ptr = nullptr) : value(item), next(ptr) {}
  ~SingleNode() {} // destruktor
};

template <typename T>
class SingleList {
    SingleNode<T> *head, *tail;
  public:
    SingleList() : head(nullptr), tail(nullptr) {}
    ~SingleList(); // tu trzeba wyczyscic wezly
    SingleList(const SingleList& other); // copy constructor
    SingleList(SingleList&& other); // move constructor
    SingleList& operator=(const SingleList& other); // copy assignment operator, return *this

    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1), L.push_front(item)
    void push_back(const T& item); // O(1), L.push_back(item)
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(n)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void reverse(); // O(n)

    // Operacje z indeksami.
    int erase(int pos); // return Iterator following the last removed element,
    T& operator[](int pos); // podstawienie L[pos]=item
    const T& operator[](int pos) const; // odczyt L[pos]
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    int insert(int pos, const T& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
    // Zwraca pozycje wstawionego elementu.
    T& get_index(unsigned pos);
};

template <typename T>
SingleList<T>::~SingleList() {
  for (SingleNode<T> *node; !empty(); ) {
    node = head->next; // zapamietujemy
    delete head;
    head = node; // kopiowanie wskaznika
  }
}

template <typename T>
SingleList<T>::SingleList(const SingleList& other) : head{ nullptr }, tail{ nullptr } {
  SingleNode<T> *node = other.head;

   while(node != nullptr) {
     push_back(node->value);
     node = node->next;
  }
}

template <typename T>
SingleList<T>::SingleList(SingleList&& other) : head{ nullptr }, tail{ nullptr } { // move constructor
  std::swap(head, other.head);
  std::swap(tail, other.tail);
}

template <typename T>
SingleList<T>& SingleList<T>::operator=(const SingleList<T>& other) {
  SingleList<T> temp(other);
  std::swap(head, temp.head);
  std::swap(tail, temp.tail);
  return *this;
}

template <typename T>
int SingleList<T>::size() const {
  int counter = 1;

  if (empty()) {
    return 0;
  } else {
    SingleNode<T> *node = head;

    while (node->next != nullptr) {
      counter++;
      node = node->next;
    }
  }

  return counter;
}

template <typename T>
void SingleList<T>::push_front(const T& item) {
  if (!empty()) {
    head = new SingleNode<T>(item, head);
  } else {
    head = tail = new SingleNode<T>(item);
  }
}

template <typename T>
void SingleList<T>::push_back(const T& item) {
  if (!empty()) {
    tail->next = new SingleNode<T>(item);
    tail = tail->next;
  } else {
    head = tail = new SingleNode<T>(item);
  }
}

template <typename T>
void SingleList<T>::pop_front() {
  assert(!empty());
  SingleNode<T> *node = head; // zapamietujemy

  if (head == tail) { // jeden wezel na liscie
    head = tail = nullptr;
  } else { // wiecej niz jeden wezel na liscie
    head = head->next;
  }

  delete node;
}

template <typename T>
void SingleList<T>::pop_back() {
  assert(!empty());
  SingleNode<T> *node = tail; // zapamietujemy

  if (head == tail) { // jeden wezel na liscie
    head = tail = nullptr;
  } else { // wiecej niz jeden wezel na liscie
    // Szukamy poprzednika ogona.
    SingleNode<T> *before = head;

    while (before->next != tail) {
      before = before->next;
    }

    tail = before;
    tail->next = nullptr;
  }

  delete node;
}

template <typename T>
void SingleList<T>::clear() {
  while (!empty()) { pop_front(); }
}


template <typename T>
void SingleList<T>::display() {
  SingleNode<T> *node = head;

  while (node != nullptr){
    std::cout << node->value << " ";
    node = node->next;
  }

  std::cout << '\n';
}

template <typename T>
void SingleList<T>::reverse() {
  SingleList<T> reversed;
  SingleNode<T> *node = head;

  while (node != nullptr) {
    reversed.push_front(node->value);
    node = node->next;
  }

  std::swap(head, reversed.head);
}

template <typename T>
T& SingleList<T>::get_index(unsigned pos) {
  unsigned i = 0;
  SingleNode<T> *node = head;

  while (i++ != pos)
    node = node->next;

  return node->value;
}

#endif
