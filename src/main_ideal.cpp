#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <cassert>

#include "ideal_cache.h"

using namespace std;



int main()
{
    int size_cache = 0, quanity_element = 0, kol = 0;
    vector <int> vector_element;
    cin >> size_cache >> quanity_element;
    assert(std::cin.good());
    Ideal_cache<int, int> cache(size_cache);

    if (size_cache == 0){
        cout << "zero cache size" << endl;
        exit(0);
    }

    for (int i = 0; i < quanity_element; i++){
        int element;
        cin >> element;
        assert(std::cin.good());
        int key = element;
        int index = i;

        vector_element.push_back(element);
        cache.data_put(key, index);
    }

    for (int i = 0; i < vector_element.size(); i++){
        int key = vector_element[i];
        slow_get_page_int(key);
        kol += cache.lookup_update(key, slow_get_page_int(key));


    }

    cout << kol;

    return 0;
}
