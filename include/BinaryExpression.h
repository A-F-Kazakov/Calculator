/**
 * @author   Казаков Андрей
 * @date     06.08.17.
 */

#ifndef CALCULATOR_BINARYEXPRESSION_H
#define CALCULATOR_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression
{
	public:
		BinaryExpression(char, Expression*, Expression*);

		~BinaryExpression() override;

		float eval() override;

		void print(std::ostream& os) const override;

	private:
		Expression* expr1, * expr2;
		char operation;
};

#endif //CALCULATOR_BINARYEXPRESSION_H
