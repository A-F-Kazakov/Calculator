#include <lexer.hpp>
#include <parser.hpp>
#include <iostream>
#include <vector>

using namespace calc;

int usage(const char* name)
{
	std::cout << "usage:\n" << name << " [expression] [expression]\n";
	return 0;
}

int main(int argc, const char** argv)
{
	if(argc < 2)
		return usage(argv[0]);

	for(int i = 1; i < argc; ++i)
	{
		lexer<std::vector> l;
		l.tokenize(argv[i]);

		parser<std::vector, std::vector> p(l.tokens());
		p.parse();

		auto& parsed = p.expressions();
		std::cout << i << ". " << p << " = " << parsed[0]->eval() << std::endl;
	}
}
