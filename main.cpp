#include "extendable_vector.hpp"
#include "single_linked_list.hpp"

#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	ExtendableArray<int> v;

	for (int i = 0; i < 10; i++)
		v.push_back(i);

	for (auto x : v)
		cout << x << ",";

	cout << endl;
	return 0;
}