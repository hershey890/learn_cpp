#include <iostream>
#include <memory>
#include <string>
#include <list>

using namespace std;

template<typename T>
class MyVector {
private:
    // T* elem; // points to an arr of sz elements of type T
    unique_ptr<T[]> elem;
    int sz;
public:
    explicit MyVector(int s); 
    // ~Vector() {
    //     delete[] elem;
    // }

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
        // return &x[0];
        return x.elem.get();
    }

    friend T* end(MyVector<T>& x) {
        // return &x[0]+x.size();
        return x.elem.get() + x.size();
    }
};

template<typename T>
MyVector<T>::MyVector(int s) {
    if(s < 0)
        throw length_error("Vector constructor: negative size");
    // elem = new T[s];
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






// #include <iostream>
// #include <memory> // for std::unique_ptr

// template<typename T>
// class DynamicArrayWrapper {
// private:
//     std::unique_ptr<T[]> data; // Pointer to dynamically allocated array
//     size_t size; // Size of the array

// public:
//     // Constructor
//     explicit DynamicArrayWrapper(size_t size) : size(size) {
//         data = std::make_unique<T[]>(size);
//     }

//     // Destructor (automatically deallocates memory)
//     ~DynamicArrayWrapper() = default;

//     // Copy constructor (deleted to prevent copying)
//     DynamicArrayWrapper(const DynamicArrayWrapper&) = delete;

//     // Move constructor
//     DynamicArrayWrapper(DynamicArrayWrapper&& other) noexcept {
//         data = std::move(other.data);
//         size = other.size;
//         other.size = 0;
//     }

//     // Assignment operator (deleted to prevent copying)
//     DynamicArrayWrapper& operator=(const DynamicArrayWrapper&) = delete;

//     // Move assignment operator
//     DynamicArrayWrapper& operator=(DynamicArrayWrapper&& other) noexcept {
//         if (this != &other) {
//             data = std::move(other.data);
//             size = other.size;
//             other.size = 0;
//         }
//         return *this;
//     }

//     // Accessor to get element at index
//     T& operator[](size_t index) {
//         if (index >= size) {
//             throw std::out_of_range("Index out of range");
//         }
//         return data[index];
//     }

//     // Const accessor to get element at index
//     const T& operator[](size_t index) const {
//         if (index >= size) {
//             throw std::out_of_range("Index out of range");
//         }
//         return data[index];
//     }

//     // Function to get the size of the array
//     size_t getSize() const {
//         return size;
//     }

//     // Iterator pointing to the beginning of the array
//     T* begin() {
//         return data.get();
//     }

//     // Iterator pointing to the end of the array
//     T* end() {
//         return data.get() + size;
//     }
// };

// int main() {
//     // Example usage
//     DynamicArrayWrapper<int> array(5);
//     for (int i = 0; i < array.getSize(); ++i) {
//         array[i] = i * 2;
//     }

//     std::cout << "Array elements:" << std::endl;
//     for (auto it = array.begin(); it != array.end(); ++it) {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
