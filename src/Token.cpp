//
// Created by k on 28.07.17.
//

#include <Token.h>

std::ostream& operator<<(std::ostream& os, const TokenType& type)
{
	switch(type)
	{
		case TokenType::NUMBER:
			os << "NUMBER";
			break;
		case TokenType::DIVISION:
			os << "DIVISION";
			break;
		case TokenType::PLUS:
			os << "PLUS";
			break;
		case TokenType::MINUS:
			os << "MINUS";
			break;
		case TokenType::MULTIPLY:
			os << "MULTIPLY";
			break;
		case TokenType::HEX_NUMBER:
			os << "HEX";
			break;
		case TokenType::BIN_NUMBER:
			os << "BIN";
			break;
		case TokenType::L_BRACKET:
			os << "LEFT_BRACKET";
			break;
		case TokenType::R_BRACKET:
			os << "RIGHT_BRACKET";
			break;
		default:
			os << "unknown";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << "Token: " << token.type << "(" << token.data << ")";
	return os;
}

Token::Token(){}

Token::Token(TokenType type) : type(type){}

Token::Token(TokenType type, const std::string& data) : type(type), data(data){}

const std::string& Token::getData() const
{
	return data;
}

void Token::setData(const std::string& data)
{
	Token::data = data;
}

TokenType Token::getType() const
{
	return type;
}

void Token::setType(TokenType type)
{
	Token::type = type;
}