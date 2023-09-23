#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

template <typename KeyType, typename ValueType>
class Ideal_cache {
public:
    Ideal_cache(int size_cache);
    void data_put(const KeyType& key, const ValueType& index);
    int lookup_update(const KeyType& key, const ValueType& element);

private:
    int size_cache;
    std::unordered_map<KeyType, std::pair<int, std::list<KeyType>>> data;
    std::list<KeyType> list_element_cache;
    std::unordered_map<KeyType, ValueType> cache_element;
};

