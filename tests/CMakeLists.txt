message(STATUS "Build ${PROJECT_NAME} tests enabled")

find_package(Catch2 CONFIG REQUIRED)

set(TARGET_NAME_HEAD ${PROJECT_NAME}-test)

add_compile_options(-O0 -g --coverage)
link_libraries(Catch2::Catch2 Parser --coverage)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}-lexer)

add_executable(${TARGET_NAME} lexer.cpp)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o ${TARGET_NAME}.xml -r junit)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}-parser)

add_executable(${TARGET_NAME} parser.cpp)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o ${TARGET_NAME}.xml -r junit)

