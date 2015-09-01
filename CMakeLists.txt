cmake_minimum_required(VERSION 3.3)
project(GRunner)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES grunner/main.cpp grunner/debug.h grunner/debug.cpp grunner/debug.h grunner/global.h)
add_executable(GRunner ${SOURCE_FILES})