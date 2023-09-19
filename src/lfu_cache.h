#pragma once

#include "lfu_cache.h"
#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>


class LFU_cache{
public:
    LFU_cache(int size_cache);
    int get(int key);
    int put(int key, int element);

private:
    int size_cache;
    std::unordered_map<int, std::pair <int,int>> data;
    std::unordered_map <int, std::list<int>> list_key;
    std:: unordered_map<int, std::list<int>::iterator> data_it;
};