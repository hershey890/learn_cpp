#include "MyVector.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

int main() {
    Hersh::MyVector<int> mv1;
    Hersh::MyVector<int> mv2((int)5);

    mv2[0];
    mv2[0] = 5;
    assert(mv2[0] == 5);
    mv2.push_back(1);
    assert(mv2[0] == 5);
    assert(mv2[5] == 1);
    mv2.resize(7);
    assert(mv2[0] == 5);
    assert(mv2[5] == 1);
    assert(mv2[6] == 0);
    assert(mv2.size() == 7);
    assert(*(mv2.begin()) == mv2[0]);
    assert(mv2[0] == 5);
    int arr[] = {5,0,0,0,0,1,0};
    int i = 0;
    for(auto it=mv2.begin(); it != mv2.end(); it++)
        assert(arr[i++] == *it);
    assert(mv2.end() - mv2.begin() == 7);

    // mv2.begin() + 5;
    Hersh::MyVector<int> mv3(mv2.begin()+5, mv2.end());
    int arr2[] = {1,0};
    i = 0;
    for(auto it=mv3.begin(); it != mv3.end(); it++)
        assert(*it == arr2[i++]);

    const Hersh::MyVector<int> mv4(5);
    mv4[0];

    return 0;
}