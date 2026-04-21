#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "polinomial.h"
#include "hash_table.h"
#include "unordered_table.h"
#include "avl_tree.h"

// Polinomial craetion
Polinomial CreatePolynomial1() {
    return Polinomial("2 0 3 1 4 2"); 
}

Polinomial CreatePolynomial2() {
    return Polinomial("1 0 2 1 3 2");
}

Polinomial CreatePolynomial3() {
    return Polinomial("5 0 5 1 5 2");
}

// HashTable<Polinomial>
TEST(HashTablePolinomialTest, EmplaceAndFind) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);

    Polinomial* result1 = table.Find("key1");
    Polinomial* result2 = table.Find("key2");
    Polinomial* result3 = table.Find("key3");  // non-existing key

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(HashTablePolinomialTest, EmplaceReplace) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key1", p2);

    Polinomial* result = table.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p2);
}

TEST(HashTablePolinomialTest, Erase) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);

    ASSERT_NE(table.Find("key1"), nullptr);

    table.Erase("key1");

    EXPECT_EQ(table.Find("key1"), nullptr);
}

TEST(HashTablePolinomialTest, MultipleOperations) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);
    table.EmplaceBack("key3", p3);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key2"), p2);
    EXPECT_EQ(*table.Find("key3"), p3);

    table.Erase("key2");
    EXPECT_EQ(table.Find("key2"), nullptr);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key3"), p3);
}

TEST(HashTablePolinomialTest, Statistics) {
    HashTable<Polinomial> table(10);

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);
    table.Find("key1");
    table.Erase("key1");

    int operations = table.GetOperationNumber();
    EXPECT_GT(operations, 0);

    table.Reset();
    EXPECT_EQ(table.GetOperationNumber(), 0);
}

// UnorderedTable<Polinomial>
TEST(UnorderedTablePolinomialTest, EmplaceAndFind) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);

    Polinomial* result1 = table.Find("key1");
    Polinomial* result2 = table.Find("key2");
    Polinomial* result3 = table.Find("key3");

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(UnorderedTablePolinomialTest, EmplaceReplace) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key1", p2);

    Polinomial* result = table.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p2);
}

TEST(UnorderedTablePolinomialTest, Erase) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);

    ASSERT_NE(table.Find("key1"), nullptr);

    table.Erase("key1");

    EXPECT_EQ(table.Find("key1"), nullptr);
}

TEST(UnorderedTablePolinomialTest, MultipleOperations) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    table.EmplaceBack("key1", p1);
    table.EmplaceBack("key2", p2);
    table.EmplaceBack("key3", p3);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key2"), p2);
    EXPECT_EQ(*table.Find("key3"), p3);

    table.Erase("key2");
    EXPECT_EQ(table.Find("key2"), nullptr);

    EXPECT_EQ(*table.Find("key1"), p1);
    EXPECT_EQ(*table.Find("key3"), p3);
}

TEST(UnorderedTablePolinomialTest, Statistics) {
    UnorderedTable<Polinomial> table;

    Polinomial p1 = CreatePolynomial1();
    table.EmplaceBack("key1", p1);
    table.Find("key1");
    table.Erase("key1");

    int operations = table.GetOperationNumber();
    EXPECT_GT(operations, 0);

    table.Reset();
    EXPECT_EQ(table.GetOperationNumber(), 0);
}

// AvlTree<Polinomial>
TEST(AvlTreePolinomialTest, EmplaceAndFind) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    tree.EmplaceBack("key1", p1);
    tree.EmplaceBack("key2", p2);

    Polinomial* result1 = tree.Find("key1");
    Polinomial* result2 = tree.Find("key2");
    Polinomial* result3 = tree.Find("key3");

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result3, nullptr);

    EXPECT_EQ(*result1, p1);
    EXPECT_EQ(*result2, p2);
}

TEST(AvlTreePolinomialTest, EmplaceReplace) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();

    tree.EmplaceBack("key1", p1);
    tree.EmplaceBack("key1", p2);

    Polinomial* result = tree.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p2);
}

TEST(AvlTreePolinomialTest, Erase) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    tree.EmplaceBack("key1", p1);

    ASSERT_NE(tree.Find("key1"), nullptr);

    tree.Erase("key1");

    EXPECT_EQ(tree.Find("key1"), nullptr);
}

