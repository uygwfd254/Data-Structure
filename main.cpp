#include "extendable_vector.hpp"
//#include "singly_linked_list.hpp"
#include "doubly_linked_list.hpp"

#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	DoublyLinkedList<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.pop_front();
	l.pop_back();
	l.pop_back();

	for (auto elem : l)
		cout << elem;

	return 0;
}