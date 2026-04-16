#include "pch.h"
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
TEST(HashTablePolinomialTest, EmplaceAndFind) {
    Hash_Table<Polinomial> table(10);

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");

    table.emplace_back("key1", p1);
    table.emplace_back("key2", p2);

    Polinomial* result1 = table.find("key1");
    Polinomial* result2 = table.find("key2");
    Polinomial* result3 = table.find("key3"); // non-existing key

    EXPECT_NE(result1, nullptr);
    EXPECT_NE(result2, nullptr);
    EXPECT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(HashTablePolinomialTest, EmplaceReplace) {
    Hash_Table<Polinomial> table(10);

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");

    table.emplace_back("key1", p1);
    table.emplace_back("key1", p2); 

    Polinomial* result = table.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p2); 
}

TEST(HashTablePolinomialTest, Erase) {
    Hash_Table<Polinomial> table(10);

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table.emplace_back("key1", p1);
    EXPECT_NE(table.find("key1"), nullptr);
    table.erase("key1");
    EXPECT_EQ(table.find("key1"), nullptr);
}

TEST(HashTablePolinomialTest, MultipleOperations) {
    Hash_Table<Polinomial> table(10);

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");
    Polinomial p3 = Polinomial("5 0 5 1 5 2");

    table.emplace_back("key1", p1);
    table.emplace_back("key2", p2);
    table.emplace_back("key3", p3);

    EXPECT_EQ(*table.find("key1"), p1);
    EXPECT_EQ(*table.find("key2"), p2);
    EXPECT_EQ(*table.find("key3"), p3);

    table.erase("key2");
    EXPECT_EQ(table.find("key2"), nullptr);

    EXPECT_EQ(*table.find("key1"), p1);
    EXPECT_EQ(*table.find("key3"), p3);
}

TEST(HashTablePolinomialTest, Statistics) {
    Hash_Table<Polinomial> table(10);

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table.emplace_back("key1", p1);
    table.find("key1");
    table.erase("key1");

    int operations = table.get_operation_number();
    EXPECT_NE(operations, 0);

    table.reset();
    EXPECT_EQ(table.get_operation_number(), 0);
}

TEST(UnorderedTablePolinomialTest, EmplaceAndFind) {
    Unordered_Table<Polinomial> table;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");

    table.emplace_back("key1", p1);
    table.emplace_back("key2", p2);

    Polinomial* result1 = table.find("key1");
    Polinomial* result2 = table.find("key2");
    Polinomial* result3 = table.find("key3");

    EXPECT_NE(result1, nullptr);
    EXPECT_NE(result2, nullptr);
    EXPECT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(UnorderedTablePolinomialTest, EmplaceReplace) {
    Unordered_Table<Polinomial> table;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");

    table.emplace_back("key1", p1);
    table.emplace_back("key1", p2); 

    Polinomial* result = table.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p2); 
}

TEST(UnorderedTablePolinomialTest, Erase) {
    Unordered_Table<Polinomial> table;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table.emplace_back("key1", p1);

    EXPECT_NE(table.find("key1"), nullptr);

    table.erase("key1");

    EXPECT_EQ(table.find("key1"), nullptr);
}

TEST(UnorderedTablePolinomialTest, MultipleOperations) {
    Unordered_Table<Polinomial> table;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");
    Polinomial p3 = Polinomial("5 0 5 1 5 2");

    table.emplace_back("key1", p1);
    table.emplace_back("key2", p2);
    table.emplace_back("key3", p3);

    EXPECT_EQ(*table.find("key1"), p1);
    EXPECT_EQ(*table.find("key2"), p2);
    EXPECT_EQ(*table.find("key3"), p3);

    table.erase("key2");
    EXPECT_EQ(table.find("key2"), nullptr);

    EXPECT_EQ(*table.find("key1"), p1);
    EXPECT_EQ(*table.find("key3"), p3);
}

TEST(UnorderedTablePolinomialTest, Statistics) {
    Unordered_Table<Polinomial> table;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table.emplace_back("key1", p1);
    table.find("key1");
    table.erase("key1");

    int operations = table.get_operation_number();
    EXPECT_GT(operations, 0);

    table.reset();
    EXPECT_EQ(table.get_operation_number(), 0);
}

TEST(AVLTreePolinomialTest, EmplaceAndFind) {
    AVL_Tree<Polinomial> tree;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");

    tree.emplace_back("key1", p1);
    tree.emplace_back("key2", p2);

    Polinomial* result1 = tree.find("key1");
    Polinomial* result2 = tree.find("key2");
    Polinomial* result3 = tree.find("key3");

    EXPECT_NE(result1, nullptr);
    EXPECT_NE(result2, nullptr);
    EXPECT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(AVLTreePolinomialTest, EmplaceReplace) {
    AVL_Tree<Polinomial> tree;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");

    tree.emplace_back("key1", p1);
    tree.emplace_back("key1", p2); 

    Polinomial* result = tree.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p2); 
}

