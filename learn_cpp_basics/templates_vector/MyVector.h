#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stddef.h>
#include <memory>
#include <stdexcept>

namespace Hersh {

template <typename T>
class MyVector {
private:
    // T* data;
    std::unique_ptr<T[]> data;    
    size_t data_size;
    size_t capacity;
    size_t max_capacity; // todo, not implemented

public:
    class iterator {
    private:
        T* ptr;
    
    public:
        iterator(T*);
        T& operator*();
        iterator& operator++(); // pre-increment
        iterator operator++(int x); // post-increment
        bool operator!=(const iterator&) const;
        ptrdiff_t operator-(const iterator&) const;
        iterator operator+(const int&) const;
    };

    MyVector();
    MyVector(size_t);
    MyVector(std::initializer_list<T>); // todo
    // template <typename Iter> // iterator-pair constructor [a,b) // todo
    MyVector(iterator, iterator);

    MyVector operator=(const MyVector<T>&); // todo
    T& operator[](const size_t);
    T operator[](const size_t) const;

    void push_back(const T&);
    void resize(const size_t);
    iterator begin() const;
    iterator end() const;
    size_t size() const;
    
    template <typename U>
        friend void swap(MyVector<U>& p, MyVector<U>& q); // todo
};

template <typename T>
MyVector<T>::iterator::iterator(T* p) : ptr(p) {}

template <typename T>
T& MyVector<T>::iterator::operator*() {
    return *ptr;
}

template <typename T>
typename MyVector<T>::iterator& MyVector<T>::iterator::operator++() { // prefix
    // todo: test
    ptr++;
    return *this;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator++(int x) { // postfix
    typename MyVector<T>::iterator* old_this = this;
    ptr++;
    return *old_this;
}

template <typename T>
bool MyVector<T>::iterator::operator!=(const iterator& other) const {
    return ptr != other.ptr;
}

template <typename T>
ptrdiff_t MyVector<T>::iterator::operator-(const typename MyVector<T>::iterator& other) const {
    return ptr - other.ptr;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator+(const int& other) const {
    MyVector<T>::iterator it = *this;
    it.ptr += other;
    return it;
}

template <typename T>
MyVector<T>::MyVector() : data(nullptr), data_size(0), capacity(0) {
    max_capacity = 1000000000 / sizeof(T); // todo, arbitrarily set max size as 1e9 bytes
    // todo, come up with an actualy value and set limits on the size in resizing the array
}

template <typename T>
MyVector<T>::MyVector(size_t sz) : data_size(sz), capacity(sz) {
    max_capacity = 1000000000 / sizeof(T); // todo, arbitrarily set max size as 1e9 bytes
    // todo, come up with an actualy value and set limits on the size in resizing the array
    data = std::make_unique<T[]>(sz);
    for(size_t i=0; i<data_size; i++)
        data[i] = 0;
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>::iterator a, MyVector<T>::iterator b) : data_size(b-a) {
    data = std::make_unique<T[]>(data_size);
    int i = 0;
    for(auto it=a; it != b; it++)
        data[i++] = *it;
}
    
template <typename T>
T& MyVector<T>::operator[](const size_t i) {
    if(i >= data_size)
        throw std::out_of_range("Array index out of bounds");
    return data[i];
}

template <typename T>
T MyVector<T>::operator[](const size_t i) const {
    if(i >= data_size)
        throw std::out_of_range("Array index out of bounds");
    return data[i];
}

template <typename T>
void MyVector<T>::push_back(const T& elem) {
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(data_size + 1);
    for(size_t i=0; i<data_size; i++)
        new_data[i] = data[i];
    swap(new_data, data);
    data[data_size] = elem;
    data_size++;
    capacity++;
}

template<typename T>
void MyVector<T>::resize(const size_t sz) {
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(sz);
    for(size_t i=0; i<std::max(sz, data_size); i++)
        new_data[i] = i < data_size ? data[i] : 0;
    data_size = sz;
    capacity = sz;
    swap(new_data, data);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() const {
    return MyVector<T>::iterator(data.get());
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() const {
    return MyVector<T>::iterator(data.get() + data_size);
}

template <typename T>
size_t MyVector<T>::size() const {
    return data_size;
}

}

#endif