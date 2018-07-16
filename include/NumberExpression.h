/**
 * author   k 
 * date     06.08.17.
 */

#ifndef CALCULATOR_NUMBEREXPRESSION_H
#define CALCULATOR_NUMBEREXPRESSION_H

#include <ostream>
#include <iostream>
#include <Expression.h>

class NumberExpression : public Expression
{
	public:
		NumberExpression(float);

		float eval();

		void print(std::ostream& os) const;

	private:
		float value;
};

#endif //CALCULATOR_NUMBEREXPRESSION_H
