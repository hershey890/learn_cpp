#include <iostream>
#include <cstdarg> // for variadic functions

using namespace std;

/* Variadic Template */
template<typename... Args>
void printArgs(Args... args) {
	cout << "Number of arguments: " << sizeof...(args) << endl;
	cout << "Arguments: ";
	((cout << args << " "), ...); // fold expression C++17
	cout << endl;
}

/* Recursive base case */
template<typename T>
void printArgs2(T t) {
	cout << t << endl;
}

template<typename T, typename... Args>
void printArgs2(T t, Args... args) {
	cout << t << " ";
	printArgs2(args...);	
}

/* Base Case */
template<typename T>
T sum(T t) {
	return t;
}

template<typename T, typename... Args>
T sum(T t, Args... args) {
	return t + sum(args...);
}

int main() {
	printArgs(1,2,3,4,5);
	printArgs("Hello", "world");
	printArgs2('a', 'b', 'c');
	cout << "Sum: " << sum<double>(1, 2.0, 3.5) << endl;
	cout << "Sum: " << sum<int>(1, 2, 3) << endl;
}
