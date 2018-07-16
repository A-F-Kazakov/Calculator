/**
 * author   k 
 * date     06.08.17.
 */

#ifndef CALCULATOR_UNARYEXPRESSION_H
#define CALCULATOR_UNARYEXPRESSION_H

#include <ostream>
#include <iostream>
#include <Expression.h>

class UnaryExpression : public Expression
{
	public:
		UnaryExpression(char, Expression*);

		virtual ~UnaryExpression();

		float eval();
		void print(std::ostream& os) const;

	private:
		char operation;
		Expression* data;
};

#endif //CALCULATOR_UNARYEXPRESSION_H
