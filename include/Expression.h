/**
 * @author   Казаков Андрей
 * @date     06.08.17.
 */

#ifndef CALCULATOR_EXPRESSION_H
#define CALCULATOR_EXPRESSION_H

#include <ostream>

class Expression
{
	public:
		virtual ~Expression() = default;

		virtual float eval() const = 0;

		virtual void print(std::ostream& os) const = 0;

		friend std::ostream& operator<<(std::ostream&, const Expression&);
};

inline std::ostream& operator<<(std::ostream& os, const Expression& data)
{
	data.print(os);
	return os;
}

#endif //CALCULATOR_EXPRESSION_H
