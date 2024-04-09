/**
 * Barebones tuple implementation to explore variadic templates
 */

#include <iostream>
#include <string>

namespace Hersh {

/* Primary template for tuple */
template<typename... Types>
struct Tuple {};

template<typename Head, typename... Tail>
struct Tuple<Head, Tail...> {
	Head head;
	Tuple<Tail...> tail;
	Tuple(Head h, Tail... t) : head(h), tail(t...) {}
};

template<typename Head>
void printTuple(const Tuple<Head>& tuple) {
	std::cout << tuple.head << std::endl;
}

template<typename Head, typename... Tail>
void printTuple(const Tuple<Head, Tail...>& tuple) {
	std::cout << tuple.head << " ";
	printTuple(tuple.tail);
}

}

int main() {
	Hersh::Tuple<int, char> myTuple(1, 'a');
	printTuple(myTuple);
	return 0;
}
