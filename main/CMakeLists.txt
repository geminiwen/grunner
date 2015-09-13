set(DEPS_SOURCE_FILES ../deps/debug.h
        ../deps/debug.cpp
        ../deps/debug.h
        ../deps/global.h
        ../deps/run.h
        ../deps/limit.cpp
        ../deps/limit.h
        ../deps/run.cpp
        ../deps/run.h
        ../deps/check.h
        ../deps/check.cpp)


add_executable(GRunner execute_main.cpp ${DEPS_SOURCE_FILES})