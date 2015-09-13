cmake_minimum_required(VERSION 3.3)
project(node)

set(DEPS_SOURCE_FILES ../deps/debug.h
        ../deps/debug.cpp
        ../deps/debug.h
        ../deps/global.h
        ../deps/run.h
        ../deps/limit.cpp
        ../deps/limit.h
        ../deps/run.cpp
        ../deps/run.h
        ../deps/check.cpp
        ../deps/check.h)

set(CMAKE_JS_INC "/Users/geminiwen/.cmake-js/node-x64/v4.0.0/src;/Users/geminiwen/.cmake-js/node-x64/v4.0.0/deps/v8/include;/Users/geminiwen/.cmake-js/node-x64/v4.0.0/deps/uv/include")
include_directories(${CMAKE_JS_INC})


set(SOURCE_FILES ${DEPS_SOURCE_FILES} ../deps/check.cpp ../deps/check.h)

add_library(grunner SHARED exports.cpp ${SOURCE_FILES})

set_target_properties(grunner PROPERTIES PREFIX "" SUFFIX ".node")

#message(STATUS ${CMAKE_JS_LIB})
#target_link_libraries(grunner ${CMAKE_JS_LIB})
