cmake_minimum_required(VERSION 3.13)

project(Calculator VERSION 0.0.17)

option(BUILD_TESTS "Build ${PROJECT_NAME} tests" OFF)

add_subdirectory(lib)
add_subdirectory(app)

if(${BUILD_TESTS})
	add_subdirectory(tests)
endif()
