cmake_minimum_required(VERSION 3.5)

project(claes)

set(CMAKE_CXX_COMPILER clang++)

option(WITH_CURL "Add support for curl" ON)

if(WITH_CURL)
  add_definitions(-DUSE_CURL)
  find_library(CURL_LIBRARY NAMES curl curllib libcurl_imp curllib_static)
  add_link_options(-lcurl)
endif()

add_compile_options(-std=c++20 -fno-exceptions -Wall -Werror -g -O2 -fno-omit-frame-pointer -Wno-unused-variable -fsanitize=address,undefined)

add_link_options(-fsanitize=address,undefined)

file(GLOB_RECURSE src src/claes/*.cpp)

add_executable(bench ${src} src/bench.cpp)
target_include_directories(bench PUBLIC src/)

add_executable(claes ${src} src/main.cpp)
target_include_directories(claes PUBLIC src/)

add_executable(test ${src} src/test.cpp)
target_include_directories(test PUBLIC src/)
