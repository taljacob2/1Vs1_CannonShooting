cmake_minimum_required(VERSION 3.16)
project(my_t1)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_t1 main.cpp cannon.cpp cannon.h board.cpp board.h my_utils.cpp my_utils.h)