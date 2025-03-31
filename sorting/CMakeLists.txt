cmake_minimum_required(VERSION 3.30)
project(sorting)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(sorting main.cpp binary_search_tree.cpp sorting.cpp)
