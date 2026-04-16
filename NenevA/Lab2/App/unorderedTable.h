#pragma once
#include <vector>
#include <string>
#include <iostream>
template <typename ValType>
struct Table_Node {
	std::string Key;
	ValType Value;
	Table_Node(std::string key, ValType val) : Key(key), Value(val) {}
};

template <typename ValType>
class Unordered_Table {
private:
	std::vector<Table_Node<ValType>> Unordered_Table_Data;
	int unorderedCounters;
public:
	Unordered_Table();
	~Unordered_Table() = default;
	Unordered_Table(const Unordered_Table& other);
	Unordered_Table& operator=(const Unordered_Table& other);
	void emplace_back(std::string Key, ValType Value);
	void erase(std::string Key);
	ValType* find(std::string Key);
	void print();
	void print_operations();
	int get_operation_number();
	void reset();
};

template <typename ValType>
Unordered_Table< ValType>::Unordered_Table() : unorderedCounters(0) {}

template <typename ValType>
Unordered_Table< ValType>::Unordered_Table(const Unordered_Table& other) :
	Unordered_Table_Data(other.Unordered_Table_Data),
	unorderedCounters(0) {
}

template <typename ValType>
Unordered_Table<ValType>& Unordered_Table<ValType>::operator=(const Unordered_Table& other) {
	unorderedCounters++;
	if (this != &other) {
		unorderedCounters++;
		Unordered_Table_Data = other.Unordered_Table_Data;
	}
	return *this;
}

template <typename ValType>
void Unordered_Table<ValType>::emplace_back(std::string Key, ValType Value) {
	for (auto& Table_Element : Unordered_Table_Data) {
		unorderedCounters++;
		if (Table_Element.Key == Key) { //replace
			Table_Element.Value = Value;
			unorderedCounters++;
			return;
		}
	}
	Unordered_Table_Data.emplace_back(Key, Value);
	unorderedCounters++;
}

template <typename ValType>
void Unordered_Table<ValType>::erase(std::string Key) {
	int DeletedIndex = -1;
	unorderedCounters++;
	for (std::size_t i = 0; i < Unordered_Table_Data.size(); ++i) {
		unorderedCounters++;
		if (Unordered_Table_Data[i].Key == Key) {
			DeletedIndex = i; unorderedCounters++;
		}
	}
	unorderedCounters++;
	if (DeletedIndex >= 0) {
		unorderedCounters++;
		Unordered_Table_Data.erase(Unordered_Table_Data.begin() + DeletedIndex);
	}
}

template <typename ValType>
ValType* Unordered_Table<ValType>::find(std::string Key) {
	for (auto& Table_Element : Unordered_Table_Data) {
		unorderedCounters++;
		if (Key == Table_Element.Key) return &(Table_Element.Value);
	}
	return nullptr;
}

template <typename ValType>
void Unordered_Table<ValType>::print() {
	for (size_t i = 0; i < Unordered_Table_Data.size(); ++i) {
		unorderedCounters++;
		std::cout << i << " " << Unordered_Table_Data[i].Key << " "
			<< Unordered_Table_Data[i].Value << "\n";
	}
}

template <typename ValType>
void Unordered_Table<ValType>::print_operations() {
	std::cout << "Total number of operations: " << unorderedCounters << std::endl;
}

template <typename ValType>
int Unordered_Table<ValType>::get_operation_number() {
	return unorderedCounters;
}

template <typename ValType>
void Unordered_Table<ValType>::reset() {
	unorderedCounters = 0;
}