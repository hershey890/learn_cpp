#include <vector>
#include <iostream>

template<typename T, typename Oper>
void map(T& container, Oper op) {
    for(auto& x: container)
        x = op(x);
}

template<typename T>
void print(const T& container) {
    for(auto& x: container)
        std::cout << x << " ";
    std::cout << std::endl;
}

// todo: write something using [&]

int main() {
    std::vector<int> vec{0,1,2,3,4};
    map(vec, [](int& x){ return x*x; });
    print(vec);

    int a = 10;
    map(vec, [&a](const int& x) {return x<a; });
    print(vec);

    return 0;
}   