#pragma once
#include <iostream>
#include "hashTable.h"
#include "unorderedTable.h"
#include "AVL_tree.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Polinomial.h"
#include <concepts>

template <typename T>
std::string to_string(const T& value) { // to_string for polinomials
    //made as i used int type for cheching the app initially
    if constexpr (std::is_arithmetic_v<T>) { 
        return std::to_string(value);
    }
    else {
        std::ostringstream ss;
        ss << value;
        return ss.str();
    }
}

template <typename ValType>
class TableManager { 
private:
    Hash_Table<ValType> hashTable;
    Unordered_Table<ValType> unorderedTable;
    AVL_Tree<ValType> avlTree;

    std::ofstream logFile;

    // Method statistics
    struct MethodStats {
        int emplace_count = 0;
        int erase_count = 0;
        int find_count = 0;
        int print_count = 0;
    };

    MethodStats hashStats;
    MethodStats unorderedStats;
    MethodStats avlStats;

    // Log with operation counter
    void log(const std::string& message, int operations = -1);

    // Basic operations handlers
    void handle_emplace();
    void handle_erase();
    void handle_find();
    void handle_print();

    // Functions for polinomials 
    void handle_polynomial_operations();
    Polinomial read_polynomial(const std::string& prompt);

    // To choose polinomial from the table if it fails calls read_polinomial()
    Polinomial select_polynomial(const std::string& prompt);

    // Functions for operations
    void show_stats();
    void reset_stats();

    // Show the overall statistics once the programme is finished
    void log_final_stats();

public:
    TableManager();
    ~TableManager();

    //function that runs the app
    void run();
};

template <typename ValType>
void TableManager<ValType>::log(const std::string& message, int operations) {
    if (logFile.is_open()) {
        logFile << message;
        if (operations >= 0) {
            logFile << " [operations: " << operations << "]";
        }
        logFile << std::endl;
    }
}

template <typename ValType>
void TableManager<ValType>::handle_emplace() {
    std::string key;
    ValType value;
    std::cout << "Enter the key and the value(the existing key may be entered as well): ";
    std::cin >> key >> value;

    hashTable.emplace_back(key, value);
    int hashOps = hashTable.get_operation_number();
    log("Hash_Table: emplace(" + key + ", " + to_string(value) + ")", hashOps);
    hashStats.emplace_count++;

    unorderedTable.emplace_back(key, value);
    int unorderedOps = unorderedTable.get_operation_number();
    log("Unordered_Table: emplace(" + key + ", " + to_string(value) + ")", unorderedOps);
    unorderedStats.emplace_count++;

    avlTree.emplace_back(key, value);
    int avlOps = avlTree.get_operation_number();
    log("AVL_Tree: emplace(" + key + ", " + to_string(value) + ")", avlOps);
    avlStats.emplace_count++;
}

template <typename ValType>
void TableManager<ValType>::handle_erase() {
    std::string key;
    std::cout << "Enter the key for removing: ";
    std::cin >> key;

    hashTable.erase(key);
    int hashOps = hashTable.get_operation_number();
    log("Hash_Table: erase(" + key + ")", hashOps);
    hashStats.erase_count++;

    unorderedTable.erase(key);
    int unorderedOps = unorderedTable.get_operation_number();
    log("Unordered_Table: erase(" + key + ")", unorderedOps);
    unorderedStats.erase_count++;

    avlTree.erase(key);
    int avlOps = avlTree.get_operation_number();
    log("AVL_Tree: erase(" + key + ")", avlOps);
    avlStats.erase_count++;
}

template <typename ValType>
void TableManager<ValType>::handle_find() {
    std::string key;
    std::cout << "Enter the key for search: ";
    std::cin >> key;

    ValType* result = hashTable.find(key);
    int hashOps = hashTable.get_operation_number();
    if (result) {
        log("Hash_Table: find(" + key + ") = " + to_string(*result), hashOps);
        std::cout << "Hash table : " << key << " " << *result << "\n";
    }
    else {
        log("Hash_Table: find(" + key + ") = not found", hashOps);
        std::cout << "The record with such a key hasn't been found\n";
    }
    hashStats.find_count++;

    result = unorderedTable.find(key);
    int unorderedOps = unorderedTable.get_operation_number();
    if (result) {
        log("Unordered_Table: find(" + key + ") = " + to_string(*result), unorderedOps);
        std::cout << "Unordered table : " << key << " " << *result << "\n";
    }
    else {
        log("Unordered_Table: find(" + key + ") = not found", unorderedOps);
        std::cout << "The record with such a key hasn't been found\n";
    }
    unorderedStats.find_count++;

    result = avlTree.find(key);
    int avlOps = avlTree.get_operation_number();
    if (result) {
        log("AVL_Tree: find(" + key + ") = " + to_string(*result), avlOps);
        std::cout << "AVL_Tree : " << key << " " << *result << "\n";
    }
    else {
        log("AVL_Tree: find(" + key + ") = not found", avlOps);
        std::cout << "The record with such a key hasn't been found\n";
    }
    avlStats.find_count++;
}

