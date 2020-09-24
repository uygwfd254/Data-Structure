#include "extendable_vector.hpp"
//#include "singly_linked_list.hpp"
//#include "doubly_linked_list.hpp"
//#include "stack.hpp"
#include "queue.hpp"

#include <iostream>

using namespace std;

int main(int argc, const char* argv[]) {
	// QueueExtendableArray<int> q;

	// q.push(1);
	// q.push(2);
	// q.push(3);
	// q.push(4);
	// q.push(5);

	// while(!q.empty()) {
	// 	cout << q.front() << " ";
	// 	q.pop();
	// }

	ExtendableArray<int> v;
	v.insert(v.begin(), 1);
	v.insert(v.begin(), 2);
	// v.insert(v.begin(), 3);
	// v.insert(v.begin(), 4);

	for (auto e : v)
		cout << e << " ";


	return 0;
}