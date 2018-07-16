/**
 * author   k 
 * date     06.08.17.
 */

#include <Parser.h>

const Token Parser::end(TokenType::NONE);

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentPosition(0), length(tokens.size()){}

Parser::~Parser()
{
	for(std::vector<Expression*>::iterator it = result.begin() ; it != result.end(); ++it)
		delete(*it);
	result.clear();
}

std::vector<Expression*> Parser::parse()
{
	while(!match(TokenType::NONE))
		result.push_back(expression());

	return result;
}

Expression* Parser::expression()
{
	return additive();
}

Expression* Parser::additive()
{
	Expression* result = multiplicative();

	while(true)
	{
		if(match(TokenType::PLUS))
		{
			result = new BinaryExpression('+', result, multiplicative());
			continue;
		}
		if(match(TokenType::MINUS))
		{
			result = new BinaryExpression('-', result, multiplicative());
			continue;
		}
		break;
	}

	return result;
}

Expression* Parser::multiplicative()
{
	Expression* res = unary();

	while(true)
	{
		// 2 * 6 / 3
		if(match(TokenType::MULTIPLY))
		{
			res = new BinaryExpression('*', res, unary());
			continue;
		}
		if(match(TokenType::DIVISION))
		{
			res = new BinaryExpression('/', res, unary());
			continue;
		}
		break;
	}

	return res;
}

Expression* Parser::unary()
{
	if(match(TokenType::MINUS))
		return new UnaryExpression('-', primary());
	return primary();
}

Expression* Parser::primary()
{
	const Token& current = get();

	if(match(TokenType::NUMBER))
		return new NumberExpression(atof(current.getData().c_str()));

	if(match(TokenType::HEX_NUMBER))
		return new NumberExpression(std::stoul(current.getData(), nullptr, 16));

	if(match(TokenType::BIN_NUMBER))
	{
		std::string tmp = current.getData();
		tmp.erase(0,2);
		return new NumberExpression(std::stoi(tmp, nullptr, 2));
	}

	if(match(TokenType::L_BRACKET))
	{
		Expression* result = expression();
		match(TokenType::R_BRACKET);
		return result;
	}

	throw std::runtime_error("unsupported expression");
}

const Token& Parser::get(size_t relativePosition)
{
	size_t position = currentPosition + relativePosition;
	if(position >= length)
		return Parser::end;

	return tokens.at(position);
}

bool Parser::match(TokenType type)
{
	const Token& current  = get();
	if(current.getType() != type)
		return  false;
	++currentPosition;

	return true;
}

std::ostream& operator<<(std::ostream& os, const Parser& parser)
{
	for(auto&& it : parser.result)
		it->print(os);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Expression& data)
{
	data.print(os);
	return os;
}
