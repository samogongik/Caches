#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

typedef int (*FunctionPointer)(int);

int slow_get_page_int(int element) {
    return element;
}

template <typename KeyType, typename ValueType>
class Ideal_cache {
public:
    Ideal_cache(int size_cache);
    void data_put(const KeyType& key, const ValueType& index);
    bool lookup_update(const KeyType& key, const FunctionPointer slow_get_page);
    void cache_erase(const KeyType& key, const ValueType& element);
    void alternative_erase(const KeyType& key, const ValueType& element);

private:
    int size_cache;
    std::unordered_map<KeyType, std::pair<int, std::list<KeyType>>> data;
    std::list<KeyType> list_element_cache;
    std::unordered_map<KeyType, ValueType> cache_element;
};

template <typename KeyType, typename ValueType>
Ideal_cache<KeyType, ValueType>::Ideal_cache(int size_cache) : size_cache(size_cache) {}

template <typename KeyType, typename ValueType>
void Ideal_cache<KeyType, ValueType>::data_put(const KeyType& key, const ValueType& index) {

    if (data.find(key) == data.end()) {
        data[key].first = 1;
        data[key].second.push_back(index);
    }
    else {
        data[key].first += 1;
        data[key].second.push_back(index);
    }
}
template <typename KeyType, typename ValueType>
void Ideal_cache<KeyType, ValueType>::alternative_erase(const KeyType &key, const ValueType &element){

    int key_last = 0;
    auto old_elem_it = list_element_cache.begin();
    for (auto elem_it = list_element_cache.begin(); elem_it != list_element_cache.end(); elem_it++) {
        if (key_last < (data[*elem_it].second.front())) {
            key_last = (data[*elem_it].second.front());
            old_elem_it = elem_it;
        }
    }

    data[key].first--;
    data[key].second.pop_front();

    cache_element.erase(*old_elem_it);
    cache_element[key] = element;

    list_element_cache.erase(old_elem_it);
    list_element_cache.push_back(element);
}

template <typename KeyType, typename ValueType>
void Ideal_cache<KeyType, ValueType>::cache_erase(const KeyType &key, const ValueType &element){
    if (data[key].first == 1) {
        data.erase(key);
        return;
    }

    int key_last = 0;
    auto old_elem_it = list_element_cache.begin();
    bool flag = 0;

    for (auto elem_it = list_element_cache.begin(); elem_it != list_element_cache.end(); elem_it++) {
        if ((data[*elem_it].second.empty())) {
            old_elem_it = elem_it;
            flag = 1;
        }
    }

    if (flag == 1) {
        data.erase(*old_elem_it);

        data[key].first--;
        data[key].second.pop_front();

        cache_element.erase(*old_elem_it);
        cache_element[key] = element;

        list_element_cache.erase(old_elem_it);
        list_element_cache.push_back(element);

        return;
    }
    alternative_erase(key, element);
}

template <typename KeyType, typename ValueType>
bool Ideal_cache<KeyType, ValueType>::lookup_update(const KeyType& key, const FunctionPointer slow_get_page) {
    if (cache_element.find(key) != cache_element.end()) {
        data[key].first--;
        data[key].second.pop_front();

        if (data[key].second.empty()) {
            data.erase(key);
        }
        return true;
    }
    else if (cache_element.size() < size_cache) {

        if (data[key].first == 1) {
            data.erase(key);
            return false;
        }
        ValueType val = slow_get_page(key);
        cache_element[key] = val;
        data[key].first--;
        data[key].second.pop_front();

        list_element_cache.push_back(val);
        if (data[key].second.empty()) {
            data.erase(key);
        }

        return false;
    }
    else {
        cache_erase(key, slow_get_page(key));
        return false;
    }



}


