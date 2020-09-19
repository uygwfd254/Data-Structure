//
// doubly linked lists with dummy nodes as head and tail
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
	Node<T>* prev;

	Node() = delete;
	Node(const T& data) : Node(data, nullptr, nullptr) { }
	Node(const T& data, Node<T>* next, Node<T>* prev) :
		data(data), next(next), prev(prev) { }
};

template<typename T>
class DoublyLinkedList {
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
				type operator--() { ptr_ = ptr_->prev; return *this; }
				type operator--(int) { type i = ptr_; ptr_ = ptr_->prev; return i; }
				T& operator*() { return ptr_->data; }
				T* operator->() { return &ptr_->data; }
				pointer node() { return ptr_; }
				bool operator==(const type& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const type& rhs) { return ptr_ != rhs.ptr_; }
				bool operator!() { return ptr_ != nullptr; }

				friend class DoublyLinkedList;

			protected:
				pointer ptr_;
		};
		iterator begin() { return iterator(head->next); }
		iterator end() { return iterator(tail); }


		DoublyLinkedList() : head(new Node<T>(T())), tail(new Node<T>(T())) {
			head->next = tail;
			tail->prev = head;
		}
		DoublyLinkedList(const DoublyLinkedList& rhs) : DoublyLinkedList() {
			for (auto elem : rhs)
				push_back(elem);
		}
		~DoublyLinkedList() { clear(); }

		bool empty() {
			return head->next == tail;
		}

		void push_front(const T& data) {
			head->next = new Node<T>(data, head->next, head);
			head->next->next->prev = head->next;
		}
		void pop_front() {
			Node<T>* temp = head->next;
			head->next = head->next->next;
			head->next->prev = head;

			delete temp;
		}
		void push_back(const T& data) {
			tail->prev = new Node<T>(data, tail, tail->prev);
			tail->prev->prev->next = tail->prev;
		}
		void pop_back() {
			Node<T>* temp = tail->prev;
			tail->prev = tail->prev->prev;
			tail->prev->next = tail;

			delete temp;
		}
		void clear() {
			while(!empty())
				pop_front();

			delete head;
			delete tail;
		}
};