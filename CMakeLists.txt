cmake_minimum_required(VERSION 3.7)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

set(CALCULATOR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

#=======================================================================================================================
# General config
#=======================================================================================================================

set(CALCULATOR_SOURCES  src/Lexer.cpp src/Token.cpp src/NumberExpression.cpp src/BinaryExpression.cpp
	 src/UnaryExpression.cpp src/Parser.cpp)

if(BUILD_SHARED_LIBS)
	add_library(${PROJECT_NAME} SHARED ${CALCULATOR_SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${CALCULATOR_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CALCULATOR_INCLUDE_DIR})

add_subdirectory(test)
