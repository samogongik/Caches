#include "ideal_cache.h"

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
int Ideal_cache<KeyType, ValueType>::lookup_update(const KeyType& key, const ValueType& element) {

    if (cache_element.find(key) != cache_element.end()) {
        data[key].first--;
        data[key].second.pop_front();

        if (data[key].second.empty()) {
            data.erase(key);
        }
        return 1;
    }
    else if (cache_element.size() < size_cache) {

        if (data[key].first == 1) {
            data.erase(key);
            return 0;
        }

        cache_element[key] = element;
        data[key].first--;
        data[key].second.pop_front();

        list_element_cache.push_back(element);
        if (data[key].second.empty()) {
            data.erase(key);
        }

        return 0;
    }
    else {
        if (data[key].first == 1) {
            data.erase(key);
            return 0;
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

            return 0;
        }

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

        return 0;
    }
}

// Эксплицитная инстанциация шаблона для конкретных типов int, чтобы компилятор создал код для них.
template class Ideal_cache<int, int>;
