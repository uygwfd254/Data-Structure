#pragma once

#include <iostream>

using namespace std;

template<typename T1, typename T2>
class Pair {
	public:
		T1 first;
		T2 second;

		Pair() : first(T1()), second(T2()) { }
		Pair(const T1& first, const T2& second) :
			first(first), second(second) { }

		Pair<T1, T2>* operator->() { return this; }
};

template<typename T1, typename T2>
Pair<T1, T2> make_Pair(const T1& first, const T2& second) {
	return Pair<T1, T2>(first, second);
}