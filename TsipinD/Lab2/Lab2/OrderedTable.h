#pragma once

#include <vector>
#include <string>
#include "OpStats.h"

template <typename T>
class OrderedTable {
private:
    std::vector<std::pair<std::string, T>> data;
    OpStats stats;

    int BinarySearch(const std::string& key, bool& found) {
        int left = 0, right = data.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            stats.equals++;
            if (data[mid].first == key) {
                found = true;
                return mid;
            }

            stats.comparisons++;
            if (data[mid].first < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        found = false;
        return left;
    }

public:
    OpStats GetStats() const { return stats; }
    void ResetStats() { stats.Reset(); }

    void Insert(const std::string& key, const T& value) {
        bool found = false;
        int pos = BinarySearch(key, found);

        if (found) {
            stats.assignments++;
            data[pos].second = value;
        }
        else {
            stats.assignments += (data.size() - pos + 1);
            data.insert(data.begin() + pos, { key, value });
        }
    }

    T* Find(const std::string& key) {
        bool found = false;
        int pos = BinarySearch(key, found);
        if (found) return &data[pos].second;
        return nullptr;
    }

    bool Remove(const std::string& key) {
        bool found = false;
        int pos = BinarySearch(key, found);
        if (found) {
            stats.assignments += (data.size() - pos);
            data.erase(data.begin() + pos);
            return true;
        }
        return false;
    }
};