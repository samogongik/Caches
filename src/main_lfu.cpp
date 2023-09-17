#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>
#include "lfu_cache.h"
using namespace std;

int main()
{
    int size_cache = 0, quanity_element = 0, kol = 0;

    cin >> size_cache >> quanity_element;
    LFU_cache cache(size_cache);

    for (int i = 0; i < quanity_element; i++){
        int element, key;
        cin >> element;
        key = element;
        kol += cache.get(key);
        cache.put(key, element);
    }

    cout << kol;
}
