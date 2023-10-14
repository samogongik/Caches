#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

typedef int (*FunctionPointer)(int);
int slow_get_page_int(int element) {
    return element;
}

template <typename KeyType, typename ValueType>
class LFU_cache {
public:
    LFU_cache(int size_cache);

    bool lookup_update(const KeyType& key,  const FunctionPointer slow_get_page);
    void cache_erase(const KeyType& key, const ValueType& element);

private:
    int size_cache;
    std::unordered_map<KeyType, std::pair<int, ValueType>> data;
    std::unordered_map<KeyType, std::list<KeyType>> list_key;
    std::unordered_map<KeyType, typename std::list<KeyType>::iterator> data_it;
};

template <typename KeyType, typename ValueType>
LFU_cache<KeyType, ValueType>::LFU_cache(int size_cache) : size_cache(size_cache) {}

template <typename KeyType, typename ValueType>
void LFU_cache<KeyType, ValueType>::cache_erase(const KeyType &key, const ValueType &element) {
    int min_count = 1;
    while (list_key.find(min_count) == list_key.end()){
        min_count++;
    }

    int key_min_used_element = list_key[min_count].front();
    data.erase(key_min_used_element);
    data_it.erase(key_min_used_element);
    list_key[min_count].pop_front();

    if (list_key[min_count].empty()){
        list_key.erase(min_count);
    }

    data[key] = { element, 1 };
    list_key[1].push_back(key);
    data_it[key] = prev(list_key[1].end());



}

template <typename KeyType, typename ValueType>
bool LFU_cache<KeyType, ValueType>::lookup_update(const KeyType& key,  const FunctionPointer slow_get_page) {

    if (data.find(key) != data.end()) {
        int old_count = data[key].second;
        int new_count = old_count + 1;
        data[key].second = new_count;

        list_key[old_count].erase(data_it[key]);
        data_it.erase(key);

        if (list_key[old_count].empty()){
            list_key.erase(old_count);
        }

        list_key[new_count].push_back(key);
        data_it[key] = prev(list_key[new_count].end());

        return true;

    }

    else if (data.size() < size_cache){
        data[key] = {slow_get_page(key), 1};
        list_key[1].push_back(key);
        data_it[key] = prev(list_key[1].end());

        return false;
    }

    else {
        cache_erase(key, slow_get_page(key));

        return false;
    }
}

