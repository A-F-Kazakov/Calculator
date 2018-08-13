/**
 * @author   Казаков Андрей
 * @date     13.08.18.
 */

#ifndef CALCULATOR_BINNUMBEREXPRESSION_H
#define CALCULATOR_BINNUMBEREXPRESSION_H

#include <bitset>

#include "NumberExpression.h"

class BinNumberExpression : public NumberExpression
{
	public:
		explicit BinNumberExpression(float val) : NumberExpression(val){}

		void print(std::ostream& os) const override
		{
			os << std::bitset<16>(static_cast<uint64_t>(NumberExpression::eval()));
		}
};

#endif //CALCULATOR_BINNUMBEREXPRESSION_H
