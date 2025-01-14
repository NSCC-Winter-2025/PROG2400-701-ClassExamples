cmake_minimum_required(VERSION 3.30)
project(pointers)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(pointers main.cpp)
