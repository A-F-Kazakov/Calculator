cmake_minimum_required(VERSION 3.13)

project(Calculator)

add_subdirectory(lib)
add_subdirectory(app)

find_package(Catch2 QUIET)

if(Catch2_FOUND)
	add_subdirectory(tests)
endif()
