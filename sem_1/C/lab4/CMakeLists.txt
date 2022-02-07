cmake_minimum_required(VERSION 3.19)
project(EditorMP3 C)

set(CMAKE_C_STANDARD 99)

add_executable(EditorMP3 main.c library/types.h library/constant.h library/header_and_frame.h library/ID3v2lib.h
        src/types.c src/header_and_frame.c src/ID3v2lib.c)