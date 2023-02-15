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
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {} // konstruktor
    ~DoubleNode() {} // destruktor
};


template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList(); // tu trzeba wyczyscic wezly

    DoubleList(const DoubleList& other); // copy constructor
    // usage:   DoubleList<int> list2(list1);

    DoubleList(DoubleList&& other); // move constructor NIEOBOWIAZKOWE
    // usage:   DoubleList<int> list2(std::move(list1));

    DoubleList& operator=(const DoubleList& other); // copy assignment operator, return *this
    // usage:   list2 = list1;

    DoubleList& operator=(DoubleList&& other); // move assignment operator, return *this
    // usage:   list2 = std::move(list1); NIEOBOWIAZKOWE

    bool empty() const { return head == nullptr; }
    int size() const; // O(n) bo trzeba policzyc
    void push_front(const T& item); // O(1)
    void push_front(T&& item); // O(1) NIEOBOWIAZKOWE
    void push_back(const T& item); // O(1)
    void push_back(T&& item); // O(1) NIEOBOWIAZKOWE
    T& front() const { return head->value; } // zwraca poczatek, nie usuwa
    T& back() const { return tail->value; } // zwraca koniec, nie usuwa
    void pop_front(); // usuwa poczatek O(1)
    void pop_back(); // usuwa koniec O(1)
    void clear(); // czyszczenie listy z elementow O(n)
    void display(); // O(n)
    void display_reversed(); // O(n)

    // Operacje z indeksami. NIEOBOWIAZKOWE
    T& operator[](int pos); // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const; // dostep do obiektu const
    void erase(int pos);
    int index(const T& item); // jaki index na liscie (-1 gdy nie ma) O(n)
    void insert(int pos, const T& item); // inserts item before pos,
    void insert(int pos, T&& item); // inserts item before pos,
    // Jezeli pos=0, to wstawiamy na poczatek.
    // Jezeli pos=size(), to wstawiamy na koniec.
};

template <typename T>
DoubleList<T>::~DoubleList() {
    clear();
}

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) {
    head = tail = nullptr;
    DoubleNode<T>* temp = other.head;
    while (temp != nullptr) {
        push_back(temp->value);
        temp = temp->next;
    }
}

template <typename T>
DoubleList<T>::DoubleList(DoubleList&& other) {
    head = other.head;
    tail = other.tail;
    other.head = other.tail = nullptr;
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) {
        clear();
        DoubleNode<T>* temp = other.head;
        while (temp != nullptr) {
            push_back(temp->value);
            temp = temp->next;
        }
    }
    return *this;
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& other) {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        other.head = other.tail = nullptr;
    }
    return *this;
}

template <typename T>
int DoubleList<T>::size() const {
    int count = 0;
    DoubleNode<T>* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail = new DoubleNode<T>(item, nullptr, tail);
        tail->prev->next = tail;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail = new DoubleNode<T>(std::move(item), nullptr, tail);
        tail->prev->next = tail;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::pop_front() {
    if (!empty()) {
        DoubleNode<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
    }
}

template <typename T>
void DoubleList<T>::pop_back() {
    if (!empty()) {
        DoubleNode<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
    }
}

template <typename T>
void DoubleList<T>::clear() {
    DoubleNode<T>* temp = head;
    while (temp != nullptr) {
        DoubleNode<T>* next = temp->next;
        delete temp;
        temp = next;
    }
    head = tail = nullptr;
}

template <typename T>
void DoubleList<T>::display() {
    DoubleNode<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->value << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <typename T>
void DoubleList<T>::display_reversed() {
    DoubleNode<T>* current = tail;
    while (current) {
        std::cout << current->value << ' ';
        current = current->prev;
    }
    std::cout << std::endl;
}

template <typename T>
T& DoubleList<T>::operator[](int pos) {
    assert(pos >= 0 && pos < size());
    DoubleNode<T>* current = head;
    for (int i = 0; i < pos; ++i)
        current = current->next;
    return current->value;
}

template <typename T>
const T& DoubleList<T>::operator[](int pos) const {
    assert(pos >= 0 && pos < size());
    DoubleNode<T>* current = head;
    for (int i = 0; i < pos; ++i)
        current = current->next;
    return current->value;
}

template <typename T>
void DoubleList<T>::erase(int pos) {
    assert(pos >= 0 && pos < size());
    if (pos == 0)
        pop_front();
    else if (pos == size() - 1)
        pop_back();
    else {
        DoubleNode<T>* current = head;
        for (int i = 0; i < pos; ++i)
            current = current->next;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }
}

template <typename T>
int DoubleList<T>::index(const T& item) {
    int pos = 0;
    for (DoubleNode<T> *current = head; current != nullptr; current = current->next, ++pos) {
        if (current->value == item) {
            return pos;
        }
    }
    return -1;
}

template <typename T>
void DoubleList<T>::insert(int pos, const T& item) {
    if (pos == 0) {
        push_front(item);
    } else if (pos == size()) {
        push_back(item);
    } else {
        DoubleNode<T> *current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        current->next = new DoubleNode<T>(item, current->next, current);
        current->next->next->prev = current->next;
    }
}

template <typename T>
void DoubleList<T>::insert(int pos, T&& item) {
    if (pos == 0) {
        push_front(std::move(item));
    } else if (pos == size()) {
        push_back(std::move(item));
    } else {
        DoubleNode<T> *current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        current->next = new DoubleNode<T>(std::move(item), current->next, current);
        current->next->next->prev = current->next;
    }
}

#endif

// EOF