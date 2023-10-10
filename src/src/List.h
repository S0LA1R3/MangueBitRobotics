#ifndef LIST_H
#define LIST_H

template <typename T>
class ListIterator;

template <typename T>
class List {
private:
  T* current;
  T* data;
  size_t capacity;
  size_t size;

public:
  List() : data(nullptr), capacity(0), size(0) {}

  void push_back(const T& value) {
    if (size >= capacity) {
      if (capacity == 0) {
        capacity = 1;
      } else {
        capacity *= 2;
      }
      T* newData = new T[capacity];
      for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
      }
      delete[] data;
      data = newData;
    }
    data[size] = value;
    size++;
  }

  T& operator[](size_t index) {
    if (index < size) {
      return data[index];
    }
  }

  size_t getSize() const {
    return size;
  }

  size_t getCapacity() const {
    return capacity;
  }

  bool empty() const {
    return size == 0;
  }

  void pop_back() {
    if (size > 0) {
      size--;
    }
  }

  using iterator = ListIterator<T>;

  iterator begin() {
    return iterator(data);
  }

  iterator end() {
    return iterator(data + size);
  }
};

template <typename T>
class ListIterator {
private:
  T* current;

public:
  ListIterator(T* ptr) : current(ptr) {}

  T& operator*() {
    return *current;
  }

  ListIterator& operator++() {
    current++;
    return *this;
  }

  bool operator!=(const ListIterator& other) const {
    return current != other.current;
  }
};

#endif
