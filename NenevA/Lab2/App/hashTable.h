#pragma once
#include <vector>
#include <string>
#include <iostream>
template <typename ValType>
struct Hash_Table_Node {
	std::string Key;
	ValType Value;
	Hash_Table_Node<ValType>* Next; //chain method
	Hash_Table_Node() : Next(nullptr) {}
	Hash_Table_Node(std::string key, ValType Val) :
		Key(key), Value(Val), Next(nullptr) {
	}
};

template <typename ValType>
class Hash_Table {
private:
	std::vector<Hash_Table_Node<ValType>*> Hash_Table_Data;
	size_t Hash_Table_Size;
	int hashCounters;

	int hash(std::string key);
	//for copy constructor
	void copy_chain(Hash_Table_Node<ValType>* source, Hash_Table_Node<ValType>*& dest);
public:
	Hash_Table(std::size_t _size);
	Hash_Table(const Hash_Table& other);
	Hash_Table& operator=(const Hash_Table& other);
	~Hash_Table();
	ValType* find(std::string key);
	void emplace_back(std::string key, ValType Value);
	void erase(std::string key);
	void print();
	void print_operations();
	int get_operation_number();
	void reset();
};

template <typename ValType>
int Hash_Table<ValType>::hash(std::string key) {
	int res = 5381; //just some random numbers
	for (char c : key) { 
		res = res * 33 + c; //used to be ineffective due to many collisions res+=c
		hashCounters += 3;
	}
	return res % Hash_Table_Size;
}

template <typename ValType>
void Hash_Table<ValType>::copy_chain(Hash_Table_Node<ValType>* source, Hash_Table_Node<ValType>*& dest) {
	if (source == nullptr) {
		dest = nullptr;
		return;
	}
	dest = new Hash_Table_Node<ValType>(source->Key, source->Value);
	copy_chain(source->Next, dest->Next);
}

template <typename ValType>
Hash_Table<ValType>::Hash_Table(size_t _size) : hashCounters(0) {
	Hash_Table_Size = _size;
	Hash_Table_Data.resize(_size, nullptr);
	hashCounters += 2;
}

template <typename ValType>
Hash_Table<ValType>::Hash_Table(const Hash_Table& other) :
	Hash_Table_Size(other.Hash_Table_Size), hashCounters(0)
{
	Hash_Table_Data.resize(Hash_Table_Size, nullptr);
	for (size_t i = 0; i < Hash_Table_Size; ++i) {
		hashCounters++;
		copy_chain(other.Hash_Table_Data[i], Hash_Table_Data[i]);
	}

}

template <typename ValType>
Hash_Table<ValType>& Hash_Table<ValType>::operator=(const Hash_Table<ValType>& other) {
	hashCounters++;
	if (this != &other) {
		for (std::size_t i = 0; i < Hash_Table_Data.size(); ++i) {
			hashCounters += 2;
			Hash_Table_Node<ValType>* Node_Current = Hash_Table_Data[i];
			while (Node_Current != nullptr) {
				hashCounters += 3;
				Hash_Table_Node<ValType>* temp = Node_Current;
				Node_Current = Node_Current->Next;
				delete temp;
			}
		}
		hashCounters += 2;
		Hash_Table_Size = other.Hash_Table_Size;
		Hash_Table_Data.resize(Hash_Table_Size, nullptr);
		for (size_t i = 0; i < Hash_Table_Size; ++i) {
			copy_chain(other.Hash_Table_Data[i], Hash_Table_Data[i]);
		}
	}
	return *this;
}

template <typename ValType>
Hash_Table<ValType>::~Hash_Table() {
	for (std::size_t i = 0; i < Hash_Table_Data.size(); ++i) {
		Hash_Table_Node<ValType>* Node_Current = Hash_Table_Data[i];
		hashCounters++;
		while (Node_Current != nullptr) {
			Hash_Table_Node<ValType>* temp = Node_Current;
			Node_Current = Node_Current->Next;
			delete temp;
			hashCounters++;
		}
	}
}

template <typename ValType>
ValType* Hash_Table<ValType>::find(std::string key) {
	int Predicted_Index = hash(key);
	Hash_Table_Node<ValType>* Node_Current = Hash_Table_Data[Predicted_Index];
	while (Node_Current != nullptr) {
		hashCounters++;
		if (key == Node_Current->Key) {
			return &(Node_Current->Value);
		}
		Node_Current = Node_Current->Next;
		hashCounters++;
	}
	return nullptr;
}

template <typename ValType>
void Hash_Table<ValType>::emplace_back(std::string key, ValType Value) {
	int Predicted_Index = hash(key);
	Hash_Table_Node<ValType>* Node_Current = Hash_Table_Data[Predicted_Index];
	while (Node_Current != nullptr) {
		hashCounters++;
		if (key == Node_Current->Key) { // replace
			Node_Current->Value = Value;
			hashCounters++;
			return;
		}
		Node_Current = Node_Current->Next;
		hashCounters++;
	}
	Hash_Table_Node<ValType>* Inserted_Node = new Hash_Table_Node<ValType>(key, Value);
	Inserted_Node->Next = Hash_Table_Data[Predicted_Index];
	Hash_Table_Data[Predicted_Index] = Inserted_Node;
	hashCounters += 3;
}

template <typename ValType>
void Hash_Table<ValType>::erase(std::string key) {
	int Predicted_Index = hash(key);
	Hash_Table_Node<ValType>** Node_Current = &Hash_Table_Data[Predicted_Index];
	hashCounters++;

	while (*Node_Current != nullptr) {
		hashCounters++;
		if ((*Node_Current)->Key == key) {
			Hash_Table_Node<ValType>* temp = *Node_Current;
			*Node_Current = (*Node_Current)->Next;
			delete temp;
			hashCounters += 3;
			return;
		}
		Node_Current = &(*Node_Current)->Next;
		hashCounters++;;
	}
}

template <typename ValType>
void Hash_Table<ValType>::print() {
	for (int i = 0; i < Hash_Table_Size; ++i) {
		hashCounters++;
		Hash_Table_Node<ValType>* Node_Current = Hash_Table_Data[i];
		while (Node_Current != nullptr) {
			std::cout << i << " " << Node_Current->Key
				<< " " << Node_Current->Value << "\n";
			Node_Current = Node_Current->Next;
			hashCounters += 2;
		}
	}
}

template <typename ValType>
void Hash_Table<ValType>::print_operations() {
	std::cout << "Total number of operations: " << hashCounters << std::endl;
}

template <typename ValType>
int Hash_Table<ValType>::get_operation_number() {
	return hashCounters;
}

template <typename ValType>
void Hash_Table<ValType>::reset() {
	hashCounters = 0;
}