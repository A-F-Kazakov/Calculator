#ifndef CALCULATOR_PARSER_HPP
#define CALCULATOR_PARSER_HPP

#include "bin_number_expression.hpp"
#include "binary_expression.hpp"
#include "factorial_expression.hpp"
#include "hex_number_expression.hpp"
#include "lexer.hpp"
#include "unary_expression.hpp"

namespace calc
{
	template<template<typename, typename> typename In, template<typename, typename> typename Out>
	struct parser
	{
		using expression_t = std::unique_ptr<expression::interface>;
		using data_type	 = Out<expression_t, std::allocator<expression_t>>;
		using input_type	 = In<token, std::allocator<token>>;

		parser() = default;

		void parse(const input_type& tokens)
		{
			m_current = tokens.cbegin();
			m_end		 = tokens.cend();

			while(m_current != tokens.cend())
				m_result.push_back(expression());
		}

		const data_type& expressions() const { return m_result; }

		void clear() { m_result.clear(); }

		typename data_type::const_iterator begin() const { return m_result.cbegin(); }

		typename data_type::const_iterator end() const { return m_result.cend(); }

	  private:
		typename input_type::const_iterator m_current;
		typename input_type::const_iterator m_end;
		data_type m_result;
		constexpr static bool pop_element = true;

		expression_t expression() { return additive(); }

		expression_t additive()
		{
			auto result = multiplicative();

			while(true)
			{
				if(match(token::plus, pop_element))
				{
					result = std::make_unique<expression::binary>('+', std::move(result), multiplicative());
					continue;
				}

				if(match(token::minus, pop_element))
				{
					result = std::make_unique<expression::binary>('-', std::move(result), multiplicative());
					continue;
				}
				break;
			}

			return std::move(result);
		}

		expression_t multiplicative()
		{
			auto result = functions();

			while(true)
			{
				// 2 * 6 / 3
				if(match(token::multiply, pop_element))
				{
					result = std::make_unique<expression::binary>('*', std::move(result), unary());
					continue;
				}

				if(match(token::division, pop_element))
				{
					result = std::make_unique<expression::binary>('/', std::move(result), unary());
					continue;
				}
				break;
			}

			return std::move(result);
		}

		expression_t functions()
		{
			auto result = unary();

			if(match(token::factorial, pop_element))
				return std::make_unique<expression::factorial>(std::move(result));
			return result;
		}

		expression_t unary()
		{
			if(match(token::minus, pop_element))
				return std::make_unique<expression::unary>('-', primary());
			return primary();
		}

		expression_t primary()
		{
			if(match(token::number))
				return std::make_unique<expression::number>(get());

			if(match(token::hex_number))
				return std::make_unique<expression::hex_number>(get());

			if(match(token::bin_number))
				return std::make_unique<expression::binary_number>(get());

			if(match(token::l_bracket))
			{
				get();
				auto result = expression();
				get();
				return result;
			}

			throw std::runtime_error("unsupported expression");
		}

		const token& get()
		{
			auto& ref = *m_current;
			m_current++;
			return ref;
		}

		bool match(const token::type_t type, const bool pop = false)
		{
			if(m_current == m_end || m_current->type() != type)
				return false;

			if(pop)
				get();

			return true;
		}
	};

	template<template<typename, typename> typename In, template<typename, typename> typename Out>
	inline std::ostream& operator<<(std::ostream& os, const parser<In, Out>& parser)
	{
		auto it = parser.begin(); 
		while(it != parser.end())
		{
			(*it)->print(os);
			it++;
			if(it != parser.end())
				os << ", ";
		}

		return os;
	}

} // namespace calc
#endif // CALCULATOR_PARSER_HPP
