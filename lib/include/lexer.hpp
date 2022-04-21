#ifndef CALCULATOR_LEXER_HPP
#define CALCULATOR_LEXER_HPP

#include <string_view>
#include <token.hpp>

namespace calc
{
	namespace
	{
		constexpr bool check(char c)
		{
			return (c >= '0' && c <= '9') || (c == '.' || c == ',') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (c == 'x' || c == 'X');
		}

		template<typename Container>
		void tokenize_number(Container& tokens, std::string_view::const_iterator& begin, std::string_view::const_iterator end)
		{
			std::string str;
			auto t = token::number;

			do
			{
				if(t == token::number && (*begin == 'x' || *begin == 'X'))
					t = token::hex_number;

				if(t == token::number && (*begin == 'b' || *begin == 'B'))
					t = token::bin_number;

				if(!check(*begin))
					break;

				if(*begin == ',')
					str.push_back('.');
				else
					str.push_back(*begin);

				begin++;
			} while(begin != end);

			tokens.emplace_back(t, std::move(str));
		}
	} // namespace

	template<template<typename T> typename Container>
	Container<token> tokenize(std::string_view str)
	{
		Container<token> tokens;
		auto c = str.begin();
		do
		{
			if(*c == ' ')
			{
				++c;
				continue;
			}

			if(*c >= '0' && *c <= '9')
				tokenize_number(tokens, c, str.end());
			else
			{
				 tokens.emplace_back(static_cast<token::type_t>(*c)); 
				++c;
			}
		}
		while(c != str.end());

		return tokens;
	}
} // namespace calc
#endif // CALCULATOR_LEXER_H
