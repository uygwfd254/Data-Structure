#pragma once

#include <iostream>
#include <iterator>

using namespace std;

template<typename K, typename V>
struct Node {
	K key;
	V val;

	Node<K,V>* left;
	Node<K,V>* right;
	Node<K,V>* parent;

	Node() = delete;
	Node(const K& key, const V& val) : Node(key, val, nullptr, nullptr, nullptr) { }
	Node(const K& key, const V& val, Node<K,V>* left, Node<K,V>* right, Node<K,V>* parent) :
		key(key), val(val), left(left), right(right), parent(parent) { }
};

template<typename K, typename V>
class BinarySearchTree {
	private:
		Node<K,V>* root;

	public:
		BinarySearchTree() : root(nullptr) { }
		
};