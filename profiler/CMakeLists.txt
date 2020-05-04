cmake_minimum_required(VERSION 3.15)

# Simple profile library
add_library(profiler INTERFACE)

target_include_directories(profiler
        INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include/
        )