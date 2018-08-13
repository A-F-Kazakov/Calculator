/**
* @author   Казаков Андрей
* @date     06.08.17.
*/

#ifndef CALCULATOR_UNARYEXPRESSION_H
#define CALCULATOR_UNARYEXPRESSION_H

//#include <ostream>
//#include <iostream>
#include "Expression.h"

class UnaryExpression : public Expression
{
	public:
		UnaryExpression(char, Expression*);

		~UnaryExpression() override;

		float eval() const override;

		void print(std::ostream& os) const override;

	private:
		char operation;
		Expression* data;
};

#endif //CALCULATOR_UNARYEXPRESSION_H
