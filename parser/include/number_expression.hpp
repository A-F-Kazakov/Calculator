#ifndef CALCULATOR_NUMBER_EXPRESSION_HPP
#define CALCULATOR_NUMBER_EXPRESSION_HPP

#include "expression.hpp"
#include <string>

namespace calc::expression
{
	struct number : interface
	{
		explicit number(double val) : m_value(val) {}
		explicit number(token t) : m_value(static_cast<double>(std::stod(t.data().data()))) {}

		double eval() const override { return m_value; }

		void print(std::ostream& os) const override { os << m_value; }

		double data() const noexcept { return m_value; }

		void data(double dta) noexcept { m_value = dta; }

	  private:
		double m_value;
	};
} // namespace calc::expression

#endif //CALCULATOR_NUMBER_EXPRESSION_HPP
