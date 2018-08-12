/**
 * @author   Казаков Андрей
 * @date     28.08.17.
 */

#ifndef CALCULATOR_LEXER_H
#define CALCULATOR_LEXER_H

#include <sstream>
#include <string_view>
#include <ostream>

#include "Token.h"

template<template<typename, typename> typename Container>
class Lexer
{
	public:
		typedef Container<Token, std::allocator<Token>> dataType;

		Lexer() = default;

		void tokenize(std::string_view str)
		{
			size_t currentPosition = 0;
			char c = 0;
			while(currentPosition < str.size())
			{
				c = str.at(currentPosition);
				if(c == ' ')
				{
					++currentPosition;
					continue;
				}

				if(c >= '0' && c <= '9')
					currentPosition = tokenizeNumber(str, currentPosition);
				else
				{
					tokenizeOperator(c);
					++currentPosition;
				}
			}
		}

		const dataType& getTokens() const { return this->tokens; };

		friend std::ostream& operator<<(std::ostream& os, const Lexer& lexer)
		{
			for(auto&& item : lexer.tokens)
				os << item << '\n';
			return os;
		}

	private:
		dataType tokens;

		size_t tokenizeNumber(std::string_view str, size_t pos)
		{
			std::stringstream ss;

			Token::Type t = Token::Type::NUMBER;
			char c = 0;

			do
			{
				c = str.at(pos);

				if((c == 'x' || c == 'X') && ss.peek() == '0')
					t = Token::Type::HEX_NUMBER;

				if((c == 'b' || c == 'B') && ss.peek() == '0')
					t = Token::Type::BIN_NUMBER;

				if(c == ',')
					c = '.';

				if(!check(c))
					break;
				ss << c;
				++pos;
			}
			while(pos < str.length());

			tokens.emplace_back(t, ss.str());
			return pos;
		}

		void tokenizeOperator(size_t op) { tokens.emplace_back(static_cast<Token::Type>(op)); }

		inline bool check(char c)
		{
			return (c >= '0' && c <= '9') ||
					 (c == '.' || c == ',') ||
					 (c == 'x' || c == 'X') ||
					 (c == 'b' || c == 'B') ||
					 (c >= 'A' && c <= 'F') ||
					 (c >= 'a' && c <= 'f');
		}
};

#endif //CALCULATOR_LEXER_H