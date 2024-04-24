#include <iostream>
#include <memory>
#include <string>
#include <list>

using namespace std;

template<typename T>
class MyVector {
private:
    unique_ptr<T[]> elem;
    int sz;
public:
    explicit MyVector(int s); 

    template<typename iter>
        MyVector(iter b, iter e);
    
    struct iterator {
        using value_type = T;
        // idk
    };

    iterator begin() {
        // 92
    };

    T& operator[](int i);
    const T& operator[](int i) const;
    int size() const {
        return sz;
    }

    friend T* begin(MyVector<T>& x) {
        return x.elem.get();
    }

    friend T* end(MyVector<T>& x) {
        return x.elem.get() + x.size();
    }
};

template<typename T>
MyVector<T>::MyVector(int s) {
    if(s < 0)
        throw length_error("Vector constructor: negative size");
    elem = make_unique<T[]>(s);
    sz = s;
}

template<typename T>
const T& MyVector<T>::operator[](int i) const {
    if(i < 0 || size() <= i)
        throw out_of_range("Vector::operator[]");
    return elem[i];
}

void write(const MyVector<string>& vs) {
    for(int i=0; i<vs.size(); i++)
        cout << vs[i] << endl;
}

void write2(MyVector<string>& vs) {
    for(auto& s : vs)
        cout << s << endl;
}

template<typename T, int N>
struct Buffer {
    constexpr int size() {
        return N;
    }
    T elem[N];
};



int main() {
    MyVector<char> vc(200);
    MyVector<string> vs(17);
    MyVector<list<int>> vli(45);

    Buffer<char,1024> buff;

    return 0;
}