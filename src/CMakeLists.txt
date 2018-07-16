set(LIB_SRC ${INCLUDE_DIR}/Lexer.h Lexer.cpp
	 ${INCLUDE_DIR}/Token.h Token.cpp
	 ${INCLUDE_DIR}/Expression.h
	 ${INCLUDE_DIR}/NumberExpression.h NumberExpression.cpp
	 ${INCLUDE_DIR}/BinaryExpression.h BinaryExpression.cpp
	 ${INCLUDE_DIR}/UnaryExpression.h UnaryExpression.cpp
	 ${INCLUDE_DIR}/Parser.h Parser.cpp)

add_library(${PROJECT_NAME} ${LIB_SRC})