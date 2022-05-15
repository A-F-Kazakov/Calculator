#ifndef CALCULATOR_TOKEN_HPP
#define CALCULATOR_TOKEN_HPP

#include <ostream>
#include <string_view>

namespace calc
{
	struct token
	{
		enum type_t
		{
			none,
			number,
			hex_number,
			bin_number,
			plus = '+',
			minus = '-',
			multiply = '*',
			division = '/',
			l_bracket = '(',
			r_bracket = ')',
			factorial = '!'
		};

		token() = default;

		explicit token(type_t t) : m_type(t) {}

		token(type_t t, std::string str) : m_type(t), m_data(std::move(str)) {}

		std::string_view data() const { return m_data; }

		void data(std::string data) { m_data = std::move(data); }

		type_t type() const { return m_type; }

		void type(type_t t) { m_type = t; }

	  private:
		type_t m_type{none};
		std::string m_data;
	};

	inline std::ostream& operator<<(std::ostream& os, token::type_t type)
	{
		switch(type)
		{
			case token::number:
				os << "NUMBER";
				break;
			case token::division:
				os << "DIVISION";
				break;
			case token::plus:
				os << "PLUS";
				break;
			case token::minus:
				os << "MINUS";
				break;
			case token::multiply:
				os << "MULTIPLY";
				break;
			case token::hex_number:
				os << "HEX";
				break;
			case token::bin_number:
				os << "BIN";
				break;
			case token::l_bracket:
				os << "LEFT_BRACKET";
				break;
			case token::r_bracket:
				os << "RIGHT_BRACKET";
				break;
			case token::factorial:
				os << "FACTORIAL";
				break;
			case token::none:
			default:
				os << "unknown";
		}
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, token t)
	{
		os << "Token: " << t.type() << "(" << t.data() << ")";
		return os;
	}
} // namespace parser

#endif // CALCULATOR_TOKEN_H
