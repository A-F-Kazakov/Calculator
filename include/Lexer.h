//
// Created by k on 28.07.17.
//

#ifndef CALCULATOR_LEXER_H
#define CALCULATOR_LEXER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <Token.h>

class Lexer
{
	public:
		Lexer(const std::string&);

		void tokenize();

		const std::vector<Token>& getTokens() const;

		friend std::ostream& operator<<(std::ostream&, const Lexer&);

	private:
		std::string input;
		std::vector<Token> tokens;
		size_t currentPosition, lenght;

		static std::string OPERATOR_CHARS;
		static TokenType OPERATOR_TYPES[];

		char peek(size_t = 0);
		char next();

		void tokenizeNumber();
		void tokenizeOperator(size_t);

		void tokenizeHex();

		void tokenizeBin();
};

#endif //CALCULATOR_LEXER_H