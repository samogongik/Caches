#include "lfu_cache.h"
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;


LFU_cache::LFU_cache(int size_cache) : size_cache(size_cache) {}

int LFU_cache::get(int key){
    if (data.find(key) != data.end()){
        return 1;
    }
    return 0;
}
int LFU_cache::put(int key, int element){

    if (data.find(key) != data.end()) {
        int old_count = data[key].second;
        int new_count = old_count + 1;
        data[key].second = new_count;


        list_key[old_count].remove(key);
        if (list_key[old_count].empty()){
            list_key.erase(old_count);
        }
        list_key[new_count].push_back(key);


        return 0;

    }

    else if (data.size() < size_cache){
        data[key] = {element, 1};
        list_key[1].push_back(key);

        return 0;
    }

    else {
        int min_count = 1;
        while (list_key.find(min_count) == list_key.end()){
            min_count++;
        }


        int key_min_used_element = list_key[min_count].front();
        data.erase(key_min_used_element);
        list_key[min_count].pop_front();

        if (list_key[min_count].empty()){
            list_key.erase(min_count);
        }

        data[key] = { element, 1 };
        list_key[1].push_back(key);

        return 0;
    }
}



