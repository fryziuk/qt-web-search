cmake_minimum_required(VERSION 3.15)

project(qt-web-search)

include(cmake/clangformat.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)

##set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
#include(CTest)

find_package(Qt5 COMPONENTS Quick Core Network QuickControls2 REQUIRED)

add_subdirectory(profiler)
add_subdirectory(url_utils)

add_executable(qt-web-search)

target_sources(qt-web-search
        PRIVATE
        # Headers
        ${CMAKE_CURRENT_LIST_DIR}/include/Controller.h
        ${CMAKE_CURRENT_LIST_DIR}/include/web_search_result.h
        ${CMAKE_CURRENT_LIST_DIR}/include/worker.h
        ${CMAKE_CURRENT_LIST_DIR}/include/concurrent_queue.h
        ${CMAKE_CURRENT_LIST_DIR}/include/utils.h
        ${CMAKE_CURRENT_LIST_DIR}/include/downloader.h

        # Sources
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/Controller.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/worker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/web_search_result.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/downloader.cpp

        # Resources
        ${CMAKE_CURRENT_LIST_DIR}/qml/resources.qrc
        )

target_include_directories(qt-web-search
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
        )


target_link_libraries(qt-web-search
        PUBLIC
        profiler
            url_utils
        PRIVATE
            Qt5::Quick
            Qt5::Qml
            Qt5::QuickControls2
            Qt5::Network
        )

add_clangformat(qt-web-search)


add_subdirectory(test)


#target_compile_options(qt-web-search
#        PUBLIC
#        "-fsanitize=address,undefined"
#        "-fno-omit-frame-pointer"
#        )
#target_link_options(qt-web-search
#        PUBLIC
#        "-fsanitize=address,undefined"
#        )