TEST(AvlTreePolinomialTest, MultipleOperations) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    tree.EmplaceBack("key1", p1);
    tree.EmplaceBack("key2", p2);
    tree.EmplaceBack("key3", p3);

    EXPECT_EQ(*tree.Find("key1"), p1);
    EXPECT_EQ(*tree.Find("key2"), p2);
    EXPECT_EQ(*tree.Find("key3"), p3);

    tree.Erase("key2");
    EXPECT_EQ(tree.Find("key2"), nullptr);

    EXPECT_EQ(*tree.Find("key1"), p1);
    EXPECT_EQ(*tree.Find("key3"), p3);
}

TEST(AvlTreePolinomialTest, Statistics) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    tree.EmplaceBack("key1", p1);
    tree.Find("key1");
    tree.Erase("key1");

    int operations = tree.GetOperationNumber();
    EXPECT_GT(operations, 0);

    tree.Reset();
    EXPECT_EQ(tree.GetOperationNumber(), 0);
}

TEST(AvlTreePolinomialTest, BalanceCheck) {
    AvlTree<Polinomial> tree;

    Polinomial p1 = CreatePolynomial1();
    Polinomial p2 = CreatePolynomial2();
    Polinomial p3 = CreatePolynomial3();

    tree.EmplaceBack("key5", p1);
    tree.EmplaceBack("key3", p2);
    tree.EmplaceBack("key7", p3);
    tree.EmplaceBack("key2", p1);
    tree.EmplaceBack("key4", p2);
    tree.EmplaceBack("key6", p3);
    tree.EmplaceBack("key8", p1);

    EXPECT_NE(tree.Find("key5"), nullptr);
    EXPECT_NE(tree.Find("key3"), nullptr);
    EXPECT_NE(tree.Find("key7"), nullptr);
    EXPECT_NE(tree.Find("key2"), nullptr);
    EXPECT_NE(tree.Find("key4"), nullptr);
    EXPECT_NE(tree.Find("key6"), nullptr);
    EXPECT_NE(tree.Find("key8"), nullptr);
}

// Specific tests
TEST(HashTablePolinomialTest, EmptyTable) {
    HashTable<Polinomial> table(10);

    EXPECT_EQ(table.Find("any_key"), nullptr);
    EXPECT_NO_THROW(table.Erase("any_key"));
}

TEST(UnorderedTablePolinomialTest, EmptyTable) {
    UnorderedTable<Polinomial> table;

    EXPECT_EQ(table.Find("any_key"), nullptr);
    EXPECT_NO_THROW(table.Erase("any_key"));
}

TEST(AvlTreePolinomialTest, EmptyTree) {
    AvlTree<Polinomial> tree;

    EXPECT_EQ(tree.Find("any_key"), nullptr);
    EXPECT_NO_THROW(tree.Erase("any_key"));
}

TEST(HashTablePolinomialTest, CopyConstructor) {
    HashTable<Polinomial> table1(10);
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    HashTable<Polinomial> table2(table1);

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(UnorderedTablePolinomialTest, CopyConstructor) {
    UnorderedTable<Polinomial> table1;
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    UnorderedTable<Polinomial> table2(table1);

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(AvlTreePolinomialTest, CopyConstructor) {
    AvlTree<Polinomial> tree1;
    Polinomial p1 = CreatePolynomial1();
    tree1.EmplaceBack("key1", p1);

    AvlTree<Polinomial> tree2(tree1);

    Polinomial* result = tree2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(HashTablePolinomialTest, AssignmentOperator) {
    HashTable<Polinomial> table1(10);
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    HashTable<Polinomial> table2(10);
    table2 = table1;

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(UnorderedTablePolinomialTest, AssignmentOperator) {
    UnorderedTable<Polinomial> table1;
    Polinomial p1 = CreatePolynomial1();
    table1.EmplaceBack("key1", p1);

    UnorderedTable<Polinomial> table2;
    table2 = table1;

    Polinomial* result = table2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}

TEST(AvlTreePolinomialTest, AssignmentOperator) {
    AvlTree<Polinomial> tree1;
    Polinomial p1 = CreatePolynomial1();
    tree1.EmplaceBack("key1", p1);

    AvlTree<Polinomial> tree2;
    tree2 = tree1;

    Polinomial* result = tree2.Find("key1");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, p1);
}