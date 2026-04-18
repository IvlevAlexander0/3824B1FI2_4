#pragma once
#include <string>
#include <algorithm>
#include "OpStats.h"

template <typename T>
class AVLTreeTable {

private:
    struct Node {
        std::string key;
        T value;
        int height;
        Node* left;
        Node* right;

        Node(std::string k, T v) : key(std::move(k)), value(std::move(v)), height(1), left(nullptr), right(nullptr) {}
    };
    
    OpStats stats;
    Node* root = nullptr;

    int getHeight(Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    int getBalance(Node* node) {
        return node == nullptr ? 0 : getHeight(node->right) - getHeight(node->left);
    }


    Node* rightRotate(Node* y) {
        stats.assignments += 4;
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

   
    Node* leftRotate(Node* x) {
        stats.assignments += 4;
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);
        return y;
    }


    Node* balance(Node* node) {
        updateHeight(node);
        int bal = getBalance(node);

        // перекос влево
        if (bal == -2) {
            stats.comparisons++;
            if (getBalance(node->left) == 1) {
                node->left = leftRotate(node->left); // левый-правый поворот
            }
            return rightRotate(node);
        }
        // вправо
        else if (bal == 2) {
            stats.comparisons++;
            if (getBalance(node->right) == -1) {
                node->right = rightRotate(node->right); // правый-левый поворот
            }
            return leftRotate(node);
        }
        return node;
    }

    Node* insertImpl(Node* node, const std::string& key, const T& value) {

        if (node == nullptr) {
            stats.assignments++;
            return new Node(key, value);
        }

        stats.equals++;
        if (key == node->key) {
            stats.assignments++;
            node->value = value;
            return node;
        }

        stats.comparisons++;
        if (key < node->key) {
            node->left = insertImpl(node->left, key, value);
        }
        else {
            node->right = insertImpl(node->right, key, value);
        }

        // возвращаем сбалансированный корень
        return balance(node);
    }


    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* removeMin(Node* node) {
        if (node->left == nullptr) return node->right;
        node->left = removeMin(node->left);
        return balance(node);
    }


    Node* removeImpl(Node* node, const std::string& key, bool& removed) {
        if (node == nullptr) return nullptr;

        stats.equals++;
        if (key == node->key) {
            removed = true; // флаг, что узел найден

            // нет одного из детей
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                delete node; 
                stats.assignments++;
                return temp;
            }
            // есть оба ребенка
            else {
                Node* minNode = findMin(node->right);
                node->key = minNode->key;
                node->value = minNode->value;
                stats.assignments += 2;
                node->right = removeMin(node->right);
            }
        }
        else {
            stats.comparisons++;
            if (key < node->key) {
                node->left = removeImpl(node->left, key, removed);
            }
            else {
                node->right = removeImpl(node->right, key, removed);
            }
        }
        return balance(node);
    }

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    std::string GetRootKey() const {
        if (root == nullptr) return "";
        return root->key;
    }

    ~AVLTreeTable() { destroyTree(root); }

    OpStats GetStats() const { return stats; }
    void ResetStats() { stats.Reset(); }

    void Insert(const std::string& key, const T& value) {
        root = insertImpl(root, key, value);
    }

    T* Find(const std::string& key) {
        Node* current = root;
        while (current != nullptr) {
            stats.equals++;
            if (key == current->key) return &current->value;

            stats.comparisons++;
            if (key < current->key) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

    bool Remove(const std::string& key) {
        bool removed = false;
        root = removeImpl(root, key, removed);
        return removed; // true если удалили, false если ключа в дереве не было
    }

    int GetTotalHeight() {
        return getHeight(this->root);
    }
};