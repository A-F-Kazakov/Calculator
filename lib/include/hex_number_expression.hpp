#ifndef CALCULATOR_HEX_NUMBER_EXPRESSION_HPP
#define CALCULATOR_HEX_NUMBER_EXPRESSION_HPP

#include "number_expression.hpp"

namespace calc::expression
{
	struct hex_number : number
	{
		explicit hex_number(double val) : number(val) {}
		explicit hex_number(const token& val) : number(std::strtol(val.data().data(), nullptr, 16)) {}


		void print(std::ostream& os) const override { os << std::hex << static_cast<int>(number::eval()); }
	};
} // namespace calc::expression

#endif //CALCULATOR_HEX_NUMBER_EXPRESSION_HPP
