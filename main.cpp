#include "extendable_vector.hpp"
#include "singly_linked_list.hpp"
#include "doubly_linked_list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "binary_search_tree.hpp"
#include "avl_tree.hpp"
#include "pair.hpp"

#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	AVLTree<int, char> avl;
	int num[] = {50, 25, 80, 10, 65, 100, 30, 28, 110, 1, 40, 35};
	//int num[] = {10, 5, 20, 30};
	for (int x : num) {
		avl.insert(make_Pair(x, 'a'));
	}

	// for (int x : avl) {
	// 	cout << x << endl;
	// }
	avl.print();
	avl.erase(65);
	avl.print();

	return 0;
}