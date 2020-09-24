//#include "extendable_vector.hpp"
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

	DoublyLinkedList<int> l2;
	l2.push_back(6);
	l2.push_back(7);
	l2.push_back(8);
	l2.push_back(9);
	l2.push_back(10);
	l2.push_back(11);
	l2.push_back(12);

	l2 = l;

	l2.push_back(20);
	l2.reverse();
	l2.push_back(10);

	for (auto elem : l2)
		cout << elem << " ";

	return 0;
}