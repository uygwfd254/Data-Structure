#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>

using namespace std;

template <typename T>
class ExtendableArray {
	private:
		static const size_t INITIAL_CAPACITY = 1;
		size_t size_;
		size_t capacity_;
		T* array_;

	public:

		class iterator {
			public:
				typedef iterator type;
				typedef T* pointer;

				iterator(pointer ptr) : ptr_(ptr) { }
				type operator++() { ptr_++; return *this; }
				type operator++(int) { type i = ptr_; ptr_++; return i; }
				type operator--() { ptr_--; return ptr_; }
				type operator--(int) { type i = ptr_; ptr_--; return i; }
				type operator+(int step) { type i = ptr_ + step; return i; }
				type operator-(int step) { type i = ptr_ - step; return i; }
				T& operator*() { return *ptr_; }
				pointer operator->() { return ptr_; }
				bool operator==(const type& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const type& rhs) { return ptr_ != rhs.ptr_; }
				bool operator<(const type& rhs) { return ptr_ < rhs.ptr_; }
				bool operator>(const type& rhs) { return ptr_ > rhs.ptr_; }
				bool operator<=(const type& rhs) { return ptr_ <= rhs.ptr_; }
				bool operator>=(const type& rhs) { return ptr_ >= rhs.ptr_; }
				friend ostream& operator<<(ostream& out, const iterator& data) {
					out << data;
					return out;
				}

			private:
				pointer ptr_;
		};
		iterator begin() { return iterator(array_); }
		iterator end() { return iterator(array_ + size_); }


		ExtendableArray() :
			size_(0), capacity_(INITIAL_CAPACITY), array_(new T[capacity_]) { }
		~ExtendableArray() { delete[] array_; }
		ExtendableArray(const ExtendableArray& input) {
			size_ = input.size_;
			capacity_ = input.capacity_;
			array_ = new T[capacity_];
			for (int i = 0; i < size_; ++i)
				array_[i] = input.array_[i];
		}
		ExtendableArray& operator=(const ExtendableArray& rhs) {
			if (this != &rhs) {
				delete[] array_;
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				array_ = new T[capacity_];
				for (int i = 0; i < size_; ++i)
					array_[i] = rhs.array_[i];
			}
			return *this;
		}

		size_t size() { return size_; }
		size_t capacity() { return capacity_; }
		bool empty() { return size_ == 0; }
		void reserve(size_t new_capacity) {
			if (new_capacity <= capacity_)
				return;

			T* new_array = new T[new_capacity];
			for (int i = 0; i < size_; i++)
				new_array[i] = array_[i];

			delete[] array_;
			array_ = new_array;
			capacity_ = new_capacity;
		}

		T& at(size_t index) {
			if (size_ <= index)
				throw out_of_range("index out of range");
			return array_[index];
		}
		T& operator[](size_t index) { return array_[index]; }
		T& front() { return array_[0]; }
		T& back() { return array_[size_ - 1]; }

		void push_back(const T& value) {
			if (size_ >= capacity_)
				reserve(2 * capacity_);
			array_[size_++] = value;
		}
		void pop_back() {
			if (!empty()) {
				array_[--size_] = T();
			}
		}
		void set(size_t index, const T& value) { at(index) = value; }
		void insert(iterator index_it, const T& value) {
			if (end() < index_it)
				throw out_of_range("index out of range");

			if (size_ >= capacity_)
				reserve(2 * capacity_);

			for (iterator it = end(); index_it != it; it--)
				*it = *(it - 1);

			*index_it = value;
			size_++;
		}
		void erase(iterator index_it) {
			if (end() <= index_it)
				throw out_of_range("index out of range");

			for (iterator it = index_it + 1; it != end(); it++)
				*(it - 1) = *it;
			size_--;
		}
		void clear() {
			delete[] array_;
			size_ = 0;
			capacity_ = INITIAL_CAPACITY;
			array_ = new T[capacity_];
		}
};