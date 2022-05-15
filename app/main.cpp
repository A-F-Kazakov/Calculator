#include <iostream>
#include <vector>

#include <lexer.hpp>
#include <parser.hpp>

using std::cout;

static inline int usage(std::string_view name)
{
	std::cout << "usage:\n" << name << " [expression] [expression]\n";
	return 0;
}

int main(int argc, const char** argv)
{
	if(argc < 2)
		return usage(argv[0]);

	size_t counter{};
	for(int i{1}; i < argc; ++i)
	{
		auto tokens = calc::tokenize<std::vector>(argv[i]);

		auto expressions = calc::parse<std::vector>(tokens);

		for(const auto& it : expressions)
		{
			cout << ++counter << ". ";
			it->print(std::cout);
			cout << " = " << it->eval() << '\n';
		}
	}
}
