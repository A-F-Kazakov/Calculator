#ifndef CALCULATOR_LEXER_HPP
#define CALCULATOR_LEXER_HPP

#include <ostream>
#include <string_view>
#include <token.hpp>

namespace calc
{
	template<template<typename, typename> typename Container>
	struct lexer
	{
		using data_type = Container<token, std::allocator<token>>;

		lexer() = default;

		void tokenize(std::string_view str)
		{
			for(auto c = str.cbegin(); c != str.cend(); c++)
			{
				if(*c == ' ')
				{
					c++;
					continue;
				}

				if(*c >= '0' && *c <= '9')
					tokenize_number(c, str.cend());
				else
					tokenize_operator(static_cast<size_t>(*c));
			}
		}

		const data_type& tokens() const { return m_tokens; };

		void clear() { m_tokens.clear(); }

	  private:
		data_type m_tokens;

		void tokenize_number(std::string_view::const_iterator begin, std::string_view::const_iterator end)
		{
			std::string str;
			auto t = token::type_t::number;

			bool check_format = false;

			if(*begin == '0')
				check_format = true;

			do
			{
				if(check_format && (*begin == 'x' || *begin == 'X') && t != token::type_t::bin_number)
					t = token::type_t::hex_number;

				if(check_format && (*begin == 'b' || *begin == 'B') && t != token::type_t::hex_number)
					t = token::type_t::bin_number;

				if(!check(*begin))
					break;

				if(*begin == ',')
					str.push_back('.');
				else
					str.push_back(*begin);

				begin++;
			} while(begin != end);

			m_tokens.emplace_back(t, std::move(str));
		}

		void tokenize_operator(size_t op) { m_tokens.emplace_back(static_cast<token::type_t>(op)); }

		bool check(char c)
		{
			return (c >= '0' && c <= '9') || (c == '.' || c == ',') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
		}
	};

	template<template<typename, typename> typename T>
	inline std::ostream& operator<<(std::ostream& os, const lexer<T>& lxr)
	{
		for(const auto& item : lxr.tokens())
			os << item << '\n';
		return os;
	}

} // namespace calc
#endif // CALCULATOR_LEXER_H
