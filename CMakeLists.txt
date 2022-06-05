cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 0.0.20)

option(BUILD_TESTS "Build ${PROJECT_NAME} tests" OFF)

add_subdirectory(lib)
add_subdirectory(app)

if(${BUILD_TESTS})
	enable_testing()
	add_subdirectory(tests)
endif()