TEST(AVLTreePolinomialTest, Erase) {
    AVL_Tree<Polinomial> tree;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    tree.emplace_back("key1", p1);

    EXPECT_NE(tree.find("key1"), nullptr);

    tree.erase("key1");

    EXPECT_EQ(tree.find("key1"), nullptr);
}

TEST(AVLTreePolinomialTest, MultipleOperations) {
    AVL_Tree<Polinomial> tree;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");
    Polinomial p3 = Polinomial("5 0 5 1 5 2");

    tree.emplace_back("key1", p1);
    tree.emplace_back("key2", p2);
    tree.emplace_back("key3", p3);

    EXPECT_EQ(*tree.find("key1"), p1);
    EXPECT_EQ(*tree.find("key2"), p2);
    EXPECT_EQ(*tree.find("key3"), p3);

    tree.erase("key2");
    EXPECT_EQ(tree.find("key2"), nullptr);

    EXPECT_EQ(*tree.find("key1"), p1);
    EXPECT_EQ(*tree.find("key3"), p3);
}

TEST(AVLTreePolinomialTest, Statistics) {
    AVL_Tree<Polinomial> tree;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    tree.emplace_back("key1", p1);
    tree.find("key1");
    tree.erase("key1");

    int operations = tree.get_operation_number();
    EXPECT_NE(operations, 0);

    tree.reset();
    EXPECT_EQ(tree.get_operation_number(), 0);
}

TEST(AVLTreePolinomialTest, BalanceCheck) {
    AVL_Tree<Polinomial> tree;

    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    Polinomial p2 = Polinomial("1 0 2 1 3 2");
    Polinomial p3 = Polinomial("5 0 5 1 5 2");
    tree.emplace_back("key5", p1);
    tree.emplace_back("key3", p2);
    tree.emplace_back("key7", p3);
    tree.emplace_back("key2", p1);
    tree.emplace_back("key4", p2);
    tree.emplace_back("key6", p3);
    tree.emplace_back("key8", p1);

    EXPECT_NE(tree.find("key5"), nullptr);
    EXPECT_NE(tree.find("key3"), nullptr);
    EXPECT_NE(tree.find("key7"), nullptr);
    EXPECT_NE(tree.find("key2"), nullptr);
    EXPECT_NE(tree.find("key4"), nullptr);
    EXPECT_NE(tree.find("key6"), nullptr);
    EXPECT_NE(tree.find("key8"), nullptr);
}

TEST(HashTablePolinomialTest, EmptyTable) {
    Hash_Table<Polinomial> table(10);

    EXPECT_EQ(table.find("any_key"), nullptr);
    EXPECT_NO_THROW(table.erase("any_key"));
}

TEST(UnorderedTablePolinomialTest, EmptyTable) {
    Unordered_Table<Polinomial> table;

    EXPECT_EQ(table.find("any_key"), nullptr);
    EXPECT_NO_THROW(table.erase("any_key"));
}

TEST(AVLTreePolinomialTest, EmptyTree) {
    AVL_Tree<Polinomial> tree;

    EXPECT_EQ(tree.find("any_key"), nullptr);
    EXPECT_NO_THROW(tree.erase("any_key"));
}

TEST(HashTablePolinomialTest, CopyConstructor) {
    Hash_Table<Polinomial> table1(10);
    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table1.emplace_back("key1", p1);

    Hash_Table<Polinomial> table2(table1);

    Polinomial* result = table2.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(UnorderedTablePolinomialTest, CopyConstructor) {
    Unordered_Table<Polinomial> table1;
    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table1.emplace_back("key1", p1);

    Unordered_Table<Polinomial> table2(table1);

    Polinomial* result = table2.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(AVLTreePolinomialTest, CopyConstructor) {
    AVL_Tree<Polinomial> tree1;
    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    tree1.emplace_back("key1", p1);

    AVL_Tree<Polinomial> tree2(tree1);

    Polinomial* result = tree2.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(HashTablePolinomialTest, AssignmentOperator) {
    Hash_Table<Polinomial> table1(10);
    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table1.emplace_back("key1", p1);

    Hash_Table<Polinomial> table2(10);
    table2 = table1;

    Polinomial* result = table2.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(UnorderedTablePolinomialTest, AssignmentOperator) {
    Unordered_Table<Polinomial> table1;
    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    table1.emplace_back("key1", p1);

    Unordered_Table<Polinomial> table2;
    table2 = table1;

    Polinomial* result = table2.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(AVLTreePolinomialTest, AssignmentOperator) {
    AVL_Tree<Polinomial> tree1;
    Polinomial p1 = Polinomial("2 0 3 1 4 2");
    tree1.emplace_back("key1", p1);

    AVL_Tree<Polinomial> tree2;
    tree2 = tree1;

    Polinomial* result = tree2.find("key1");
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}