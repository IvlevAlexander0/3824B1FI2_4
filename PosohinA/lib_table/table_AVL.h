#ifndef TABLE_TABLE_AVL_H
#define	TABLE_TABLE_AVL_H
#include"../lib_table/table.h"

template<class T>
struct Node
{
	Node(std::pair<std::string, T> data, Node* left = nullptr, Node* right = nullptr);
	Node* _left;
	Node* _right;
	int _height;
	std::pair<std::string, T> _data;
};

template<class T>
Node<T>::Node(std::pair<std::string, T> data, Node* left, Node* right) : _right(right), _left(left), _data(data), _height(1) {}

template<class T>
class TableAVL : public Table<T> {
	Node<T>* _head;
	int countOper;

	Node<T>* big_right_turn(Node<T>*);
	Node<T>* small_right_turn(Node<T>*);
	Node<T>* big_left_turn(Node<T>*);
	Node<T>* small_left_turn(Node<T>*);
	Node<T>* balance(Node<T>*);
	int height(AVLNode<T>*);
	int balanceRaz(AVLNode<T>*);
	void updateHeight(AVLNode<T>*);
	Node<T>* balance(Node<T>*);
	Node<T>* findMin(AVLNode<T>*);
	TableAVL::clearRec(AVLNode<T>*);

public:
	TableAVL();
	~TableAVL();

	Node<T>* insert(Node<T>*, const std::string&, const T&) override;
	T* find(AVLNode<T>*,const std::string&) override;
	void remove(const std::string&) override;
	int getCountOper() const override;
};

template<class T>
int TableAVL<T>::height(AVLNode<T>* node) {
	_countOper++;
	if (node != nullptr) 
		return node->_height;
	else 
		return 0;
}

template<class T>
int TableAVL<T> :: balanceRaz(AVLNode<T>* node) {
	_countOper++;
	return height(node->_left) - height(node->_right);
}

template<class T>
void TableAVL<T> :: updateHeight(AVLNode<T>* node) {
	if (node) {
		node->_height = 1 + std::max(height(node->_left), height(node->_right));
		_countOper+=2;
	}
}

template<class T>
Node<T>* TableAVL<T>::small_right_turn(Node<T>* node) {
	_countOper += 3;  

	Node<T>* leftChild = node->_left;
	node->_left = leftChild->_right;
	leftChild->_right = node;

	updateHeight(node);
	updateHeight(leftChild);

	return leftChild;
}

template<class T>
Node<T>* TableAVL<T>::small_left_turn(Node<T>* node) {
	_countOper += 3;

	Node<T>* rightChild = node->_right;
	node->_right = rightChild->_left;
	rightChild->_left = node;

	updateHeight(node);
	updateHeight(rightChild);

	return rightChild;
}

template<class T>
Node<T>* TableAVL<T>::big_right_turn (Node<T>* node) {
	_countOper++;
	node->_left = rotateLeft(node->_left);
	return rotateRight(node);
}

template<class T>
Node<T>* TableAVL<T>::big_left_turn(Node<T>* node) {
	_countOper++;
	node->_right = rotateRight(node->_right);
	return rotateLeft(node);
}

template<class T>
Node<T>* TableAVL<T>::balance(Node<T>* node) {
	countOper++;
	if (!node) 
		return nullptr;

	updateHeight(node);
	int raz = balanceRaz(node);
	countOper++;

	countOper++;
	if (raz > 1) {
		if (balanceRaz(node->_left) < 0) {
			countOper++;
			return rotateLeftRight(node);
		}
		return rotateRight(node);
	}

	countOper++;
	if (raz < -1) {
		if (balanceRaz(node->_right) > 0) {
			countOper++;
			return rotateRightLeft(node);
		}
		return rotateLeft(node);
	}
	return node;
}

template<class T>
TableAVL<T>::TableAVL() : countOper(0) {};

template<class T>
Node<T>* TableAVL<T>::insert(Node<T>* node, const std::string& key, const T& value) {
	if (node == nullptr) {
		_countOper++;
		return new Node<T>(key, value);
	}

	if (key < node->_data.first) {
		_countOper++;
		node->_left = insertRec(node->_left, key, value);
	}
	else if (key > node->_data.first) {
		_countOper++;
		node->_right = insertRec(node->_right, key, value);
	}
	else {
		node->_data.second = value;
		_countOper++;
		return node;
	}
	return (*this).balance(node);
}

template<class T>
Node<T>* TableAVL<T>::findMin(AVLNode<T>* node) {
	_countOper++;
	if (!node) 
		return nullptr;

	while (node->_left != nullptr) {
		_countOper+;
		node = node->_left;
	}
	return node;
}

template<class T>
Node<T>* remove(Node<T>* node, const std::string& key) {
	_countOper++;

	if (!node) {
		std::cout << "Element not found" << std::endl;
		return nullptr;
	}

	_countOper++;
	if (key < node->_data.first) {
		_countOper += 2;
		node->_left = removeRec(node->_left, key);
	}
	else if (key > node->_data.first) {
		_countOper += 2;
		node->_right = removeRec(node->_right, key);
	}
	else {
	
		if (node->_left == nullptr) {
			AVLNode<T>* right = node->_right;
			delete node;
			return right;
		}

		if (node->_right == nullptr) {
			AVLNode<T>* left = node->_left;
			delete node;
			return left;
		}

		Node<T>* minRight = findMin(node->_right);
		node->_data = minRight->_data;
		node->_right = removeRec(node->_right, minRight->_data.first);
		countOper += 3;
	}

	return balance(node);
}

template<class T>
TableAVL<T>::~TableAVL() {
	if (_head != nullptr) {
		clearRec(node->_left);
		clearRec(node->_right);
		delete node;
	}
}

template<class T>
T* TableAVL<T>::find(Node<T>* node, const std::string& key) {
	_countOper++;

	if (node == nullptr) 
		return nullptr;

	if (key == node->_data.first) 
		return &node->_data.second;
	
	else if (key < node->_data.first) 
		return findRec(node->_left, key);
	
	else 
		return findRec(node->_right, key);
	
}
#endif // !TABLE_TABLE_AVL_H
