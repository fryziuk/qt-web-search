cmake_minimum_required(VERSION 3.15)

project(qt-web-searcher-test)


add_executable(url_searcher_test)

target_sources(url_searcher_test
        PRIVATE
        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/url_searcher_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/test_runner.h
        )


target_link_libraries(url_searcher_test
        PUBLIC
        url_utils
        Qt5::Core
        Qt5::Network
        )
