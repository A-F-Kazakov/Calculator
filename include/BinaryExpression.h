/**
 * author   k 
 * date     06.08.17.
 */

#ifndef CALCULATOR_BINARYEXPRESSION_H
#define CALCULATOR_BINARYEXPRESSION_H

#include <ostream>
#include <iostream>
#include <Expression.h>

class BinaryExpression : public Expression
{
	public:
		BinaryExpression(char, Expression*, Expression*);

		virtual ~BinaryExpression();

		float eval();
		void print(std::ostream& os) const;

	private:
		Expression* expr1, *expr2;
		char operation;
};

#endif //CALCULATOR_BINARYEXPRESSION_H
