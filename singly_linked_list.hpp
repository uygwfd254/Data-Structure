//
// singly linked lists with dummy nodes as head
//

#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>

using namespace std;

template<typename T>
struct Node{
	T data;
	Node<T>* next;

	Node() = delete;
	Node(const T& data) : Node(data, nullptr) { }
	Node(const T& data, Node<T>* next) :
		data(data), next(next) { }
};

template<typename T>
class SinglyLinkedList {
	private:
		Node<T>* head;
		Node<T>* tail;

	public:

		class iterator {
			public:
				typedef iterator type;
				typedef Node<T>* pointer;

				iterator(pointer ptr) : ptr_(ptr) { }
				iterator() : ptr_(nullptr) { }
				type operator++() { ptr_ = ptr_->next; return *this; }
				type operator++(int) { type i = ptr_; ptr_ = ptr_->next; return i; }
				// type operator+(int step) {
				// 	type it = ptr_;
				// 	for (int i = 0; i < step; i++)
				// 		it = it->next;
				// 	return it;
				// }
				T& operator*() { return ptr_->data; }
				T* operator->() { return &ptr_->data; }
				pointer node() { return ptr_; }
				bool operator==(const type& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const type& rhs) { return ptr_ != rhs.ptr_; }
				bool operator!() { return ptr_ != nullptr; }
				// friend ostream& operator<<(ostream& out, const iterator& data) {
				// 	out << data.ptr_->data;
				// 	return out;
				// }
				friend class SinglyLinkedList;

			protected:
				pointer ptr_;
		};
		iterator before_begin() { return iterator(head); }
		iterator begin() { return iterator(head->next); }
		iterator end() { return iterator(tail->next); }


		SinglyLinkedList() : head(new Node<T>(T(), nullptr)), tail(nullptr) { }
		~SinglyLinkedList() { clear(); }
		SinglyLinkedList(const SinglyLinkedList& rhs) : SinglyLinkedList() {
			auto it = before_begin();
			for (Node<T>* curr = rhs.head->next; curr; curr = curr->next)
				it = insert_after(it, curr->data);
		}
		SinglyLinkedList& operator=(const SinglyLinkedList& rhs) {
			if (this != &rhs) {
				clear();

				head = new Node<T>(T(), nullptr);
				auto it = before_begin();
				for (Node<T>* curr = rhs.head->next; curr; curr = curr->next)
					it = insert_after(it, curr->data);
			}
			return *this;
		}

		bool empty() { return head->next == nullptr; }
		size_t size() = delete;
		// method 1:
		// have a size variable, increment or
		// decrement as list grow or shrink
		// method 2:
		// iterate through the list and
		// count the nodes

		T& front() { return head->next->data; }
		// T& back() { return tail->data; }

		void push_front(const T& data) {
			Node<T>* temp = head->next;
			head->next = new Node<T>(data, temp);

			if (!head->next->next)
				tail = head->next;
		}
		void pop_front() {
			Node<T>* temp = head->next;
			head->next = temp->next;
			delete temp;
		}
		// append recursive:
		// private: void append_helper(Node<T>*& curr, const T& data) {
		// 	if (!curr) {
		// 		curr = new Node<T>(data);
		// 		tail = curr;
		// 	} else
		// 		append_helper(curr->next, data);
		// }
		// public: void append(const T& data) { append_helper(head, data); }
		// append iterative:
		// void append(const T& data) {
		// 	Node<T>* curr = head;
		// 	while(curr->next) {
		// 		curr = curr->next;
		// 	}
		// 	curr->next = new Node<T>(data);
		// 	tail = curr->next;
		// }
		// append using tail:
		// void append(const T& data) {
		// 	tail->next = new Node<T>(data);
		// 	tail = tail->next;
		// }
		iterator insert_after(iterator it, const T& data) {
			Node<T>* temp = it.ptr_->next;
			it.ptr_->next = new Node<T>(data, temp);

			if (!temp)
				tail = it.ptr_->next;
			return it.ptr_->next;
		}
		iterator erase_after(iterator it) {
			Node<T>* temp = it.ptr_->next;
			it.ptr_->next = it.ptr_->next->next;
			delete temp;

			if (!it.ptr_->next)
				tail = it.ptr_;
			return it.ptr_->next;
		}
		void clear() {
			while(!empty())
				pop_front();
			delete head;

			// alternative method: recursion
			// delete head;
			// in node class:
			// ~Node() {
			// 	if (!next)
			// 		return;
			// 	delete next;
			// }
		}
		void resize(size_t n) {
			bool is_done = false;
			iterator it = begin(), p;
			for (int i = 0; i < n; i++) {
				if (!it) {
					p = it;
				 	it++;
				} else {
					is_done = true;
				 	p = insert_after(p, T());
				}
			}

			if (!is_done) {
				it = p;
				while(!++p) {
					p = it;
					erase_after(p);
				}
			}
		}

		void reverse() {
			Node<T>* curr = head->next,
				*prev = nullptr,
				*next = nullptr;

			tail = curr;
			while (curr) {
				next = curr->next;
				curr->next = prev;
				prev = curr;
				curr = next;
			}

			delete head;
			head = new Node<T>(T(), prev);
		}
};