message(STATUS "Build ${PROJECT_NAME} tests enabled")

find_package(Catch2 REQUIRED)

set(TARGET_NAME_HEAD ${PROJECT_NAME}-test)

add_compile_options(-O0 -g --coverage)
link_libraries(Catch2::Catch2 Parser --coverage)

set(TARGETS)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}-lexer)
list(APPEND TARGETS ${TARGET_NAME})

add_executable(${TARGET_NAME} lexer.cpp)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o ${TARGET_NAME}.xml -r junit)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}-parser)
list(APPEND TARGETS ${TARGET_NAME})

add_executable(${TARGET_NAME} parser.cpp)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o ${TARGET_NAME}.xml -r junit)

# All in one target

set(TARGET_NAME ${TARGET_NAME_HEAD}s)
add_custom_target(${TARGET_NAME} DEPENDS ${TARGETS})

add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
		COMMAND ctest -C $<CONFIGURATION> --output-on-failure
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
