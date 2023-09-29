#include <iostream>
#include <list>
#include <unordered_map>
#include <cassert>

#include "lfu_cache.h"
using namespace std;

int main()
{
    int size_cache = 0, quanity_element = 0, kol = 0;

    cin >> size_cache >> quanity_element;
    assert(std::cin.good());
    LFU_cache<int, int> cache(size_cache);

    if (size_cache == 0){
        cout << "zero cache size" << endl;
        exit(0);
    }

    for (int i = 0; i < quanity_element; i++){
        int element, key;
        cin >> element;
        assert(std::cin.good());
        key = element;
        slow_get_page_int(key);
        kol += cache.lookup_update(key, slow_get_page_int(key));

    }

    cout << kol;
}
