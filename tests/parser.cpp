#include <catch2/catch_test_macros.hpp>
#include <lexer.hpp>
#include <parser.hpp>
#include <vector>
#include <vector>

using namespace std;

using calc::token;

TEST_CASE("Parser can handle addition", "[parser]")
{
	string input_expression{"3+3"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 6.0);
}

TEST_CASE("Parser can handle substraction", "[parser]")
{
	string input_expression{"42-2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 40.0);
}

TEST_CASE("Parser can handle multiplications", "[parser]")
{
	string input_expression{"33*7"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 231.0);
}

TEST_CASE("Parser can handle division", "[parser]")
{
	string input_expression{"13/2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 6.5);
}

TEST_CASE("Parser can handle factorial", "[parser]")
{
	string input_expression{"6!"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 720.0);
}

TEST_CASE("Parser can handle complex expressions", "[parser]")
{
	string input_expression{"2+2*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 6.0);
}

TEST_CASE("Parser can handle complex expressions 2", "[parser]")
{
	string input_expression{"(2+2)*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 8.0);
}

TEST_CASE("Parser can handle complex expressions 3", "[parser]")
{
	string input_expression{"(2+2)/4"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 1.0);
}

TEST_CASE("Parser can handle complex expressions 4", "[parser]")
{
	string input_expression{"(2+2)/(4+12)"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 0.25);
}

TEST_CASE("Parser can handle complex expressions 5", "[parser]")
{
	string input_expression{"((3+2)-(1+2))!"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 2.0);
}

TEST_CASE("Parser can handle multiple expressions", "[parser]")
{
	string input_expression{"2+2*2 (2+2)*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 2);
	REQUIRE(expressions[0]->eval() == 6.0);
	REQUIRE(expressions[1]->eval() == 8.0);
}

TEST_CASE("Parser can handle incomplete expression", "[parser]")
{
	string input_expression{"(2+2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	auto expressions = calc::parse<vector>(tokens);

	REQUIRE(expressions.size() == 1);
	REQUIRE(expressions[0]->eval() == 4);
}

TEST_CASE("Parser can handle incomplete expression 2", "[parser]")
{
	string input_expression{"2+2)"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE_THROWS_AS(calc::parse<vector>(tokens), std::runtime_error);
}

TEST_CASE("Parser can handle incomplete expression 3", "[parser]")
{
	string input_expression{"2(+2)"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE_THROWS_AS(calc::parse<vector>(tokens), std::runtime_error);
}
