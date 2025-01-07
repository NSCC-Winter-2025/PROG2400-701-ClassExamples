cmake_minimum_required(VERSION 3.30)
project(best_practices)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "-static")

add_executable(best_practices
        src/main.cpp
        src/best_practices.cpp
        src/best_practices_app.cpp
)

target_include_directories(best_practices
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)