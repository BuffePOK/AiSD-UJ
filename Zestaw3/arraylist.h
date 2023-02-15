#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <cassert>
#include <vector>
#include <iostream>

#ifndef MINSIZE
#define MINSIZE 4
#endif

template <typename T>

class ArrayList {
  public:
    ArrayList(unsigned size = MINSIZE) : _size{size}, _elCount{0} {
      _tab = new T[_size];
      assert(_tab != nullptr);
    }

    ~ArrayList() { delete [] _tab; }

    ArrayList(const ArrayList& other) : _size{other._size}, _elCount{other._elCount} { // copy constructor
      _tab = new T[_size];

      for (size_t i = 0; i < _elCount; i++)
        _tab[i] = other._tab[i];
    }

    ArrayList(ArrayList&& other) : _tab{other._tab}, _size{other._size}, _elCount{other._elCount} { // move constructor
      other._tab = nullptr;
      other._size = 0;
      other._elCount = 0;
    }

    ArrayList& operator=(const ArrayList& other) { // copy assigment operator, return *this
      if (this != &other) {
        delete [] _tab;

        _tab = new T[_size];
        _size = other._size;
        _elCount = other._elCount;

        for (int i = 0; i < _elCount; ++i) {
                _tab[i] = other._tab[i];
            }
      }

      return *this;
    }

    ArrayList& operator=(ArrayList&& other) { // move assigment operator, return *this
      if (this != &other) {
        delete [] _tab;

        _tab = new T[_size];
        _size = other._size;
        _elCount = other._elCount;

        other._tab = nullptr;
        other._size = 0;
        other._elCount = 0;
      }

      return *this;
    }

    bool empty() { return _elCount == 0; }
    unsigned size() { return _elCount; }
    unsigned max_size() { return _size; }
    bool full() { return _elCount == _size; }

    void push_front(const T& item) {
      if (++_elCount > _size)
        double_size();

      for (unsigned i = _elCount - 1; i > 0; i--)
        _tab[i] = _tab[i - 1];

      _tab[0] = item;
    }

    void push_front(T&& item) {
      if (++_elCount > _size)
        double_size();

      for (unsigned i = _elCount - 1; i > 0; i--)
        _tab[i] = std::move(_tab[i - 1]);

      _tab[0] = std::move(item);
    }

    void push_back(const T& item) {
      if (_elCount + 1 > _size)
        double_size();

      _tab[_elCount++] = item;
    }

    void push_back(T&& item) {
      if (_elCount + 1 > _size)
        double_size();

      _tab[_elCount++] = std::move(item);
    }

    T& front() {
      assert(!this->empty());

      return _tab[0];
    }

    T& back() {
      assert(!this->empty());

      return _tab[_elCount - 1];
    }


    T pop_front() {
      assert(!this->empty());

      if (_elCount - 1 <= _size / 2)
        half_size();

      T value = _tab[0];

      for (unsigned i = 0; i < _elCount; i++)
        _tab[i] = _tab[i + 1];

      _tab[_elCount--] = T();

      return value;
    }

    T pop_back() {
      assert(!this->empty());

      if (_elCount - 1 <= _size / 2)
        half_size();

      T value = _tab[--_elCount];

      _tab[_elCount] = T();

      return value;
    }


    void clear() {
      _size = MINSIZE, _elCount = 0;

      T* minTab = new T[_size];

      T* temp = _tab;
      _tab = minTab;
      delete [] temp;
    }

    T& get_index(unsigned pos) { return _tab[pos]; }

    void insert(const T& item, unsigned pos) {
      if (++_elCount > _size)
        double_size();

      for (unsigned i = _elCount; i > pos; i--)
        _tab[i] = _tab[i - 1];

      _tab[pos] = item;
    }

    void insert(T&& item, unsigned pos) {
      if (++_elCount > _size)
        double_size();

      for (unsigned i = _elCount; i > pos; i--)
        _tab[i] = std::move(_tab[i - 1]);

      _tab[pos] = std::move(item);
    }

    void erase(unsigned pos) {
      if (_elCount - 1 <= _size / 2)
        half_size();

      for (unsigned i = pos; i < _elCount; i++)
        _tab[i] = _tab[i + 1];

      _tab[_elCount--] = T();
    }

    std::vector<T> range(unsigned a, unsigned b) {
      if (b < a) {
        a = a + b;
        b = a - b;
        a = a - b;
      }

      std::vector<T> range(b - a + 1);

      for (size_t i = a; i <= b; i++)
        range[i - a] = _tab[i];

      return range;
    }

    void sort() {
      T temp;

      for (unsigned i = 0; i < _elCount; i++) {
        for (unsigned j = 0; j < _elCount; j++) {
          if (_tab[i] < _tab[j]) {
            temp = _tab[i];
            _tab[i] = _tab[j];
            _tab[j] = temp;
          }
        }
      }
    }

    void merge(ArrayList& other) {
      unsigned i = 0;

      while (!other.empty() && i != _elCount) {
        if (other.front() < _tab[i]) {
          this->insert(other.pop_front(), i);
        }

        i++;
      }

      while (!other.empty()) {
        this->push_back(other.pop_front());
      }
    }

    void display() {
      for (unsigned i = 0; i < _elCount; i++)
        std::cout << _tab[i] << ' ';

      std::cout << '\n';
    }

    void reverse() {
      unsigned i = 0, j = _elCount - 1;

      while (i < j) {
        T temp = _tab[i];
        _tab[i] = _tab[j];
        _tab[j] = temp;
        i++;
        j--;
      }
    }

    void double_size() {
      _size *= 2;

      T* expandedTab = new T[_size];

      for (unsigned i = 0; i < _elCount; i++)
        expandedTab[i] = _tab[i];

      T* temp = _tab;
      _tab = expandedTab;
      delete [] temp;
    }

    void half_size() {
      if (_size > MINSIZE)
        _size /= 2;

      T* halvedTab = new T[_size];

      for (unsigned i = 0; i < _elCount; i++)
        halvedTab[i] = _tab[i];

      T* temp = _tab;
      _tab = halvedTab;
      delete [] temp;
    }

    // podstawienie L[pos] = item
    T& operator[](unsigned pos) {
      std::cout << "podstawienie\n";
      if (pos < _size) return _tab[pos];
    }

    // odczyt L[pos]
    const T& operator[](unsigned pos) const { 
      std::cout << "odczyt\n";
      if (pos < _elCount) return _tab[pos];
    }

    friend std::ostream& operator<<(std::ostream& os, const ArrayList& L) {
        for (int i=0; i < L.last; ++i) { // odwolanie L.last
            os << L.tab[i] << " ";   // odwolanie L.tab
        }

        return os;
    }
  private:
    T* _tab;
    unsigned _size;
    unsigned _elCount;
};

#endif