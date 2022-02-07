cmake_minimum_required(VERSION 3.19)
project(Haffman C)

set(CMAKE_C_STANDARD 99)

add_executable(Haffman main.c decode.c decode.h)