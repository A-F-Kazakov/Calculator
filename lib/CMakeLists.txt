project(Parser)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_sources(${PROJECT_NAME}
	INTERFACE
		include/algorithm.hpp
		include/binary_expression.hpp
		include/bin_number_expression.hpp
		include/expression.hpp
		include/factorial_expression.hpp
		include/hex_number_expression.hpp
		include/lexer.hpp
		include/number_expression.hpp
		include/parser.hpp
		include/token.hpp
		include/unary_expression.hpp
)

add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

if(COMMAND enable_sanitizers)
	enable_sanitizers(${PROJECT_NAME}
		${ENABLE_SANITIZER_ADDRESS}
		${ENABLE_SANITIZER_LEAK}
		${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR}
		${ENABLE_SANITIZER_THREAD}
		${ENABLE_SANITIZER_MEMORY}
		)
endif()
