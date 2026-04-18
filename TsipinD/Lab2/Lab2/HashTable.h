
#pragma once
#include <vector>
#include <list>
#include <string>
#include "OpStats.h"

template <typename T>
class HashTable {
	std::vector<std::list<std::pair<std::string, T>>> buckets;
	size_t bucketCount;
	OpStats stats;

	size_t getHash(const std::string & key) const {
		size_t hash = 5381;
		for (char c : key) {
			hash = ((hash << 5) + hash) + static_cast<size_t>(c);
		}
		return hash % bucketCount;
	}
public:
	OpStats GetStats() const { return stats; }
	void ResetStats() { stats.Reset(); }

	HashTable(size_t size = 101) : bucketCount(size) {
		buckets.resize(bucketCount);
	}

	void Insert(const std::string& key, const T& value) {
		size_t index = getHash(key);

		for (auto& pair : buckets[index]) {
			stats.equals++;
			if (pair.first == key) {
				pair.second = value;
				return;
			}
		}
		stats.assignments++;
		buckets[index].push_back({ key, value });
	}

	T* Find(const std::string& key) {
		size_t index = getHash(key);

		for (auto& pair : buckets[index]) {
			stats.equals++;
			if (pair.first == key) {
				return &pair.second;
			}
		}
		return nullptr;
	}

	bool Remove(const std::string& key) {
		size_t index = getHash(key);
		auto& node = buckets[index];

		for (auto it = node.begin(); it != node.end(); ++it) {
			stats.equals++;
			if (it->first == key) {
				node.erase(it);
				return true;
			}
		}
		return false;
	}
};