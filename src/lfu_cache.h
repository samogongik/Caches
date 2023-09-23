#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

template <typename KeyType, typename ValueType>
class LFU_cache {
public:
    LFU_cache(int size_cache);

    int lookup_update(const KeyType& key, const ValueType& element);

private:
    int size_cache;
    std::unordered_map<KeyType, std::pair<int, ValueType>> data;
    std::unordered_map<KeyType, std::list<KeyType>> list_key;
    std::unordered_map<KeyType, typename std::list<KeyType>::iterator> data_it;
};



