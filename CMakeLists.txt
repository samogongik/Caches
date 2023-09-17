cmake_minimum_required(VERSION 3.26)
project(ideal_cache)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Google_tests)

add_executable(ideal_cache src/main_ideal.cpp src/ideal_cache.cpp)
add_executable(lfu_cache src/main_lfu.cpp src/lfu_cache.cpp)
