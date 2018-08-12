#include "NumberExpression.h"

NumberExpression::NumberExpression(float value) : value(value) {}

float NumberExpression::eval() { return value; }

void NumberExpression::print(std::ostream& os) const { os << value; }
