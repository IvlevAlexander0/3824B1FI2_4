#pragma once

#include <vector>
#include <string>
#include "OpStats.h"

template <typename T>
class UnorderedTable {
private:
    std::vector<std::pair<std::string, T>> data;
    OpStats stats;

public:
    OpStats GetStats() const { return stats; }
    void ResetStats() { stats.Reset(); }

    void Insert(const std::string& key, const T& value) {
        for (auto& pair : data) {
            stats.equals++;
            if (pair.first == key) {
                stats.assignments++;
                pair.second = value; // обновл€ем значение, если ключ уже есть
                return;
            }
        }
        stats.assignments++;
        data.push_back({ key, value });
    }

    T* Find(const std::string& key) {
        for (auto& pair : data) {
            stats.equals++;
            if (pair.first == key) {
                return &pair.second;
            }
        }
        return nullptr;
    }

    bool Remove(const std::string& key) {
        for (size_t i = 0; i < data.size(); ++i) {
            stats.equals++;
            if (data[i].first == key) {
                stats.assignments += 2; // перемещение последнего элемента на место удал€емого
                data[i] = data.back();
                data.pop_back();
                return true;
            }
        }
        return false;
    }
};