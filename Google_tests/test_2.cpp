#include "gtest/gtest.h"
#include "../src/lfu_cache.h"
#include <vector>

TEST(e2e, first_test){
    int size_cache = 3,  kol_expected = 2, kol_result = 0;
    std::vector <int> vector_element = { 1, 6, 9, 1, 6, 2, 5, 2};

    LFU_cache cache(size_cache);

    for (int i = 0; i < vector_element.size(); i++){
        int element, key;

        key = vector_element[i];
        kol_result += cache.get(key);
        cache.put(key, vector_element[i]);
    }
    ASSERT_EQ(kol_result, kol_expected) << "Test failed";
}

TEST(e2e, second_test){
    int size_cache = 4,  kol_expected = 6, kol_result = 0;
    std::vector <int> vector_element = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};

    LFU_cache cache(size_cache);

    for (int i = 0; i < vector_element.size(); i++){
        int element, key;

        key = vector_element[i];
        kol_result += cache.get(key);
        cache.put(key, vector_element[i]);
    }
    ASSERT_EQ(kol_result, kol_expected) << "Test failed";
}

TEST(e2e, third_test){
    int size_cache = 3,  kol_expected = 6, kol_result = 0;
    std::vector <int> vector_element = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};

    LFU_cache cache(size_cache);

    for (int i = 0; i < vector_element.size(); i++){
        int element, key;

        key = vector_element[i];
        kol_result += cache.get(key);
        cache.put(key, vector_element[i]);
    }
    ASSERT_EQ(kol_result, kol_expected) << "Test failed";
}