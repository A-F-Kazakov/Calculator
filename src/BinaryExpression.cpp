/**
 * author   k 
 * date     06.08.17.
 */

#include <BinaryExpression.h>

BinaryExpression::BinaryExpression(char operation, Expression* expr1, Expression* expr2) :
		operation(operation), expr1(expr1), expr2(expr2){}

float BinaryExpression::eval()
{
	switch(operation)
	{
		case '+':
			return expr1->eval() + expr2->eval();
		case '-':
			return expr1->eval() - expr2->eval();
		case '*':
			return expr1->eval() * expr2->eval();
		case '/':
			return expr1->eval() / expr2->eval();
	}
	return 0;
}

BinaryExpression::~BinaryExpression()
{
	delete(expr1);
	delete(expr2);
}

void BinaryExpression::print(std::ostream& os) const
{
	os << *expr1 << " " << operation << " " << *expr2;

}
