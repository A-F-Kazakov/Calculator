#ifndef CALLCULATOR_FACTORIAL_EXPRESSION_HPP
#define CALLCULATOR_FACTORIAL_EXPRESSION_HPP

#include "expression.hpp"
#include "algorithm.hpp"

namespace calc::expression
{
	struct factorial : interface
	{
		factorial(std::unique_ptr<interface>&& ptr) : m_expr(std::move(ptr)) {}

		double eval() const override { return algorithm::factorial(m_expr->eval()); }

		void print(std::ostream& os) const override
		{
			m_expr->print(os);
			os << '!'; 
		}

		private:
			std::unique_ptr<interface> m_expr;
	};
}

#endif