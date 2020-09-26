//#include "extendable_vector.hpp"
//#include "singly_linked_list.hpp"
//#include "doubly_linked_list.hpp"
//#include "stack.hpp"
//#include "queue.hpp"
#include "binary_search_tree.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]) {
	BinarySearchTree<int, string> t;
	BinarySearchTree<int, string> t1;

	t.insert(20, "aa");
	t.insert(30, "bb");
	t.insert(35, "cc");
	t.insert(40, "dd");
	t.insert(32, "ee");
	t.insert(37, "ff");
	t.insert(60, "gg");
	t.insert(45, "hh");
	t.insert(50, "ii");

	t.erase(30);
	t1 = t;
	cout << endl;
	t1.inorder();


	return 0;
}