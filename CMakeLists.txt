cmake_minimum_required(VERSION 3.7)
project(Calculator)

set(CMAKE_CXX_STANDARD 14)

set(CALCULATOR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CALCULATOR_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" PARENT_SCOPE)

#=======================================================================================================================
# General config
#=======================================================================================================================

set(CALCULATOR_SOURCES ${CALCULATOR_INCLUDE_DIR}/Expression.h
	 ${CALCULATOR_INCLUDE_DIR}/Lexer.h					src/Lexer.cpp
	 ${CALCULATOR_INCLUDE_DIR}/Token.h 					src/Token.cpp
	 ${CALCULATOR_INCLUDE_DIR}/NumberExpression.h 	src/NumberExpression.cpp
	 ${CALCULATOR_INCLUDE_DIR}/BinaryExpression.h 	src/BinaryExpression.cpp
	 ${CALCULATOR_INCLUDE_DIR}/UnaryExpression.h 	src/UnaryExpression.cpp
	 ${CALCULATOR_INCLUDE_DIR}/Parser.h 				src/Parser.cpp)

if(BUILD_SHARED_LIBS)
	add_library(${PROJECT_NAME} SHARED ${CALCULATOR_SOURCES})
else()
	add_library(${PROJECT_NAME} STATIC ${CALCULATOR_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CALCULATOR_INCLUDE_DIR})
