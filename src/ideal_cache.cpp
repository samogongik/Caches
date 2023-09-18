

#include "ideal_cache.h"

Ideal_cache::Ideal_cache(int size_cache) : size_cache(size_cache){}

void Ideal_cache::data_put(int key, int index){

    if (data.find(key) == data.end()){
        data[key].first = 1;
        data[key].second.push_back(index);
    }

    else{
        data[key].first += 1;
        data[key].second.push_back(index);
    }
}

int Ideal_cache::get(int key){
    if (cache_element.find(key) != cache_element.end()){
        return 1;
    }
    return 0;
}

void Ideal_cache::put_in_cache(int key, int element) {

    if (cache_element.find(key) != cache_element.end()) {
        data[key].first--;
        data[key].second.pop_front();

        if (data[key].second.empty()) {
            data.erase(key);
        }
    } else if (cache_element.size() < size_cache) {

        if (data[key].first == 1) {
            data.erase(key);
            return;
        }

        cache_element[key] = element;
        data[key].first--;
        data[key].second.pop_front();

        list_element_cache.push_back(element);
        if (data[key].second.empty()) {
            data.erase(key);
        }
    } else {
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

        if (flag == 1){
            data.erase(*old_elem_it);

            data[key].first--;
            data[key].second.pop_front();

            cache_element.erase(*old_elem_it);
            cache_element[key] = element;

            list_element_cache.erase(old_elem_it);
            list_element_cache.push_back(element);

            return;
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
    }
}