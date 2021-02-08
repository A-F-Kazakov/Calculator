#ifndef CALCULATOR_UNARY_EXPRESSION_HPP
#define CALCULATOR_UNARY_EXPRESSION_HPP

#include "expression.hpp"

namespace calc::expression
{
	struct unary : interface
	{
		unary(char operation, std::unique_ptr<interface>&& data) : m_operation(operation), m_data(std::move(data)) {}

		double eval() const override { return -(m_data->eval()); }

		void print(std::ostream& os) const override { os << m_operation << *m_data; }

	  private:
		char m_operation;
		std::unique_ptr<interface> m_data;
	};
} // namespace calc

#endif //CALCULATOR_UNARY_EXPRESSION_HPP
