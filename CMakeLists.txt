cmake_minimum_required(VERSION 3.7)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)

#=======================================================================================================================
# General config
#=======================================================================================================================

set(SOURCE_FILES src/main.cpp
	 src/Token.cpp
	 src/NumberExpression.cpp
	 src/BinaryExpression.cpp
	 src/UnaryExpression.cpp
	 src/algorithm.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#add_subdirectory(test)
