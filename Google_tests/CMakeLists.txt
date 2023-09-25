project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_tests_run_lfu  ../src/lfu_cache.h test_2.cpp)
add_executable(Google_tests_run_ideal test1.cpp ../src/ideal_cache.h)
target_link_libraries(Google_tests_run_lfu gtest gtest_main)
target_link_libraries(Google_tests_run_ideal gtest gtest_main)