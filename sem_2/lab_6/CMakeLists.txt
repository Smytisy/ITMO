cmake_minimum_required(VERSION 3.19)
project(Proga_lab6)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(Proga_lab6 main.cpp tests.cpp Polynomial.h delete.cpp)
target_link_libraries(Proga_lab6 gtest gtest_main)