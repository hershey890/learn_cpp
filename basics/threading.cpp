#include <thread>
#include <queue>
#include <iostream>
#include <algorithm>
#include <functional>
#include <mutex>
#include <shared_mutex>

using namespace std;

shared_mutex m;

struct F{
    vector<double>& v;
    F(vector<double>& v) : v(v) {}
    void operator()() {
        for_each(v.begin(), v.end(), [](double& d) { d *= 5; });
    }
};

void f(vector<double>& v, const int& multiplier) {
    for_each(v.begin(), v.end(), [&](double& d) { d *= multiplier; });
}

void g() {
    cout << "HELLO FROM THREAD 2" << endl;
}

template<typename T>
void setter(vector<T>& v, const T& value) {
    unique_lock<shared_mutex> lock(m);
    for_each(v.begin(), v.end(), [&](T& d) { d = value; });
}

template<typename T>
void getter(const vector<T>& v) {
    shared_lock<shared_mutex> lock(m);
    for_each(v.begin(), v.end(), [](const T& v) { cout << v << " "; });
    cout << endl;
}

int main() {
    vector<double> v = {1, 2, 3, 4, 5};
    vector<double> w = {2, 3, 5};

    jthread t1 {f, ref(v), 5};
    jthread t2 {F{w}};
    t2.join();
    t1.join();
    for_each(v.begin(), v.end(), [](const double& d) { cout << d << " "; });
    cout << endl;
    for_each(w.begin(), w.end(), [](const double& d) { cout << d << " "; });
    cout << endl;

    jthread t3 {setter<double>, ref(v), 1.0};
    jthread t4 {getter<double>, cref(v)};
    jthread t5 {getter<double>, cref(v)};
}