/**
* @author   Казаков Андрей
* @date     06.08.17.
*/

#ifndef CALCULATOR_NUMBEREXPRESSION_H
#define CALCULATOR_NUMBEREXPRESSION_H

#include "Expression.h"

class NumberExpression : public Expression
{
	public:
		explicit NumberExpression(float);

		float eval() const override;

		void print(std::ostream& os) const override;

	private:
		float value;
};

#endif //CALCULATOR_NUMBEREXPRESSION_H
