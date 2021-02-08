#ifndef CALCULATOR_PARSER_HPP
#define CALCULATOR_PARSER_HPP

#include "bin_number_expression.hpp"
#include "hex_number_expression.hpp"
#include "binary_expression.hpp"
#include "unary_expression.hpp"
#include "factorial_expression.hpp"
#include "lexer.hpp"

namespace calc
{
	template<template<typename, typename> typename In, template<typename, typename> typename Out>
	struct parser
	{
		using expression_t = expression::interface;
		using data_type  = Out<std::unique_ptr<expression_t>, std::allocator<std::unique_ptr<expression_t>>>;
		using input_type = In<token, std::allocator<token>>;

		explicit parser(const input_type& data) : m_tokens(data) {}

		void parse()
		{
			m_current = m_tokens.cbegin();
			while(m_current != m_tokens.cend())
				m_result.push_back(expression());
		}

		const data_type& expressions() const { return m_result; }

	  private:
		const input_type& m_tokens;
		typename input_type::const_iterator m_current;
		data_type m_result;

		std::unique_ptr<expression_t> expression() { return additive(); }

		std::unique_ptr<expression_t> additive()
		{
			auto result = multiplicative();

			while(true)
			{
				if(match(token::type_t::plus))
				{
					get();
					result = std::make_unique<expression::binary>('+', std::move(result), multiplicative());
					continue;
				}

				if(match(token::type_t::minus))
				{
					get();
					result = std::make_unique<expression::binary>('-', std::move(result), multiplicative());
					continue;
				}
				break;
			}

			return std::move(result);
		}

		std::unique_ptr<expression_t> multiplicative()
		{
			auto result = unary();

			while(true)
			{
				// 2 * 6 / 3
				if(match(token::type_t::multiply))
				{
					get();
					result = std::make_unique<expression::binary>('*', std::move(result), unary());
					continue;
				}

				if(match(token::type_t::division))
				{
					get();
					result = std::make_unique<expression::binary>('/', std::move(result), unary());
					continue;
				}
				break;
			}

			return std::move(result);
		}

		std::unique_ptr<expression_t> unary()
		{
			if(match(token::type_t::minus))
			{
				get();
				return std::make_unique<expression::unary>('-', primary());
			}

			return primary();
		}

		std::unique_ptr<expression_t> primary()
		{
			std::unique_ptr<expression_t> result;

			if(match(token::number))
				result = std::make_unique<expression::number>(get());

			if(match(token::hex_number))
				result = std::make_unique<expression::hex_number>(get());

			if(match(token::bin_number))
				result = std::make_unique<expression::binary_number>(get());

			if(match(token::factorial))
			{
				if(!result)
					throw std::runtime_error("wrond operator");

				result		= std::make_unique<expression::factorial>(std::move(result));
				get();
			}

			if(match(token::l_bracket))
			{
				get();
				result = expression();
				get(); // close bracket
			}

			if(!result)
				throw std::runtime_error("unsupported expression");

			return std::move(result);
		}

		const token& get()
		{
			auto& ref = *m_current;
			m_current++;
			return ref;
		}

		bool match(token::type_t type)
		{
			if(m_current == m_tokens.cend() || m_current->type() != type)
				return false;
			return true;
		}
	};

	template<template<typename, typename> typename In, template<typename, typename> typename Out>
	inline std::ostream& operator<<(std::ostream& os, const parser<In, Out>& parser)
	{
		for(const auto& it : parser.expressions())
			it->print(os);

		return os;
	}

} // namespace calc
#endif // CALCULATOR_PARSER_HPP
