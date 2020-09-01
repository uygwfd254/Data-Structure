#include<iostream>
#include<iterator>
#include<stdexcept>

using namespace std;

template <typename T>
class ExtendableArray {
	private:
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
				type operator++(int) { type i = *this; ptr_++; return i; }
				T& operator*() { return *ptr_; }
				pointer operator->() { return ptr_; }
				bool operator==(const type& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const type& rhs) { return ptr_ != rhs.ptr_; }
				friend ostream& operator<<(ostream& out, const iterator& data) {
					out << data;
					return out;
				}

			private:
				pointer ptr_;
		};


		ExtendableArray(size_t size = 0) :
			size_(0), capacity_(size), array_(new T[capacity_]) { }
		~ExtendableArray() { delete[] array_; }
		ExtendableArray(const ExtendableArray& input) {
			size_ = input.size_;
			capacity_ = input.capacity_;
			array_ = new T[capacity_];
			for (auto& elem : input.array_)
				array_->push_back(elem);
		}
		ExtendableArray& operator=(const ExtendableArray& rhs) {
			if (this != &rhs) {
				delete[] array_;
				size_ = rhs.size_;
				capacity_ = rhs.capacity_;
				array_ = new T[capacity_];
				for (auto& elem : rhs.array_)
					array_->push_back(elem);
			}
			return *this;
		}

		size_t size() { return size_; }
		size_t capacity() { return capacity_; }
		bool empty() { return size_ == 0; }

		T& at(size_t index) {
			if (size_ <= index)
				throw out_of_range("index out of range");
			return array_[index];
		}
		T& operator[](size_t index) { return array_[index]; }

		void push_back(const T& value) {
			array_[size_++] = value;
		}
		void pop_back() {
			if (empty()) {
				T new_value = new T;
				array_[--size_] = *new_value;
				delete new_value;
			}
		}
		void set(size_t index, const T& value) { at(index) = value; }

		iterator begin() { return iterator(array_); }
		iterator end() { return iterator(array_ + size_); }
};

int main(int argc, const char* argv[]) {
	ExtendableArray<int> a;
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);

	for (auto& elem : a) {
		cout << elem;
	}

	return 0;
}