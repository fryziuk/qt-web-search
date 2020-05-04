cmake_minimum_required(VERSION 3.15)

project(qt-web-searcher-test)

add_library(catch2)

target_sources(catch2
        PRIVATE
        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/include/catch2.hpp
        )


target_include_directories(catch2
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/include
        )
