cmake_minimum_required(VERSION 3.15)

project(qt-web-searcher-test)

add_subdirectory(catch2)

add_executable(url_searcher_test)

target_sources(url_searcher_test
        PRIVATE
        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/url_searcher_test.cpp
        )


target_link_libraries(url_searcher_test
        PUBLIC
        url_utils
        catch2
        )

