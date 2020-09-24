//
// two method of implementing a stack
//
#pragma once

#include <iostream>
#include <iterator>

// required data structure
#include "singly_linked_list.hpp"
#include "extendable_vector.hpp"

using namespace std;

// singly linked list implementation
template<typename T>
class StackLinkedList {
	private:
		SinglyLinkedList<T> list;
		size_t size_;

	public:
		StackLinkedList() : list(SinglyLinkedList<T>()), size_(0) { }

		// push and pop is the same direction
		void push(const T& val) {
			list.push_front(val);
			++size_;
		}
		void pop() {
			list.pop_front();
			--size_;
		}

		T& top() { return list.front(); }

		bool empty() { return list.empty(); }
		size_t size() { return size_; }
};


// extendable array implementation
template<typename T>
class StackExtendableArray {
	private:
		ExtendableArray<T> array;
		size_t size_;

	public:
		StackExtendableArray() : array(ExtendableArray<T>()), size_(0) { }

		void push(const T& val) {
			array.push_back(val);
			++size_;
		}
		void pop() {
			array.pop_back();
			--size_;
		}
		T& top() { return array.back(); }

		bool empty() { return array.empty(); }
		size_t size() { return size_; }
};