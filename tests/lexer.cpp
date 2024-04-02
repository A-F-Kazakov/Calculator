#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include <lexer.hpp>
#include <vector>
#include <list>

using namespace std;

using calc::token;

TEST_CASE("Lexer can handle addition", "[lexer]")
{
	string input_expression{"2+2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 3);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "2");
	REQUIRE(tokens[1].type() == token::plus);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "2");

	BENCHMARK("parse") { return calc::tokenize<vector>(input_expression); };
}

TEST_CASE("Lexer can handle substraction", "[lexer]")
{
	string input_expression{"22-2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 3);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "22");
	REQUIRE(tokens[1].type() == token::minus);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "2");
}

TEST_CASE("Lexer can handle multiplications", "[lexer]")
{
	string input_expression{"22*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 3);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "22");
	REQUIRE(tokens[1].type() == token::multiply);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "2");
}

TEST_CASE("Lexer can handle division", "[lexer]")
{
	string input_expression{"10/2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 3);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "10");
	REQUIRE(tokens[1].type() == token::division);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "2");
}

TEST_CASE("Lexer can handle factorial", "[lexer]")
{
	string input_expression{"5!"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 2);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "5");
	REQUIRE(tokens[1].type() == token::factorial);
}

TEST_CASE("Lexer can handle complex expressions", "[lexer]")
{
	string input_expression{"2+2*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 5);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "2");
	REQUIRE(tokens[1].type() == token::plus);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "2");
	REQUIRE(tokens[3].type() == token::multiply);
	REQUIRE(tokens[4].type() == token::number);
	REQUIRE(tokens[4].data() == "2");
}

TEST_CASE("Lexer can handle bracket expressions", "[lexer]")
{
	string input_expression{"(2+2)*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 7);
	REQUIRE(tokens[0].type() == token::l_bracket);
	REQUIRE(tokens[1].type() == token::number);
	REQUIRE(tokens[1].data() == "2");
	REQUIRE(tokens[2].type() == token::plus);
	REQUIRE(tokens[3].type() == token::number);
	REQUIRE(tokens[3].data() == "2");
	REQUIRE(tokens[4].type() == token::r_bracket);
	REQUIRE(tokens[5].type() == token::multiply);
	REQUIRE(tokens[6].type() == token::number);
	REQUIRE(tokens[6].data() == "2");
}

TEST_CASE("Lexer can handle complex expressions 3", "[lexer]")
{
	string input_expression{"(2+2)/4"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 7);
	REQUIRE(tokens[0].type() == token::l_bracket);
	REQUIRE(tokens[1].type() == token::number);
	REQUIRE(tokens[1].data() == "2");
	REQUIRE(tokens[2].type() == token::plus);
	REQUIRE(tokens[3].type() == token::number);
	REQUIRE(tokens[3].data() == "2");
	REQUIRE(tokens[4].type() == token::r_bracket);
	REQUIRE(tokens[5].type() == token::division);
	REQUIRE(tokens[6].type() == token::number);
	REQUIRE(tokens[6].data() == "4");
}

TEST_CASE("Lexer can handle complex expressions 4", "[lexer]")
{
	string input_expression{"(2+2)/(4+12)"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 11);
	REQUIRE(tokens[0].type() == token::l_bracket);
	REQUIRE(tokens[1].type() == token::number);
	REQUIRE(tokens[1].data() == "2");
	REQUIRE(tokens[2].type() == token::plus);
	REQUIRE(tokens[3].type() == token::number);
	REQUIRE(tokens[3].data() == "2");
	REQUIRE(tokens[4].type() == token::r_bracket);
	REQUIRE(tokens[5].type() == token::division);
	REQUIRE(tokens[6].type() == token::l_bracket);
	REQUIRE(tokens[7].type() == token::number);
	REQUIRE(tokens[7].data() == "4");
	REQUIRE(tokens[8].type() == token::plus);
	REQUIRE(tokens[9].type() == token::number);
	REQUIRE(tokens[9].data() == "12");
	REQUIRE(tokens[10].type() == token::r_bracket);
}

TEST_CASE("Lexer can handle complex expressions 5", "[lexer]")
{
	string input_expression{"((3+2)-(1+2))!"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 14);
	REQUIRE(tokens[0].type() == token::l_bracket);
	REQUIRE(tokens[1].type() == token::l_bracket);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "3");
	REQUIRE(tokens[3].type() == token::plus);
	REQUIRE(tokens[4].type() == token::number);
	REQUIRE(tokens[4].data() == "2");
	REQUIRE(tokens[5].type() == token::r_bracket);
	REQUIRE(tokens[6].type() == token::minus);
	REQUIRE(tokens[7].type() == token::l_bracket);
	REQUIRE(tokens[8].type() == token::number);
	REQUIRE(tokens[8].data() == "1");
	REQUIRE(tokens[9].type() == token::plus);
	REQUIRE(tokens[10].type() == token::number);
	REQUIRE(tokens[10].data() == "2");
	REQUIRE(tokens[11].type() == token::r_bracket);
	REQUIRE(tokens[12].type() == token::r_bracket);
	REQUIRE(tokens[13].type() == token::factorial);
}

TEST_CASE("Lexer can handle multiple expressions", "[lexer]")
{
	string input_expression{"2+2*2 (2+2)*2"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 12);
	REQUIRE(tokens[0].type() == token::number);
	REQUIRE(tokens[0].data() == "2");
	REQUIRE(tokens[1].type() == token::plus);
	REQUIRE(tokens[2].type() == token::number);
	REQUIRE(tokens[2].data() == "2");
	REQUIRE(tokens[3].type() == token::multiply);
	REQUIRE(tokens[4].type() == token::number);
	REQUIRE(tokens[4].data() == "2");

	REQUIRE(tokens[5].type() == token::l_bracket);
	REQUIRE(tokens[6].type() == token::number);
	REQUIRE(tokens[6].data() == "2");
	REQUIRE(tokens[7].type() == token::plus);
	REQUIRE(tokens[8].type() == token::number);
	REQUIRE(tokens[8].data() == "2");
	REQUIRE(tokens[9].type() == token::r_bracket);
	REQUIRE(tokens[10].type() == token::multiply);
	REQUIRE(tokens[11].type() == token::number);
	REQUIRE(tokens[11].data() == "2");
}

TEST_CASE("Lexer can handle different containers", "[lexer]")
{
	string input_expression{"4*4"};

	auto tokens = calc::tokenize<list>(input_expression);

	REQUIRE(tokens.size() == 3);
	auto it = tokens.begin();
	REQUIRE(it->type() == token::number);
	REQUIRE(it->data() == "4");
	REQUIRE((++it)->type() == token::multiply);
	REQUIRE((++it)->type() == token::number);
	REQUIRE(it->data() == "4");
}

TEST_CASE("Lexer can handle incorrect expression", "[lexer]")
{
	string input_expression{"(4*4"};

	auto tokens = calc::tokenize<vector>(input_expression);

	REQUIRE(tokens.size() == 4);
	REQUIRE(tokens[0].type() == token::l_bracket);
	REQUIRE(tokens[1].type() == token::number);
	REQUIRE(tokens[1].data() == "4");
	REQUIRE(tokens[2].type() == token::multiply);
	REQUIRE(tokens[3].type() == token::number);
	REQUIRE(tokens[3].data() == "4");
}
