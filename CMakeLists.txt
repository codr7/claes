cmake_minimum_required(VERSION 3.5)

project(claes)

set(CMAKE_CXX_COMPILER clang++)

option(WITH_CURL "Add support for curl" ON)
option(WITH_SQLITE "Add support for sqlite" ON)

if(WITH_CURL)
  add_definitions(-DUSE_CURL)
  find_library(CURL_LIBRARY NAMES curl curllib libcurl_imp curllib_static)
  add_link_options(-lcurl)
endif()

if(WITH_SQLITE)
  add_definitions(-DUSE_SQLITE)
  find_library(CURL_LIBRARY NAMES sqllite3)
  add_link_options(-lsqlite3)
endif()

add_compile_options(-std=c++20 -fno-exceptions -Wall -Werror -g -O2 -Wno-unused-variable)

file(GLOB_RECURSE src src/claes/*.cpp)

add_executable(bench ${src} src/bench.cpp)
target_include_directories(bench PUBLIC src/)

add_executable(claes ${src} src/main.cpp)
target_include_directories(claes PUBLIC src/)

add_executable(test ${src} src/test.cpp)
target_include_directories(test PUBLIC src/)
