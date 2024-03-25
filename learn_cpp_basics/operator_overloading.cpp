/*
 * Implenting the String class to practice operator overloading
 */
#include <vector>
#include <iostream>
#include <string.h>
#include <string>
#include <initializer_list>


class MyString {
    std::vector<char> data;

public:
    MyString() {}
    MyString(const char* str) {
        data.resize(strlen(str));
        for(size_t i=0; i<strlen(str); i++)
            data[i] = str[i];
    }

    MyString(const MyString& str) : data(str.data) {}

    MyString(std::initializer_list<char> lst) { // not working
        data.resize(lst.size());
        std::copy(lst.begin(), lst.end(), data.begin());
    }

    friend void swap(MyString& s1, MyString& s2) {
        std::swap(s1.data, s2.data);
    }

    MyString operator=(MyString str) {
        swap(*this, str);
        return *this;
    }

    char operator[](size_t index) const {
        if(index < 0 || index > data.size())
            throw std::out_of_range("Index out of bounds for MyString");
        return data[index];
    }

    char& operator[](size_t index) {
        if(index < 0 || index > data.size())
            throw std::out_of_range("Index out of bounds for MyString");
        return data[index];
    }

    // todo: could use templates here
    MyString& operator+=(const char* s1) {
        data.resize(data.size() + strlen(s1));
        for(size_t i=0; i<strlen(s1); i++)
            data[i+strlen(s1)] = s1[i];
        return *this;
    }

    // member means converts RHS
    MyString& operator+=(const MyString& s1) {
        size_t data_size = data.size();
        data.resize(data_size + s1.size());
        for(size_t i=0; i<s1.size(); i++)
            data[i+data_size] = s1[i];
        return *this;
    }

    // non-member means coverts LHS
    bool operator==(const MyString& s1) const {
        if(this->size() != s1.size())
            return false;
        for(int i=0; i<s1.size(); i++) {
            if(this->data[i] != s1[i])
                return false;
        }
        return true;
    }

    bool operator!=(const MyString& s1) const {
        return !(*this == s1);
    }

    size_t size() const {
        return data.size();
    }
};

// did I do this correctly? I want to use it as a non-member operator overloader
// but I want to be able to access the classes private data
MyString operator+(const char* s1, const MyString& s2) {
    MyString res(s1);
    res += s2;
    return res;
}

MyString operator+(MyString s1, const MyString& s2) {
    s1 += s2;
    return s1;
}

MyString operator+(MyString s1, const char* s2) {
    MyString res2(s2);
    s1 += res2;
    return s1;
}

// todo: declare as a friend
std::ostream& operator<<(std::ostream& os, const MyString& str) {
    for(size_t i=0; i<str.size(); i++)
        os << str[i];
    return os;
}


using namespace std;

int main() {
    const char str[] = "test";
    MyString s1(str);
    s1[0] = 'T';
    cout << s1[0] << endl;
    cout << s1.size() << endl;
    cout << s1 << endl;
    s1 = "Append " + s1;
    cout << "[4] " << s1 << endl;
    s1 = s1 + " Append2";
    cout << s1 << endl;
    s1 = "Append3 " + s1 + " Append3";
    cout << s1 << endl;
    s1 = s1 + s1;
    cout << s1 << endl;
    s1 += " Append4 ";
    cout << s1 << endl;
    s1 += MyString("Append5");
    cout << s1 << endl;
    cout << "equality test 1: " << (MyString("test2") == MyString("test2")) << endl;
    cout << "equality test 2: " << (MyString("test1") != MyString("test2")) << endl;
    s1 = MyString("abcd");
    cout << s1 << endl;
    cout << endl;

    const MyString s2(str);
    cout << s2[0] << endl;
    cout << s2.size() << endl;
    cout << s2 << endl;

    MyString s3({'t', 'e', 's', 't', '3'});
}