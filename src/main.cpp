#include <vector>
#include <iostream>

#include "Lexer.h"
#include "Parser.h"

uint64_t factorial(uint_fast32_t n)
{
	uint64_t factorial = 1;

	for(int i = 1; i <= n; ++i)
		factorial *= i;

	return factorial;
}

uint64_t combination(uint32_t k, uint32_t n)
{
	uint64_t res = factorial(n) / factorial(k) * factorial(n - k);

	return res;
}


int main(int argc, char** argv)
{
	for(int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}

	int counter = 0;
	std::string expressions[] = {"234+222-44", "2+2*2", "2/5-10", /*"0xAB + 0x43",*/ "0b00010101 + 0b10101010",
										  "(2+2)*2"};

	std::cout << "CalculatorTest:" << std::endl;

	for(const std::string& expr : expressions)
	{
		std::cout << "\nTest № " << ++counter << std::endl;
		std::cout << "Expression: " << expr << std::endl;

		Lexer<std::vector> l;
		l.tokenize(expr);

//		std::cout << l << std::endl;
//		std::cout << "Parsing..." << std::endl;

		Parser<std::vector, std::vector> p(l.getTokens());

		auto parsed = p.parse();

		std::cout << p  << " = " << parsed[0]->eval() << std::endl;
	}

//	auto f = factorial(3);
//
//	std::cout << "fact 3: " << f << std::endl;
//
//	auto c = combination(5, 10);
//
//	std::cout << "combination of 5 from 10: " << c << std::endl;

	std::cout << "\nEnd of test" << std::endl;
}