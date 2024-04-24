/**
 * @brief PLaying around with friend functions and class members
 * 
 * https://learn.microsoft.com/en-us/cpp/cpp/friend-cpp?view=msvc-170
 */

#include <iostream>

using namespace std;

class A; // A has to be forward declared bc C uses it before it is defined

class C { // order matters. Since A has C::showA as a friend, C must be declared first
public:
    void showA(A& a);
};

class A {
private:
    int private_a = 5;
public:
    friend class B; // gives B access to private members of A
    friend void func_showA(A& a); // gives func_showA access to private members of A
    friend void C::showA(A& a); // gives C::showA access to private members of A
};

class B {
public:
    void showA(A& a) {
        cout << "B::showA: A::private_a = " << a.private_a << endl;
    }
};

void func_showA(A& a) {
    cout << "func_showA: A::private_a = " << a.private_a << endl;
}

void C::showA(A& a) {
    cout << "C::showA: A::private_a = " << a.private_a << endl;
}

int main(void) {
    A a;
    B b;
    C c;
    b.showA(a);
    func_showA(a);
    c.showA(a);
    return 0;
}