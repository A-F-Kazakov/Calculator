cmake_minimum_required(VERSION 3.7)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
