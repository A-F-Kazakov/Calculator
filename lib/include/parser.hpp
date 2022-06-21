#ifndef CALCULATOR_PARSER_HPP
#define CALCULATOR_PARSER_HPP

#include "bin_number_expression.hpp"
#include "binary_expression.hpp"
#include "factorial_expression.hpp"
#include "hex_number_expression.hpp"
#include "unary_expression.hpp"

namespace calc
{
	namespace
	{
		using expression_t = std::unique_ptr<expression::interface>;

		template<typename Iterator>
		expression_t additive(Iterator&, Iterator);

		template<typename Iterator>
		expression_t primary(Iterator& begin, Iterator end)
		{
			switch(begin->type())
			{
				case token::number:
					return std::make_unique<expression::number>(*begin++);
				case token::hex_number:
					return std::make_unique<expression::hex_number>(*begin++);
				case token::bin_number:
					return std::make_unique<expression::binary_number>(*begin++);
				case token::l_bracket:
				{
					++begin;
					auto result = additive(begin, end);

					if(begin != end && begin->type() == token::r_bracket)
						++begin;
					return result;
				}
				default:
					throw std::runtime_error("unsupported expression");
			}
		}

		template<typename Iterator>
		expression_t unary(Iterator& begin, Iterator end)
		{
			if(begin->type() == token::minus)
				return std::make_unique<expression::unary>('-', primary(++begin, end));
			return primary(begin, end);
		}

		template<typename Iterator>
		expression_t functions(Iterator& begin, Iterator end)
		{
			auto result = unary(begin, end);

			if(begin != end && begin->type() == token::factorial)
			{
				++begin;
				return std::make_unique<expression::factorial>(std::move(result));
			}
			return result;
		}

		template<typename Iterator>
		expression_t multiplicative(Iterator& begin, Iterator end)
		{
			auto result = functions(begin, end);

			while(begin != end)
			{
				// 2 * 6 / 3
				if(begin->type() == token::multiply)
				{
					result = std::make_unique<expression::binary>('*', std::move(result), unary(++begin, end));
					continue;
				}

				if(begin->type() == token::division)
				{
					result = std::make_unique<expression::binary>('/', std::move(result), unary(++begin, end));
					continue;
				}
				break;
			}

			return result;
		}

		template<typename Iterator>
		expression_t additive(Iterator& begin, Iterator end)
		{
			auto result = multiplicative(begin, end);

			while(begin != end)
			{
				if(begin->type() == token::plus)
				{
					result = std::make_unique<expression::binary>('+', std::move(result),
						multiplicative(++begin, end));
					continue;
				}

				if(begin->type() == token::minus)
				{
					result = std::make_unique<expression::binary>('-', std::move(result),
						multiplicative(++begin, end));
					continue;
				}
				break;
			}

			return result;
		}
	}

	template<
		template<typename, typename> typename Container,
		typename Tokens,
		template<typename> typename Allocator = std::allocator
		>
	auto parse(const Tokens& tokens)
	{
		Container<expression_t, Allocator<expression_t>> expressions;

		auto begin = tokens.begin();
		auto end = tokens.end();

		while(begin != end)
			expressions.push_back(additive(begin, end));

		return expressions;
	}
} // namespace calc
#endif // CALCULATOR_PARSER_HPP
