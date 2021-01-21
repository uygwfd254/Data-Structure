#include "extendable_vector.hpp"
#include "singly_linked_list.hpp"
#include "doubly_linked_list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "binary_search_tree.hpp"
#include "avl_tree.hpp"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char* argv[]) {
	AVLTree<int, char> avl;
	int num[] = {10, 25, 30, 5, 8, 28, 20, 22};

	for (int x : num) {
		avl.insert(x, 'a');
	}

	// for (int x : avl) {
	// 	cout << x << endl;
	// }
	avl.print();

	return 0;
}