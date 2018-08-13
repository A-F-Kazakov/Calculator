/**
 * @author   Казаков Андрей
 * @date     13.08.18.
 */

#ifndef CALCULATOR_HEXEXPRESSION_H
#define CALCULATOR_HEXEXPRESSION_H

#include "NumberExpression.h"

class HexNumberExpression : public NumberExpression
{
	public:
		explicit HexNumberExpression(float val) : NumberExpression(val){}

		void print(std::ostream& os) const override
		{
			os << std::hex << static_cast<int>(NumberExpression::eval());
		}
};

#endif //CALCULATOR_HEXEXPRESSION_H
