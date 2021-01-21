#pragma once

#include "stack.hpp"

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <cmath>

using namespace std;

template<typename K, typename V>
class AVLTree {
	private:
		// node class
		template<typename Key, typename Val>
		struct Node {
			Key key;
			Val val;

			Node<Key,Val>* left;
			Node<Key,Val>* right;

			Node() = delete;
			Node(const Key& key, const Val& val,
				Node<Key,Val>* left = nullptr, Node<Key,Val>* right = nullptr) :
				key(key), val(val), left(left), right(right) { }
		};

		Node<K, V>* root;

		void clear_helper(Node<K,V>* curr) {
			if (!curr)
				return;
			if (curr->left)
				clear_helper(curr->left);
			if (curr->right)
				clear_helper(curr->right);

			delete curr;
		}

		size_t size_helper(Node<K,V>* curr) {
			if (!curr)
				return 0;
			return size_helper(curr->left) + 1 + size_helper(curr->right);
		}

		Node<K,V>* copy(Node<K,V>* curr, Node<K,V>* prev) {
			if (!curr)
				return nullptr;

			Node<K,V>* temp = new Node<K,V>(curr->key, curr->val, prev,
				copy(curr->left, curr), copy(curr->right, curr));

			return temp;
		}

		Node<K,V>* search_helper(Node<K,V>* curr, const K& key) {
			if (!curr)
				throw invalid_argument("key not found");

			if (key == curr->key)
				return curr;
			else if (key < curr->key)
				return search_helper(curr->left, key);
			else
				return search_helper(curr->right, key);
		}
		int height(Node<K,V>* curr) {
			if (!curr)
				return -1;
			return 1 + max(height(curr->left), height(curr->right));
		}
		int balance_factor(Node<K,V>* curr) {
			return height(curr->left) - height(curr->right);
		}

		// tree rotation cases:
		Node<K, V>* left_left(Node<K, V>* node) {
			return rotate_right(node);
		}

		Node<K, V>* left_right(Node<K, V>* node) {
			node->left = rotate_left(node->left);
			return left_left(node);
		}

		Node<K, V>* right_right(Node<K, V>* node) {
			return rotate_left(node);
		}

		Node<K, V>* right_left(Node<K, V>* node) {
			node->right = rotate_right(node->right);
			return right_right(node);
		}

		Node<K, V>* rotate_left(Node<K, V>* node) {
			Node<K, V>* parent = node->right;
			node->right = parent->left;
			parent->left = node;
			return parent;
		}

		Node<K, V>* rotate_right(Node<K, V>* node) {
			Node<K, V>* parent = node->left;
			node->left = parent->right;
			parent->right = node;
			return parent;
		}

	public:
		// iterator class
		class iterator {
			protected:
				typedef iterator type;
				typedef Node<K, V>* pointer;

				iterator(pointer ptr) : ptr_(ptr) { }
				iterator() : ptr_(nullptr) { }
				pointer ptr_;
				StackLinkedList<pointer> stack_;

