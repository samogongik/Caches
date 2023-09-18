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
    std::list <int> list_element_cache;
};