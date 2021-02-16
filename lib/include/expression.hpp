#ifndef CALCULATOR_EXPRESSION_H
#define CALCULATOR_EXPRESSION_H

#include <memory>

namespace calc::expression
{
	struct interface
	{
		virtual ~interface() noexcept = default;

		virtual double eval() const = 0;

		virtual void print(std::ostream& os) const = 0;
	};

	inline std::ostream& operator<<(std::ostream& os, const interface& data)
	{
		data.print(os);
		return os;
	}
} // namespace calc

#endif // CALCULATOR_EXPRESSION_H