			public:
				friend class AVLTree;
				type operator++() {
					if (stack_.empty() && !ptr_->right) {
						ptr_ = ptr_->right;
						return *this;
					} else if (ptr_->right) {
						stack_.push(ptr_);
						ptr_ = ptr_->right;
						while(ptr_->left) {
							stack_.push(ptr_);
							ptr_ = ptr_->left;
						}
					} else if(stack_.top()->left == ptr_) {
						ptr_ = stack_.top();
						stack_.pop();
					} else {
						while(stack_.top()->right == ptr_) {
							ptr_ = stack_.top();
							stack_.pop();

							// for end iterator
							if (stack_.empty()) {
								while(ptr_) {
									ptr_ = ptr_->right;
								}
								return *this;
							}
						}
						if (!stack_.empty()) {
							ptr_ = stack_.top();
							stack_.pop();
						}
					}

					return *this;
				}
				type operator++(int) {
					pointer ptr = ptr_;
					++*this;
					return ptr;
				}
				type operator--() {
					if (ptr_->left) {
						stack_.push(ptr_);
						ptr_ = ptr_->left;
						while(ptr_->right) {
							stack_.push(ptr_);
							ptr_ = ptr_->right;
						}
					} else if(stack_.top()->right == ptr_) {
						ptr_ = stack_.top();
						stack_.pop();
					} else {
						while(stack_.top()->left == ptr_) {
							ptr_ = stack_.top();
							stack_.pop();
						}
						ptr_ = stack_.top();
						stack_.pop();
					}

					return *this;
				}
				type operator--(int) {
					pointer ptr = ptr_;
					--*this;
					return ptr;
				}
				K& operator*() { return ptr_->key; }
				V* operator->() { return &ptr_->val; }
				K& key() { return ptr_->key; }
				bool operator==(const type& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const type& rhs) { return ptr_ != rhs.ptr_; }
				bool operator!() { return ptr_ != nullptr; }
		};
		iterator begin() {
			auto it = iterator(root);
			while ((it.ptr_)->left != nullptr) {
				it.stack_.push((it.ptr_));
				it.ptr_ = (it.ptr_)->left;
			}

			return it;
		}
		iterator end() {
			auto it = iterator(root);
			while (it.ptr_ != nullptr) {
				//it.stack_.push((it.ptr_));
				it.ptr_ = (it.ptr_)->right;
			}

			return it;
		}

		AVLTree() : root(nullptr) { }
		AVLTree(const AVLTree& rhs) : AVLTree() {
			root = copy(rhs.root, nullptr);
		}
		AVLTree& operator=(const AVLTree& rhs) {
			if (this != &rhs) {
				clear();
				root = copy(rhs.root, nullptr);
			}
			return *this;
		}
		~AVLTree() { clear(); }

		V& at(const K& key) {
			return search_helper(root, key)->val;
		}
		V& operator[](const K& key) {
			return search_helper(root, key)->val;
		}

		bool empty() {
			return root;
		}
		size_t size() {
			return size_helper(root);
		}

		void clear() {
			clear_helper(root);
		}

		void insert(const K& key, const V& val) {
			if (!root) {
				root = new Node<K, V>(key, val);
				return;
			}
			StackLinkedList<Node<K, V>*> visited;
			Node<K, V>* curr = root;
			while (curr) {
				visited.push(curr);
				if (curr->key > key) {
					if (!curr->left) {
						curr->left = new Node<K, V>(key, val);
						break;
					} else
						curr = curr->left;
				} else if (curr->key < key) {
					if (!curr->right) {
						curr->right = new Node<K, V>(key, val);
						break;
					} else
						curr = curr->right;
				} else if (curr->key == key) {
					curr->val = val;
				}
			}

			// calculate balancing factor
			while (!visited.empty()) {
				bool has_balanced = false;
				Node<K, V>* curr = visited.top();
				Node<K, V>* parent;
				if (balance_factor(curr) == 2) {
					if (balance_factor(curr->left) == 1) {
						parent = left_left(curr);
					} else if (balance_factor(curr->left) == -1) {
						parent = left_right(curr);
					}
					has_balanced = true;
				} else if (balance_factor(curr) == -2) {
					if (balance_factor(curr->right) == -1){
						parent = right_right(curr);
					} else if (balance_factor(curr->right) == 1) {
						parent = right_left(curr);
					}
					has_balanced = true;
				}

				visited.pop();

				// update parent pointer
				if (has_balanced) {
					if (curr == root) {
						root = parent;
					} else {
						if (visited.top()->left == curr) {
							visited.top()->left = parent;
						} else {
							visited.top()->right = parent;
						}
					}
				}
			}
		}

		void print_helper(const string& pre, Node<K, V>* node, bool is_left) {
			if( node != nullptr )
			    {
			        cout << pre;

			        cout << (is_left ? "├──" : "└──" );

			        // print the value of the node
			        cout << node->key << std::endl;

			        // enter the next tree level - left and right branch
			        print_helper( pre + (is_left ? "│   " : "    "), node->left, true);
			        print_helper( pre + (is_left ? "│   " : "    "), node->right, false);
			    }
		}

		void print() {
			print_helper("", root, false);
		}
};