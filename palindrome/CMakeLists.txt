cmake_minimum_required(VERSION 3.30)
project(palindrome)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(palindrome main.cpp)
