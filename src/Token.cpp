#include "Token.h"

std::ostream& operator<<(std::ostream& os, Token::Type type)
{
	switch(type)
	{
		case Token::Type::NUMBER: os << "NUMBER";
			break;
		case Token::Type::DIVISION: os << "DIVISION";
			break;
		case Token::Type::PLUS: os << "PLUS";
			break;
		case Token::Type::MINUS: os << "MINUS";
			break;
		case Token::Type::MULTIPLY: os << "MULTIPLY";
			break;
		case Token::Type::HEX_NUMBER: os << "HEX";
			break;
		case Token::Type::BIN_NUMBER: os << "BIN";
			break;
		case Token::Type::L_BRACKET: os << "LEFT_BRACKET";
			break;
		case Token::Type::R_BRACKET: os << "RIGHT_BRACKET";
			break;
		default: os << "unknown";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << "Token: " << token.type << "(" << token.data << ")";
	return os;
}

Token::Token() : data(), type(Token::Type::NONE) {}

Token::Token(Token::Type type) : type(type) {}

Token::Token(Token::Type type, const std::string& data) : type(type), data(data) {}

Token::Token(Token::Type type, std::string&& data) : type(type), data(std::move(data)) {}
