#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

#include "ideal_cache.h"

using namespace std;



int main()
{
    int size_cache = 0, quanity_element = 0, kol = 0;
    vector <int> vector_element;
    cin >> size_cache >> quanity_element;
    Ideal_cache<int, int> cache(size_cache);

    if (size_cache == 0){
        cout << "zero cache size" << endl;
        exit(0);
    }

    for (int i = 0; i < quanity_element; i++){
        int element;
        cin >> element;
        int key = element;
        int index = i;

        vector_element.push_back(element);
        cache.data_put(key, index);
    }

    for (int i = 0; i < vector_element.size(); i++){
        int key = vector_element[i];
        kol += cache.lookup_update(key, vector_element[i]);


    }

    cout << kol;

    return 0;
}
