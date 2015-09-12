cmake_minimum_required(VERSION 3.3)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES src/main.cpp src/debug.h src/debug.cpp src/debug.h src/global.h src/run.h src/limit.cpp src/limit.h)
add_executable(GRunner ${SOURCE_FILES})