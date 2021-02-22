#include <lexer.hpp>
#include <parser.hpp>
#include <iostream>
#include <vector>

using namespace calc;

static std::ostream& operator<<(std::ostream& os, const parser<std::vector, std::vector>::data_type& data)
{
	auto it = data.begin();
	while(it != data.end())
	{
		os << (*it)->eval();
		it++;
		if(it != data.end())
			os << ", ";
	}
	return os;
}

static inline int usage(std::string_view name)
{
	auto pos = name.find_first_of("\\");
	auto name1 = name.substr(pos);
	std::cout << "usage:\n" << name1 << " [expression] [expression]\n";
	return 0;
}

int main(int argc, const char** argv)
{
	if(argc < 2)
		return usage(argv[0]);

	lexer<std::vector> l;
	parser<std::vector, std::vector> p;

	//for(int i = 1; i < argc; ++i)
	{
		l.tokenize("2+3*4 (2+3)*4");

		p.parse(l.tokens());

		auto& parsed = p.expressions();
		std::cout << 0 << ". " << p << " = " << parsed << std::endl;
		l.clear();
		p.clear();
	}
}
