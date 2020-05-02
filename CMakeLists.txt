cmake_minimum_required(VERSION 3.15)

project(qt-web-search)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Quick Core Network QuickControls2 REQUIRED)

add_executable(qt-web-search)

target_sources(qt-web-search
        PUBLIC
        # headers
        ${CMAKE_CURRENT_LIST_DIR}/include/controller.h
        ${CMAKE_CURRENT_LIST_DIR}/include/web_search_result.h
        ${CMAKE_CURRENT_LIST_DIR}/include/worker.h
        ${CMAKE_CURRENT_LIST_DIR}/include/concurrent_queue.h
        ${CMAKE_CURRENT_LIST_DIR}/include/utils.h

        # sources
        ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/controller.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/worker.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/web_search_result.cpp

        # resources
        ${CMAKE_CURRENT_LIST_DIR}/qml/resources.qrc
        )

target_include_directories(qt-web-search
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        )


target_link_libraries(qt-web-search PRIVATE
        Qt5::Core
        Qt5::Quick
        Qt5::Qml
        Qt5::QuickControls2
        Qt5::Network
        )
