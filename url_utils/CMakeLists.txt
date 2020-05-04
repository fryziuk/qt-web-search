cmake_minimum_required(VERSION 3.15)

add_library(url_utils)

target_sources(url_utils
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include/url_searcher.h
        ${CMAKE_CURRENT_LIST_DIR}/include/downloader.h

        ${CMAKE_CURRENT_LIST_DIR}/src/downloader.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/url_searcher.cpp

        )
target_include_directories(url_utils
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        )

target_link_libraries(url_utils
        PUBLIC
        profiler
        Qt5::Core
        Qt5::Network
        )