template <typename ValType>
void TableManager<ValType>::handle_print() {
    std::cout << "\n Hash_Table \n";
    hashTable.print();
    int hashOps = hashTable.get_operation_number();
    log("Hash_Table: print()", hashOps);
    hashStats.print_count++;

    std::cout << "\n Unordered_Table \n";
    unorderedTable.print();
    int unorderedOps = unorderedTable.get_operation_number();
    log("Unordered_Table: print()", unorderedOps);
    unorderedStats.print_count++;

    std::cout << "\n AVL_Tree \n";
    avlTree.print();
    int avlOps = avlTree.get_operation_number();
    log("AVL_Tree: print()", avlOps);
    avlStats.print_count++;
}

template <typename ValType>
void TableManager<ValType>::handle_polynomial_operations() {
    std::cout << "\n Polynomial Operations \n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Multiplication\n";
    std::cout << "4. Multiplication by scalar\n";
    std::cout << "5. Back to main menu\n";
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 5) return;

    Polinomial p1, p2, result;
    double scalar;
    std::string resultKey;

    p1 = select_polynomial("Select or enter first polynomial");

    if (choice >= 1 && choice <= 3) {
        p2 = select_polynomial("Select or enter second polynomial");
    }

    switch (choice) {
    case 1: // Addition
        result = p1 + p2;
        std::cout << "Result: " << result << "\n";
        std::cout << "Enter key for storing result(you may also enter the existing key): ";
        std::cin >> resultKey;

        hashTable.emplace_back(resultKey, result);
        log("Hash_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            hashTable.get_operation_number());
        hashStats.emplace_count++;

        unorderedTable.emplace_back(resultKey, result);
        log("Unordered_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            unorderedTable.get_operation_number());
        unorderedStats.emplace_count++;

        avlTree.emplace_back(resultKey, result);
        log("AVL_Tree: emplace(" + resultKey + ", " + to_string(result) + ")",
            avlTree.get_operation_number());
        avlStats.emplace_count++;
        break;

    case 2: // Subtraction
        result = p1 - p2;
        std::cout << "Result: " << result << "\n";
        std::cout << "Enter key for storing result: ";
        std::cin >> resultKey;

        hashTable.emplace_back(resultKey, result);
        log("Hash_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            hashTable.get_operation_number());
        hashStats.emplace_count++;

        unorderedTable.emplace_back(resultKey, result);
        log("Unordered_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            unorderedTable.get_operation_number());
        unorderedStats.emplace_count++;

        avlTree.emplace_back(resultKey, result);
        log("AVL_Tree: emplace(" + resultKey + ", " + to_string(result) + ")",
            avlTree.get_operation_number());
        avlStats.emplace_count++;
        break;

    case 3: // Multiplication
        result = p1 * p2;
        std::cout << "Result: " << result << "\n";
        std::cout << "Enter key for storing result: ";
        std::cin >> resultKey;

        hashTable.emplace_back(resultKey, result);
        log("Hash_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            hashTable.get_operation_number());
        hashStats.emplace_count++;

        unorderedTable.emplace_back(resultKey, result);
        log("Unordered_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            unorderedTable.get_operation_number());
        unorderedStats.emplace_count++;

        avlTree.emplace_back(resultKey, result);
        log("AVL_Tree: emplace(" + resultKey + ", " + to_string(result) + ")",
            avlTree.get_operation_number());
        avlStats.emplace_count++;
        break;

    case 4: // Multiplication by scalar
        std::cout << "Enter scalar: ";
        std::cin >> scalar;
        result = p1 * scalar;
        std::cout << "Result: " << result << "\n";
        std::cout << "Enter key for storing result: ";
        std::cin >> resultKey;

        hashTable.emplace_back(resultKey, result);
        log("Hash_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            hashTable.get_operation_number());
        hashStats.emplace_count++;

        unorderedTable.emplace_back(resultKey, result);
        log("Unordered_Table: emplace(" + resultKey + ", " + to_string(result) + ")",
            unorderedTable.get_operation_number());
        unorderedStats.emplace_count++;

        avlTree.emplace_back(resultKey, result);
        log("AVL_Tree: emplace(" + resultKey + ", " + to_string(result) + ")",
            avlTree.get_operation_number());
        avlStats.emplace_count++;
        break;
    }
}

template <typename ValType>
Polinomial TableManager<ValType>::read_polynomial(const std::string& prompt) {
    std::cout << prompt << " (format: coeff degree, coeff degree...): ";
    std::string input;
    std::cin.ignore(); 
    std::getline(std::cin, input);
    return Polinomial(input);
}

template <typename ValType>
Polinomial TableManager<ValType>::select_polynomial(const std::string& prompt) {
    std::cout << "\n" << prompt << ":\n";
    std::cout << "1. Enter new polynomial from console\n";
    std::cout << "2. Select from table by key\n";
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        return read_polynomial("Enter polynomial");
    }
    else if (choice == 2) {
        std::string key;
        std::cout << "Enter key: ";
        std::cin >> key;

        Polinomial* result_h = hashTable.find(key);
        Polinomial* result_un = unorderedTable.find(key);
        Polinomial* result_avl = avlTree.find(key);
        if (result_h && result_un && result_avl) {
            std::cout << "Found: " << *result_h << "\n";
            return *result_h;
        }

        std::cout << "Key isn't located in all the tables. Try to enter polynomial from console instead.\n";
        return read_polynomial("Enter polynomial");
    }
    else {
        std::cout << "Invalid choice. Entering from console.\n";
        return read_polynomial("Enter polynomial");
    }
}

template <typename ValType>
void TableManager<ValType>::show_stats() {
    std::cout << "\n Operation statistics \n";
    std::cout << "Hash_Table: ";
    hashTable.print_operations();
    std::cout << "Unordered_Table: ";
    unorderedTable.print_operations();
    std::cout << "AVL_Tree: ";
    avlTree.print_operations();

    log(" Statistics ");
    log("Hash_Table: total=" + std::to_string(hashTable.get_operation_number()));
    log("Unordered_Table: total=" + std::to_string(unorderedTable.get_operation_number()));
    log("AVL_Tree: total=" + std::to_string(avlTree.get_operation_number()));
}

template <typename ValType>
void TableManager<ValType>::reset_stats() {
    hashTable.reset();
    unorderedTable.reset();
    avlTree.reset();
    hashStats = MethodStats();
    unorderedStats = MethodStats();
    avlStats = MethodStats();
    log("Statistics reseted");
}

template <typename ValType>
void TableManager<ValType>::log_final_stats() {
    log(" Final Statistics ");

    // Hash_Table
    log("Hash_Table:");
    log("  emplace: " + std::to_string(hashStats.emplace_count) + " times");
    log("  erase: " + std::to_string(hashStats.erase_count) + " times");
    log("  find: " + std::to_string(hashStats.find_count) + " times");
    log("  print: " + std::to_string(hashStats.print_count) + " times");
    log("  Total operations: " + std::to_string(hashTable.get_operation_number()));

    // Unordered_Table
    log("Unordered_Table:");
    log("  emplace: " + std::to_string(unorderedStats.emplace_count) + " times");
    log("  erase: " + std::to_string(unorderedStats.erase_count) + " times");
    log("  find: " + std::to_string(unorderedStats.find_count) + " times");
    log("  print: " + std::to_string(unorderedStats.print_count) + " times");
    log("  Total operations: " + std::to_string(unorderedTable.get_operation_number()));

    // AVL_Tree
    log("AVL_Tree:");
    log("  emplace: " + std::to_string(avlStats.emplace_count) + " times");
    log("  erase: " + std::to_string(avlStats.erase_count) + " times");
    log("  find: " + std::to_string(avlStats.find_count) + " times");
    log("  print: " + std::to_string(avlStats.print_count) + " times");
    log("  Total operations: " + std::to_string(avlTree.get_operation_number()));
}

template <typename ValType>
TableManager<ValType>::TableManager() : hashTable(10), logFile("log.txt", std::ios::app) {
    if (!logFile.is_open()) {
        std::cerr << "Failed to open the file log.txt" << std::endl;
    }
    else {
        log(" Session started ");
    }
}

template <typename ValType>
TableManager<ValType>::~TableManager() {
    log_final_stats();
    log(" Session ended ");
    if (logFile.is_open()) {
        logFile.close();
    }
}

template <typename ValType>
void TableManager<ValType>::run() {
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Insertion\n";
        std::cout << "2. Deletion\n";
        std::cout << "3. Search\n";
        std::cout << "4. Print\n";
        std::cout << "5. Polynomial operations\n";
        std::cout << "6. Operation statistics\n";
        std::cout << "7. Statistics reset\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter the command: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            handle_emplace();
            break;
        case 2:
            handle_erase();
            break;
        case 3:
            handle_find();
            break;
        case 4:
            handle_print();
            break;
        case 5:
            handle_polynomial_operations();
            break;
        case 6:
            show_stats();
            break;
        case 7:
            reset_stats();
            break;
        case 8:
            return;
        default:
            std::cout << "Incorrect choice, try again\n";
        }
    }
}