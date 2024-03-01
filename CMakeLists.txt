cmake_minimum_required(VERSION 3.5)

project(claes)

set(CMAKE_CXX_COMPILER clang++)

add_compile_options(-std=c++20 -fno-exceptions -Wall -Werror -g -O2 -fno-omit-frame-pointer -fsanitize=address,undefined)

add_link_options(-fsanitize=address,undefined)

file(GLOB_RECURSE src src/claes/*.cpp)

add_executable(test ${src} src/test.cpp)
target_include_directories(test PUBLIC src/)