#pragma once

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class Ideal_cache{
public:
    Ideal_cache(int size_cache);

    void data_put(int key, int index);

    int get(int key);

    void put_in_cache(int key, int element);

private:
    int size_cache;
    unordered_map <int, pair<int, list <int>>> data;
    list <int> list_element_cache;
    unordered_map <int, int> cache_element;
};

