#pragma once
#include <iostream>
#include <string>
template <typename ValType>
struct AVL_Node {
	std::string key;
	ValType value;
	int height;
	AVL_Node* left;
	AVL_Node* right;
	AVL_Node(std::string k, ValType val) {
		key = k;
		value = val;
		height = 1;
		left = nullptr;
		right = nullptr;
	}
};

template <typename ValType>
class AVL_Tree {
private:
	int avlCounters;
	AVL_Node<ValType>* root;
	AVL_Node<ValType>* copy_tree(AVL_Node<ValType>* node);//for copy constructor

	//tools for balance
	int get_height(AVL_Node<ValType>* node);
	int height_diff(AVL_Node<ValType>* node);
	void recount_height(AVL_Node<ValType>* node);

	//balance
	AVL_Node<ValType>* right_rotation(AVL_Node<ValType>* parent);
	AVL_Node<ValType>* left_rotation(AVL_Node<ValType>* parent);
	AVL_Node<ValType>* big_left_rotation(AVL_Node<ValType>* parent);
	AVL_Node<ValType>* big_right_rotation(AVL_Node<ValType>* parent);
	AVL_Node<ValType>* balance(AVL_Node<ValType>* parent);

	//removal logics
	AVL_Node<ValType>* find_min(AVL_Node<ValType>* node);
	AVL_Node<ValType>* delete_min(AVL_Node<ValType>* node);
	AVL_Node<ValType>* private_erase(AVL_Node<ValType>* node, std::string str);

	//insertion logics
	AVL_Node<ValType>* private_emplace_back(AVL_Node<ValType>* node, std::string str, ValType val);

	//print logics
	void private_print(AVL_Node<ValType>* node);
	//find logics
	AVL_Node<ValType>* find_node(std::string key, AVL_Node<ValType>* node);

	//for destructor
	void clear(AVL_Node<ValType>* node);
public:
	AVL_Tree();
	AVL_Tree(const AVL_Tree& other);
	AVL_Tree& operator=(const AVL_Tree& other);
	~AVL_Tree();
	ValType* find(std::string key);
	void emplace_back(std::string str, ValType val);
	void erase(std::string str);
	void print();
	void print_operations();
	int get_operation_number();
	void reset();
};

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::copy_tree(AVL_Node<ValType>* node) {
	avlCounters++;
	if (node == nullptr) return nullptr;
	avlCounters += 5;
	AVL_Node<ValType>* new_node = new AVL_Node<ValType>(node->key, node->value);
	new_node->height = node->height;
	new_node->left = copy_tree(node->left);
	new_node->right = copy_tree(node->right);
	return new_node;
}

template <typename ValType>
int AVL_Tree<ValType>::get_height(AVL_Node<ValType>* node) {
	avlCounters++;
	if (node != nullptr) return node->height;
	return 0;
}

template <typename ValType>
int AVL_Tree<ValType>::height_diff(AVL_Node<ValType>* node) {
	avlCounters++;
	return get_height(node->right) - get_height(node->left);
}

