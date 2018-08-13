/**
 * @author   Казаков Андрей
 * @date     06.08.17.
 */

#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H

#include "Token.h"
#include "Expression.h"
#include "NumberExpression.h"
#include "HexNumberExpression.h"
#include "BinNumberExpression.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "Lexer.h"

template<template <typename, typename> typename C1, template <typename, typename> typename C2>
class Parser
{
	public:
		typedef C1<Expression*, std::allocator<Token>> dataType;
		typedef C2<Token, std::allocator<Token>> inputType;

		explicit Parser(const inputType& data) : tokens(data), currentPosition(0) {}
		explicit Parser(inputType&& data) : tokens(std::move(data)), currentPosition(0) {}

		virtual ~Parser()
		{
			for(const auto& item : result)
				delete(item);
			result.clear();
		}

		void parse()
		{
			while(!match(Token::Type::NONE))
				result.emplace_back(expression());
		}

		dataType getExpression() const { return result; }

		friend std::ostream& operator<<(std::ostream& os, const Parser& parser)
		{
			for(auto&& it : parser.result)
				it->print(os);
			return os;
		}

	private:
		inputType tokens;
		size_t currentPosition;
		dataType result;

		Expression* expression() { return additive(); }
		Expression* additive()
		{
			Expression* result = multiplicative();

			while(true)
			{
				if(match(Token::Type::PLUS))
				{
					result = new BinaryExpression('+', result, multiplicative());
					continue;
				}
				if(match(Token::Type::MINUS))
				{
					result = new BinaryExpression('-', result, multiplicative());
					continue;
				}
				break;
			}

			return result;
		}

		Expression* multiplicative()
		{
			Expression* res = unary();

			while(true)
			{
				// 2 * 6 / 3
				if(match(Token::Type::MULTIPLY))
				{
					res = new BinaryExpression('*', res, unary());
					continue;
				}
				if(match(Token::Type::DIVISION))
				{
					res = new BinaryExpression('/', res, unary());
					continue;
				}
				break;
			}

			return res;
		}

		Expression* unary()
		{
			if(match(Token::Type::MINUS))
				return new UnaryExpression('-', primary());
			return primary();
		}

		Expression* primary()
		{
			const Token& current = get();

			if(match(Token::Type::NUMBER))
				return new NumberExpression(static_cast<float>(atof(current.getData().c_str())));

			if(match(Token::Type::HEX_NUMBER))
				return new HexNumberExpression(std::stoul(current.getData(), nullptr, 16));

			if(match(Token::Type::BIN_NUMBER))
			{
				std::string tmp = current.getData();
				tmp.erase(0,2);
				return new BinNumberExpression(std::stoi(tmp, nullptr, 2));
			}

			if(match(Token::Type::L_BRACKET))
			{
				Expression* result = expression();
				match(Token::Type::R_BRACKET);
				return result;
			}

			throw std::runtime_error("unsupported expression");
		}

		const Token& get(size_t relativePosition = 0)
		{
			size_t position = currentPosition + relativePosition;
			if(position >= tokens.size())
				return std::move(Token(Token::Type::NONE));

			return tokens.at(position);
		}

		bool match(Token::Type type)
		{
			const Token& current  = get();
			if(current.getType() != type)
				return  false;
			++currentPosition;

			return true;
		}
};

#endif //CALCULATOR_PARSER_H
