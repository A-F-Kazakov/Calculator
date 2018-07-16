/**
 * author   k 
 * date     06.08.17.
 */

#ifndef CALCULATOR_EXPRESSION_H
#define CALCULATOR_EXPRESSION_H

class Expression
{
	public:
		virtual float eval() = 0;
		virtual void print(std::ostream& os) const = 0;
		virtual ~Expression(){};
		friend std::ostream& operator<<(std::ostream&, const Expression&);
};

#endif //CALCULATOR_EXPRESSION_H
