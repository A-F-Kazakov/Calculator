/**
 * author   k 
 * date     06.08.17.
 */

#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H

#include <iostream>
#include <sstream>
#include <vector>
#include <exception>

#include <Token.h>
#include <Expression.h>
#include <NumberExpression.h>
#include <BinaryExpression.h>
#include <UnaryExpression.h>
#include <ostream>

class Parser
{
	public:
		static const Token end;

		Parser(const std::vector<Token>&);

		virtual ~Parser();

		std::vector<Expression*> parse();

		friend std::ostream& operator<<(std::ostream&, const Parser&);

	private:
		std::vector<Token> tokens;
		size_t currentPosition, length;
		std::vector<Expression*> result;

		Expression* expression();
		Expression* additive();
		Expression* multiplicative();
		Expression* unary();
		Expression* primary();

		const Token& get(size_t = 0);

		bool match(TokenType);
};

#endif //CALCULATOR_PARSER_H
