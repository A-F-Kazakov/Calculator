#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <parser.hpp>
#include <vector>

using std::vector;

static calc::lexer<vector> lexer;
static calc::parser<vector, vector> parser;

TEST_CASE("Parser can handle addition", "[parser]")
{
	std::string input_expression = "2+2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 4.0);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle substraction", "[parser]")
{
	std::string input_expression = "22-2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 20.0);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle multiplications", "[parser]")
{
	std::string input_expression = "22*2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 44.0);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle division", "[parser]")
{
	std::string input_expression = "10/2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 5.0);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle factorial", "[parser]")
{
	std::string input_expression = "5!";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 120);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle complex expressions", "[parser]")
{
	std::string input_expression = "2+2*2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 6);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle complex expressions 2", "[parser]")
{
	std::string input_expression = "(2+2)*2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 8);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle complex expressions 3", "[parser]")
{
	std::string input_expression = "(2+2)/4";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 1);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle complex expressions 4", "[parser]")
{
	std::string input_expression = "(2+2)/(4+12)";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 1 / 4);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle complex expressions 5", "[parser]")
{
	std::string input_expression = "((3+2)-(1+2))!";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 2);

	lexer.clear();
	parser.clear();
}

TEST_CASE("Parser can handle multiple expressions", "[parser]")
{
	std::string input_expression = "2 + 2*2 (2+2) * 2";

	lexer.tokenize(input_expression);

	parser.parse(lexer.tokens());
	const auto& out_expression = parser.expressions();

	REQUIRE(out_expression[0]->eval() == 8);
	REQUIRE(out_expression[1]->eval() == 6);

	lexer.clear();
	parser.clear();
}

