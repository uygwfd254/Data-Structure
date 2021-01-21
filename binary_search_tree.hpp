//
// simplified bst
//
#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename K, typename V>
class BinarySearchTree {
	private:
		// node class
		template<typename Key, typename Val>
		struct Node {
			Key key;
			Val val;

			Node<Key,Val>* left;
			Node<Key,Val>* right;
			Node<Key,Val>* parent;

			Node() = delete;
			Node(const Key& key, const Val& val, Node<Key,Val>* parent,
				Node<Key,Val>* left = nullptr, Node<Key,Val>* right = nullptr) :
				key(key), val(val), parent(parent), left(left), right(right) { }


			void set(Node<Key,Val>* data) {
				this->key = data->key;
				this->val = data->val;
			}
		};

		Node<K,V>* root;

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
		void insert_helper(Node<K,V>*& curr, Node<K,V>* prev, const K& key, const V& val) {
			if (!curr)
				curr = new Node<K,V>(key, val, prev);
			else if (key == curr->key)
				curr->val = val; // if key exist, update its value
			else if (key < curr->key)
				insert_helper(curr->left, curr, key, val);
			else
				insert_helper(curr->right, curr, key, val);
		}
		void erase_helper(Node<K,V>* curr) {
			if (!curr)
				return;

			// case 1: leaf node
			if (!curr->left && !curr->right) {
				if (curr == root) { // root case
					delete root;
					root = nullptr;
				} else {
					if (curr == curr->parent->left)
						curr->parent->left = nullptr;
					else
						curr->parent->right = nullptr;

					delete curr;
				}
			} else { // at least 1 child
				// internal node w/ 2 child
				if (curr->left && curr->right) {
			 		// method 1: find min in right
					Node<K,V>* temp = curr->right;

					while (temp->left)
						temp = temp->left;

					curr->set(temp);
					erase_helper(temp);

					// method 2 : find max in left
					// Node<K,V>* temp = curr->left;

					// while (temp->right)
					// 	temp = temp->right;

					// curr->set(temp);
					// erase_helper(temp);
				} else { // internal node w/ 1 child
					Node<K,V>* temp;
					if (curr->left)
						temp = curr->left;
					else
						temp = curr->right;

					if (curr == curr->parent->left)
						curr->parent->left = temp;
					else
						curr->parent->right = temp;

					delete curr;
				}
			}
		}
		void inorder_helper(Node<K,V>* curr) {
			if (!curr)
				return;
			inorder_helper(curr->left);
			cout << "(" << curr->key << ", " << curr->val << ")" << endl;
			inorder_helper(curr->right);
		}
		size_t size_helper(Node<K,V>* curr) {
			if (!curr)
				return 0;
			return size_helper(curr->left) + 1 + size_helper(curr->right);
		}
		int height_helper(Node<K,V>* curr) {
			if (!curr)
				return -1;
			return 1 + max(height_helper(curr->left), height_helper(curr->right));
		}

		void clear_helper(Node<K,V>* curr) {
			if (!curr)
				return;
			if (curr->left)
				clear_helper(curr->left);
			if (curr->right)
				clear_helper(curr->right);

			delete curr;
		}
		Node<K,V>* copy(Node<K,V>* curr, Node<K,V>* prev) {
			if (!curr)
				return nullptr;

			Node<K,V>* temp = new Node<K,V>(curr->key, curr->val, prev,
				copy(curr->left, curr), copy(curr->right, curr));

			return temp;
		}

	public:
		BinarySearchTree() : root(nullptr) { }
		BinarySearchTree(const BinarySearchTree& rhs) : BinarySearchTree() {
			root = copy(rhs.root, nullptr);
		}
		BinarySearchTree& operator=(const BinarySearchTree& rhs) {
			if (this != &rhs) {
				clear();
				root = copy(rhs.root, nullptr);
			}
			return *this;
		}
		~BinarySearchTree() { clear(); }

		V& search(const K& key) {
			return search_helper(root, key)->val;

			// iterative implementation
			// Node<K,V>* curr = root;
			// while(curr) {
			// 	if (key == curr->key)
			// 		return curr->val;
			// 	else if (key < curr->key)
			// 		curr = curr->left;
			// 	else
			// 		curr = curr->right;
			// }
			// throw invalid_argument("key not found");
		}

		void insert(const K& key, const V& val) {
			return insert_helper(root, nullptr, key, val);

			// iterative implementation
			// Node<K,V>* curr = root, *prev;
			// while(curr) {
			// 	prev = curr;
			// 	if (!curr)
			// 		curr = new Node<K,V>(key, val, prev);
			// 	else if (key == curr->key)
			// 		curr->val = val;
			// 	else if (key < curr->key)
			// 		curr = curr->left;
			// 	else
			// 		curr = curr->right;
			// }
		}

		void erase(const K& key) {
			Node<K,V>* curr = search_helper(root, key);
			erase_helper(curr);
		}

		void inorder() {
			inorder_helper(root);
		}

		size_t size() {
			return size_helper(root);
		}
		int height() {
			return height_helper(root);
		}
		bool empty() {
			return root;
		}

		void clear() {
			clear_helper(root);
		}
};