template <typename ValType>
void AVL_Tree<ValType>::recount_height(AVL_Node<ValType>* node) {
	avlCounters += 4;
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);
	if (right_height < left_height) node->height = left_height + 1;
	else node->height = right_height + 1;
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::right_rotation(AVL_Node<ValType>* parent) {
	avlCounters += 3;
	AVL_Node<ValType>* child = parent->left;
	parent->left = child->right;
	child->right = parent;
	recount_height(parent);
	recount_height(child);
	return child;
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::left_rotation(AVL_Node<ValType>* parent) {
	avlCounters += 3;
	AVL_Node<ValType>* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	recount_height(parent);
	recount_height(child);
	return child;
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::big_left_rotation(AVL_Node<ValType>* parent) {
	avlCounters++;
	if (height_diff(parent->right) < 0) parent->right = right_rotation(parent->right);
	return left_rotation(parent);
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::big_right_rotation(AVL_Node<ValType>* parent) {
	avlCounters++;
	if (height_diff(parent->left) > 0) parent->left = left_rotation(parent->left);
	return right_rotation(parent);
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::balance(AVL_Node<ValType>* parent) {
	recount_height(parent);
	avlCounters++;
	if (height_diff(parent) == 2) return big_left_rotation(parent);
	avlCounters++;
	if (height_diff(parent) == -2) return big_right_rotation(parent);
	return parent;
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::find_min(AVL_Node<ValType>* node) {
	while (node && node->left != nullptr) {
		avlCounters++;
		node = node->left;
	}
	return node;
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::delete_min(AVL_Node<ValType>* node) {
	avlCounters++;
	if (node->left == nullptr) return node->right;
	avlCounters++;
	node->left = delete_min(node->left);
	return balance(node);
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::private_erase(AVL_Node<ValType>* node, std::string str) {
	avlCounters++;
	if (node == nullptr) return nullptr;
	avlCounters++;
	if (node->key > str) {
		node->left = private_erase(node->left, str);
		avlCounters++;
	}
	else if (node->key < str) {
		node->right = private_erase(node->right, str);
		avlCounters++;
	}
	else {
		avlCounters += 4;
		AVL_Node<ValType>* left_child = node->left;
		AVL_Node<ValType>* right_child = node->right;
		if (!right_child) {
			delete node;
			return left_child;
		}
		AVL_Node<ValType>* min_node = find_min(right_child);
		node->key = min_node->key;
		node->value = min_node->value;
		node->right = delete_min(right_child);
		avlCounters += 3;
		return balance(node);
	}
	return balance(node);
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::private_emplace_back(AVL_Node<ValType>* node, std::string str, ValType val) {
	avlCounters++;
	if (!node) return new AVL_Node<ValType>(str, val);
	avlCounters++;
	if (str < node->key) {
		node->left = private_emplace_back(node->left, str, val);
		avlCounters++;
	}
	else if (str == node->key) {
		node->value = val;
		avlCounters++;
		return balance(node);
	}
	else if (str > node->key) {
		node->right = private_emplace_back(node->right, str, val);
		avlCounters++;
	}
	return balance(node);
}

template <typename ValType>
void AVL_Tree<ValType>::private_print(AVL_Node<ValType>* node) {
	avlCounters++;
	if (node == nullptr) return;
	private_print(node->left);
	avlCounters++;
	std::cout << node->key << " " << node->value << "\n";
	private_print(node->right);
}

template <typename ValType>
AVL_Node<ValType>* AVL_Tree<ValType>::find_node(std::string key, AVL_Node<ValType>* node) {
	avlCounters++;
	if (node == nullptr) return nullptr;
	avlCounters++;
	if (key < node->key) return find_node(key, node->left);
	avlCounters++;
	if (key > node->key) return find_node(key, node->right);
	return node;
}

template <typename ValType>
void AVL_Tree<ValType>::clear(AVL_Node<ValType>* node) {
	avlCounters++;
	if (node == nullptr) return;
	clear(node->left);
	clear(node->right);
	delete node;
}

template <typename ValType>
AVL_Tree<ValType>::AVL_Tree() : avlCounters(0), root(nullptr) {}

template <typename ValType>
AVL_Tree<ValType>::AVL_Tree(const AVL_Tree& other) {
	avlCounters++;
	root = copy_tree(other.root);
}

template <typename ValType>
AVL_Tree<ValType>& AVL_Tree<ValType>::operator=(const AVL_Tree& other) {
	avlCounters++;
	if (this != &other) {
		clear(root);
		root = copy_tree(other.root);
	}
	return *this;
}

template <typename ValType>
AVL_Tree<ValType>::~AVL_Tree() {
	clear(root);
}

template <typename ValType>
ValType* AVL_Tree<ValType>::find(std::string key) {
	avlCounters++;
	AVL_Node<ValType>* node = find_node(key, root);
	avlCounters++;
	if (node == nullptr) return nullptr;
	return &node->value;
}

template <typename ValType>
void AVL_Tree<ValType>::emplace_back(std::string str, ValType val) {
	avlCounters++;
	root = private_emplace_back(root, str, val);
}

template <typename ValType>
void AVL_Tree<ValType>::erase(std::string str) {
	avlCounters++;
	root = private_erase(root, str);
}

template <typename ValType>
void AVL_Tree<ValType>::print() {
	private_print(root);
}

template <typename ValType>
void AVL_Tree<ValType>::print_operations() {
	std::cout << "Total number of operations: " << avlCounters << std::endl;
}

template <typename ValType>
int AVL_Tree<ValType>::get_operation_number() {
	return avlCounters;
}

template <typename ValType>
void AVL_Tree<ValType>::reset() {
	avlCounters = 0;
}