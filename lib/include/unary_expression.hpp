#ifndef CALCULATOR_UNARY_EXPRESSION_HPP
#define CALCULATOR_UNARY_EXPRESSION_HPP

#include "expression.hpp"

namespace calc::expression
{
	struct unary : interface
	{
		unary(size_t operation, std::unique_ptr<interface>&& data) : m_operation(operation), m_data(std::move(data)) {}

		unary(const unary&) = delete;

		unary& operator=(const unary&) = delete;

		double eval() const override { return -(m_data->eval()); }

		void print(std::ostream& os) const override { os << m_operation << *m_data; }

	  private:
		size_t m_operation;
		std::unique_ptr<interface> m_data;
	};
} // namespace calc

#endif //CALCULATOR_UNARY_EXPRESSION_HPP
