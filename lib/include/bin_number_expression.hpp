#ifndef CALCULATOR_BIN_NUMBER_EXPRESSION_HPP
#define CALCULATOR_BIN_NUMBER_EXPRESSION_HPP

#include <bitset>

#include "number_expression.hpp"

namespace calc::expression
{
	struct binary_number : number
	{
		explicit binary_number(double val) : number(val) {}
		explicit binary_number(const token& val) : number(static_cast<double>(std::strtol(val.data().data(), nullptr, 2))) {}

		void print(std::ostream& os) const override { os << std::bitset<16>(static_cast<uint64_t>(number::eval())); }
	};
} // namespace calc::expression

#endif //CALCULATOR_BIN_NUMBER_EXPRESSION_HPP
