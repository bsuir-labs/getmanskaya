cmake_minimum_required(VERSION 3.5)

project(lib-test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lib-test main.cpp lib.cpp lib.h)
