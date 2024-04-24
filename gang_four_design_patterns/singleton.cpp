/**
 * Based on wikipedia https://en.wikipedia.org/wiki/Singleton_pattern,
 * not the book or the youtube videos
 */
#include <iostream>

class Singleton {
public:
    Singleton(const Singleton&) = delete; // rule of 3, prevents copying
    Singleton& operator=(const Singleton&) = delete;
    // defines a class operation that lets clients access its unique instance
    static Singleton& get() {
        // may be responsible for creating its own unique instance
        if(instance == nullptr)
            instance = new Singleton;
        return *instance;
    }
    static void destruct() {
        delete instance;
        instance = nullptr;
    }
    int getValue() {
        return value;
    }
    void setValue(int v) {
        value = v;
    }
private:
    Singleton() = default;
    ~Singleton() = default;
    static Singleton* instance;
    int value;
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton::get().setValue(1);
    std::cout << Singleton::get().getValue() << std::endl;
    Singleton::destruct();

    Singleton& s = Singleton::get();
    std::cout << s.getValue() << std::endl;
    s.setValue(2);
    std::cout << s.getValue() << std::endl;

    Singleton& s2 = Singleton::get();
    std::cout << s2.getValue() << std::endl;
    return 0;
}