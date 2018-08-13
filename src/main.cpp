#include <vector>
#include <iostream>

#include "Lexer.h"
#include "Parser.h"

void printHelp(const char* name)
{
	std::cout << "usage:\n" << name << " [expression] [expression]\n";
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		printHelp(argv[0]);
		return 1;
	}

	for(int i = 1; i < argc; ++i)
	{
		Lexer<std::vector> l;
		l.tokenize(argv[i]);

		Parser<std::vector, std::vector> p(l.getTokens());

		p.parse();

		auto parsed = p.getExpression();

	  std::cout << i << ". " << p  << " = " << parsed[0]->eval() << std::endl;
	}
}