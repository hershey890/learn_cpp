#include <future>
#include <thread>
#include <iostream>

using namespace std;

void f(promise<int>& px) {
	try {
		int res;
		res = 1;
		px.set_value(res);
	} catch(...) { // generic catch all exceptions (this is trash code)
		px.set_exception(current_exception());
	}
}

void g(future<int>& fx) {
	try {
		int res = fx.get();
		// use v
	} catch(...) {
		// handle error
	}
}

int main() {
	
}
