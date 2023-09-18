#include "lfu_cache.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
using namespace std;


LFU_cache::LFU_cache(int size_cache) : size_cache(size_cache) {}

int LFU_cache::get(int key){
    if (data.find(key) != data.end()){
        return 1;
    }
    return 0;
}
int LFU_cache::put(int key, int element){
    if (size_cache == 0){
        cout << "zero cache size" << endl;
        return -1;
    }
    if (data.find(key) != data.end()) {
        data[key].second++;
        list_element_cache.remove(element);
        list_element_cache.push_back(element);


        return 0;

    }

    else if (data.size() < size_cache){
        data[key] = {element, 1};
        list_element_cache.push_back(element);

        return 0;
    }

    else {
        auto min_it = list_element_cache.begin();

        for (auto elem_it = list_element_cache.begin(); elem_it != list_element_cache.end(); elem_it++){
            if (data[*elem_it].second < data[*min_it].second){
                min_it = elem_it;
            }
        }

        data.erase(*min_it);
        data[key] = { element, 1 };

        list_element_cache.erase(min_it);
        list_element_cache.push_back(element);

        return 0;
    }
}



