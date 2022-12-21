#include <algorithm> 
#include <iostream>
#include <vector>  // make_heap, push_heap, pop_heap

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; // działa domyślny konstruktor dla std::vector
public:
    MyPriorityQueue(int s=10) { lst.reserve(s); } // default constructor
    ~MyPriorityQueue() { lst.clear(); }
    MyPriorityQueue(const MyPriorityQueue& other)
    {
        lst.reserve(10);
        lst = other.lst;
    } // copy constructor
    MyPriorityQueue(MyPriorityQueue&& other)
    {
        lst = other.lst;
        other.lst.clear();
    } // move constructor
    MyPriorityQueue& operator=(const MyPriorityQueue& other)
    {
        this->lst.clear();
        lst.reserve(10);
        lst = other.lst;
        return *this;
    } // copy assignment operator, return *this
    MyPriorityQueue& operator=(MyPriorityQueue&& other)
    {
        this->lst.clear();
        lst = other.lst;
        other.lst.clear();
        return *this;
    } // move assignment operator, return *this
    bool empty() const { return lst.empty(); }
    int size() const { return lst.size(); } // liczba elementów w kolejce
    void push(const T& item) { // dodanie do kolejki
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }
    void push(T&& item) { // dodanie do kolejki
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }
    T& top() { return lst.front(); } // zwraca element największy, nie usuwa
    void pop() { // usuwa element największy
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }
    void clear() { lst.clear(); } // czyszczenie listy z elementów
    void display()
    {
        std::sort_heap(lst.begin(), lst.end());
        auto it = lst.begin();
        do{
            std::cout << *it <<" ";
            it++;
        }
        while (it != lst.end());
        std::cout << "\n";
    }
};