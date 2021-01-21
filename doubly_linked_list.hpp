//
// doubly linked lists with dummy nodes as head and tail
//

#pragma once

#include <iostream>
#include <iterator>

using namespace std;

template<typename T>
class DoublyLinkedList {
	private:
		template<typename Type>
		struct Node{
			Type data;
			Node<Type>* next;
			Node<Type>* prev;

			Node() = delete;
			Node(const Type& data) : Node(data, nullptr, nullptr) { }
			Node(const Type& data, Node<Type>* next, Node<Type>* prev) :
				data(data), next(next), prev(prev) { }
		};

		Node<T>* head;
		Node<T>* tail;
		size_t size_;

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

			protected:
				pointer ptr_;
		};
		iterator begin() { return iterator(head->next); }
		iterator end() { return iterator(tail); }


		DoublyLinkedList() : head(new Node<T>(T())), tail(new Node<T>(T())), size_(0) {
			head->next = tail;
			tail->prev = head;
		}
		DoublyLinkedList(const DoublyLinkedList& rhs) : DoublyLinkedList() {
			for (auto elem : rhs)
				push_back(elem);
		}
		DoublyLinkedList& operator=(const DoublyLinkedList& rhs) {
			if (this != &rhs) {
				// optimized code:
				auto it = begin();
				for (Node<T>* curr = rhs.head->next; curr->next; curr = curr->next) {
					if (it == end())
						it = insert(it, curr->data);
					else
						*it = curr->data;
					it++;
				}

				while(it != end())
					it = erase(it);
			}
			return *this;
		}
		~DoublyLinkedList() { clear(); }

		bool empty() {
			return head->next == tail;
		}

		T& front() { return head->next->data; }
		T& back() { return tail->prev->data; }
		size_t size() { return size_; } // or iterator through the list

		void push_front(const T& data) {
			head->next = new Node<T>(data, head->next, head);
			head->next->next->prev = head->next;
			++size_;

			// insert(begin(), data);
		}
		void pop_front() {
			Node<T>* temp = head->next;
			head->next = head->next->next;
			head->next->prev = head;
			--size_;

			delete temp;
			// erase(begin());
		}
		void push_back(const T& data) {
			tail->prev = new Node<T>(data, tail, tail->prev);
			tail->prev->prev->next = tail->prev;
			++size_;

			// insert(end(), data);
		}
		void pop_back() {
			Node<T>* temp = tail->prev;
			tail->prev = tail->prev->prev;
			tail->prev->next = tail;
			--size_;

			delete temp;
			// erase(--end());
		}
		iterator insert(iterator it, const T& data) {
			Node<T>* curr = it.node();
			curr->prev->next = new Node<T>(data, curr, curr->prev);
			curr->prev = curr->prev->next;
			++size_;

			return iterator(curr->prev);
		}
		iterator erase(iterator it) {
			Node<T>* curr = it.node(), *next = curr->next;
			curr->next->prev = curr->prev;
			curr->prev->next = curr->next;
			--size_;

			delete curr;
			return next;
		}

		void clear() {
			while(!empty())
				pop_front();

			delete head;
			delete tail;
		}
		void reverse() {
			Node<T>* curr = head;
			head = tail;
			tail = curr;

			Node<T>* prev = nullptr;
			while(curr) {
				prev = curr->prev;
				curr->prev = curr->next;
				curr->next = prev;
				curr = curr->prev;
			}
		}
};