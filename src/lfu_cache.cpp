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
    if (data.find(key) != data.end()){

        data[key].first = element;
        int old_count = data[key].second;
        auto old_count_it = std::find(arr_count.begin(), arr_count.end(), old_count);

        arr_count.erase(old_count_it);
        int new_count = old_count + 1;
        data[key].second = new_count;
        arr_count.push_back(new_count);

        list_key[old_count].remove(key);
        if (list_key[old_count].empty()){
            list_key.erase(old_count);
        }
        list_key[new_count].push_back(key);

    }

    else if (data.size() < size_cache){
        data[key] = {element, 1};
        list_key[1].push_back(key);
        arr_count.push_back(1);
    }

    else {
        auto min_it = arr_count.begin();

        for (auto elem_it = arr_count.begin(); elem_it != arr_count.end(); elem_it++){
            if (*elem_it < *min_it){
                min_it = elem_it;
            }
        }

        int min_count = *min_it;
        arr_count.erase(min_it);
        int key_min_used_element = list_key[min_count].front();

        data.erase(key_min_used_element);
        list_key[min_count].pop_front();
        if (list_key[min_count].empty()){
            list_key.erase(min_count);
        }
        data[key] = { element, 1 };
        arr_count.push_back(1);
        list_key[1].push_back(key);
    }
    return 0;
}



