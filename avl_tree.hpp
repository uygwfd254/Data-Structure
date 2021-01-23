#pragma once

#include "stack.hpp"
#include "pair.hpp"

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
			Pair<Key, Val> data;
			Node<Key,Val>* left;
			Node<Key,Val>* right;

			Node() = delete;
			Node(Pair<Key, Val> pair,
				Node<Key,Val>* left = nullptr, Node<Key,Val>* right = nullptr) :
				data(pair), left(left), right(right) { }

			void set(Node<Key,Val>* node) {
				this->data->first = node->data->first;
				this->data->second = node->data->second;
			}
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

			Node<K,V>* temp = new Node<K,V>(curr->data,
				copy(curr->left, curr), copy(curr->right, curr));

			return temp;
		}

		Pair<Node<K,V>*, Node<K,V>*> search_helper(Node<K,V>* curr, Node<K,V>* prev, const K& key) {
			if (!curr)
				throw invalid_argument("key not found");

			if (key == curr->data->first)
				return make_Pair(curr, prev);
			else if (key < curr->data->first)
				return search_helper(curr->left, curr, key);
			else
				return search_helper(curr->right, curr, key);
		}
		void erase_helper(Node<K,V>* curr, Node<K,V>* prev) {
			if (!curr)
				return;

			if (!curr->left && !curr->right) {
				if (curr == root) {
					delete root;
					root = nullptr;
				} else {
					if (curr == prev->left)
						prev->left = nullptr;
					else
						prev->right = nullptr;

					delete curr;
				}
			} else {
				if (curr->left && curr->right) {
					Node<K,V>* temp = curr->right;
					Node<K,V>* temp_prev = curr;

					while (temp->left) {
						temp_prev = temp;
						temp = temp->left;
					}

					curr->set(temp);
					erase_helper(temp, temp_prev);
				} else {
					Node<K,V>* temp;
					if (curr->left)
						temp = curr->left;
					else
						temp = curr->right;

					if (curr == prev->left)
						prev->left = temp;
					else
						prev->right = temp;

					delete curr;
				}
			}
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
				Pair<K, V>& operator*() { return ptr_->data; }
				Pair<K, V>& operator->() { return ptr_->data; }
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
			return search_helper(root, key)->first->data->second;
		}
		V& operator[](const K& key) {
			return search_helper(root, key)->first->data->second;
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

		Node<K, V>* balance(Node<K, V>* curr) {
			Node<K, V>* parent = nullptr;
			if (balance_factor(curr) == 2) {
				if (balance_factor(curr->left) == 1) {
					parent = left_left(curr);
				} else if (balance_factor(curr->left) == -1) {
					parent = left_right(curr);
				}
			} else if (balance_factor(curr) == -2) {
				if (balance_factor(curr->right) == -1){
					parent = right_right(curr);
				} else if (balance_factor(curr->right) == 1) {
					parent = right_left(curr);
				}
			}

			return parent;
		}

		void insert(Pair<K, V> pair) {
			if (!root) {
				root = new Node<K, V>(pair);
				return;
			}
			StackLinkedList<Node<K, V>*> visited;
			Node<K, V>* curr = root;
			while (curr) {
				visited.push(curr);
				if (curr->data->first > pair->first) {
					if (!curr->left) {
						curr->left = new Node<K, V>(pair);
						break;
					} else
						curr = curr->left;
				} else if (curr->data->first < pair->first) {
					if (!curr->right) {
						curr->right = new Node<K, V>(pair);
						break;
					} else
						curr = curr->right;
				} else if (curr->data->first == pair->first) {
					curr->data->second = pair->second;
				}
			}

			// calculate balancing factor
			while (!visited.empty()) {
				Node<K, V>* curr = visited.top();
				Node<K, V>* parent = balance(curr);

				visited.pop();
				// update parent pointer
				if (parent) {
					if (curr == root) {
						root = parent;
					} else {
						if (visited.top()->left == curr) {
							visited.top()->left = parent;
						} else {
							visited.top()->right = parent;
						}
					}
					break;
				}
			}
		}

		void erase(const K& key) {
			auto pair = search_helper(root, nullptr, key);
			erase_helper(pair->first, pair->second);

			// rebalancing
			bool has_balanced = false;
			StackLinkedList<Node<K, V>*> visited;

			do {
				visited.push(root);
				has_balanced = false;
				while (!visited.empty()) {
					Node<K, V>* curr = visited.top();
					visited.pop();

					if (curr->left) {
						visited.push(curr->left);
					}
					if (curr->right) {
						visited.push(curr->right);
					}

					Node<K, V>* parent = balance(curr);
					if (parent) {
						has_balanced = true;
						auto pair = search_helper(root, nullptr, curr->data->first);

						if (curr == root) {
							root = parent;
						} else {
							if (pair->second->left == curr) {
								pair->second->left = parent;
							} else {
								pair->second->right = parent;
							}
						}
						break;
					}
				}

				visited = StackLinkedList<Node<K, V>*>();
			} while (has_balanced);
		}

		void print_helper(const string& pre, Node<K, V>* node, bool is_left) {
			if( node != nullptr )
			    {
			        cout << pre;

			        cout << (is_left ? "├──" : "└──" );

			        // print the value of the node
			        cout << node->data->first << std::endl;

			        // enter the next tree level - left and right branch
			        print_helper( pre + (is_left ? "│   " : "    "), node->left, true);
			        print_helper( pre + (is_left ? "│   " : "    "), node->right, false);
			    }
		}

		void print() {
			print_helper("", root, false);
		}
};