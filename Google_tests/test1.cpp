#include "gtest/gtest.h"
#include "../src/ideal_cache.h"
#include <vector>

TEST(e2e_test, first_test) {
    int size_cache = 3, kol_expected = 3, kol_result = 0;
    std::vector <int> vector_element = { 1, 6, 9, 1, 6, 2, 5, 2};
    Ideal_cache<int, int> cache(size_cache);;
    int index = 0;
    for (auto elem: vector_element) cache.data_put(elem, index++);

    for (int i = 0; i < vector_element.size(); i++){
        int key = vector_element[i];
        kol_result += cache.lookup_update(key, slow_get_page_int);

    }

    ASSERT_EQ(kol_result, kol_expected) << "Test failed";
}


TEST(e2e_test, second_test) {
    int size_cache = 4, kol_expected = 7, kol_result = 0;
    std::vector <int> vector_element = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    Ideal_cache<int, int> cache(size_cache);
    int index = 0;
    for (auto elem: vector_element) cache.data_put(elem, index++);

    for (int i = 0; i < vector_element.size(); i++){
        int key = vector_element[i];
        kol_result += cache.lookup_update(key, slow_get_page_int);

    }

    ASSERT_EQ(kol_result, kol_expected) << "Test failed";
}
TEST(e2e_test, third_test) {
    int size_cache = 3, kol_expected = 8, kol_result = 0;
    std::vector <int> vector_element = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};
    Ideal_cache<int, int> cache(size_cache);
    int index = 0;
    for (auto elem: vector_element) cache.data_put(elem, index++);

    for (int i = 0; i < vector_element.size(); i++){
        int key = vector_element[i];
        kol_result += cache.lookup_update(key, slow_get_page_int);

    }

    ASSERT_EQ(kol_result, kol_expected) << "Test failed";
}