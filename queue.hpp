//
// two method of implementing a queue
//
#pragma once

#include <iostream>
#include <iterator>

// required data structure
#include "doubly_linked_list.hpp"
#include "extendable_vector.hpp"

using namespace std;

// doubly linked list implmentation
template<typename T>
class QueueLinkedList {
	private:
		DoublyLinkedList<T> list;
		size_t size_;

	public:
		QueueLinkedList() : list(DoublyLinkedList<T>()), size_(0) { }

		// push and pop is opposite direction
		void push(const T& val) {
			list.push_back(val);
			++size_;
		}
		void pop() {
			list.pop_front();
			--size_;
		}

		T& front() { return list.top(); }
		T& back() { return list.back(); }

		bool empty() { return list.empty(); }
		size_t size() { return size_; }
};

// extendable array implementation
template<typename T>
class QueueExtendableArray {
	private:
		ExtendableArray<T> array;
		size_t size_;

	public:
		QueueExtendableArray() : array(ExtendableArray<T>()), size_(0) { }

		// push and pop is opposite direction
		void push(const T& val) {
			array.push_back(val);
			++size_;
		}
		void pop() {
			array.erase(array.begin());
			--size_;
		}

		T& front() { return array.front(); }
		T& back() { return array.back(); }

		bool empty() { return array.empty(); }
		size_t size() { return size_; }

		void print() {
			for (auto elem : array)
				cout << elem << " ";
		}
};