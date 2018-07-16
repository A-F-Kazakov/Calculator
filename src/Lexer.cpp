//
// Created by k on 28.07.17.
//

#include <Lexer.h>

std::string Lexer::OPERATOR_CHARS = "+-*/()";
TokenType Lexer::OPERATOR_TYPES[] = {
		TokenType::PLUS,
		TokenType::MINUS,
		TokenType::MULTIPLY,
		TokenType::DIVISION,
		TokenType::L_BRACKET,
		TokenType::R_BRACKET
};

//void Lexer::tokenize(std::string& str)
//{
//	Token tmp;
//	for(auto&& item : str)
//	{
//		if(item >= '0' && item <= '9')
//		{
//			if(tmp.type != TokenType::NUMBER && tmp.type != TokenType::NONE)
//			{
//				tokens.push_back(tmp);
//				tmp.data = "";
//			}
//			tmp.type = TokenType::NUMBER;
//			tmp.data.push_back(item);
////			std::cout << "num: ";
//			continue;
//		}
//		else
//			if(item == '(')
//			{}
//			else
//				if(item == ')')
//				{}
//				else
//					if(item == '*')
//					{}
//					else
//						if(item == '+')
//						{
//							if(tmp.type != TokenType::OPERATOR && tmp.type != TokenType::NONE)
//							{
//								tokens.push_back(tmp);
//								tmp.data = "";
//							}
//							tmp.type = TokenType::OPERATOR;
//							tmp.data = '+';
////							std::cout << "plus: ";
//							continue;
//						}
//						else
//							if(item == '-')
//							{
//								if(tmp.type != TokenType::OPERATOR && tmp.type != TokenType::NONE)
//								{
//									tokens.push_back(tmp);
//									tmp.data = "";
//								}
//								tmp.type = TokenType::OPERATOR;
//								tmp.data = '-';
////							std::cout << "plus: ";
//								continue;
//							}
//							else
//								if(item == '/')
//								{}
//								else
//									if(item == ',' || item == '.')
//									{}
//									else
//										if(item == ' ' || item == '\n' || item == '\t')
//										{
//											std::cout << "none usefull" << std::endl;
//											continue;
//										}
//
////		std::cout << item << std::endl;
//	}
//	tokens.push_back(tmp);
//}

std::ostream& operator<<(std::ostream& os, const Lexer& parser)
{
	for(auto&& item : parser.tokens)
		os << item << std::endl;
	return os;
}

Lexer::Lexer(const std::string& input) : input(input), lenght(input.length()), currentPosition(0){}

void Lexer::tokenize()
{
	char item;
	while(currentPosition < lenght)
	{
		item = peek();
		if(item >= '0' && item <= '9')
		{
			if(item == '0')
			{
				char next = peek(1);
				if(next == 'x' || next == 'X')
				{
					tokenizeHex();
					continue;
				}
				else
					if(next == 'b' || next == 'B')
					{
						tokenizeBin();
						continue;
					}
			}
			tokenizeNumber();
		}
		else
		{
			size_t index = OPERATOR_CHARS.find(item);
			if(index != std::string::npos)
				tokenizeOperator(index);
			else
				next();
		}
	}
}

char Lexer::peek(size_t relativePosition)
{
	const size_t position = currentPosition + relativePosition;
	if(position >= lenght)
		return '\0';
	return input.at(position);
}

char Lexer::next()
{
	++currentPosition;
	return peek();
}

void Lexer::tokenizeNumber()
{
	std::stringstream ss;
	char c = peek();
	while((c >= '0' && c <= '9') || c == '.' || c == ',')
	{
		if(c == ',')
			c = '.';
		ss << c;
		c = next();
	}

	tokens.push_back({TokenType::NUMBER, ss.str()});
}

void Lexer::tokenizeOperator(size_t index)
{
	next();
	tokens.push_back({OPERATOR_TYPES[index]});
}

const std::vector<Token>& Lexer::getTokens() const
{
	return tokens;
}

void Lexer::tokenizeHex()
{
	std::stringstream ss;
	char c = peek();
	while((c >= '0' && c <= '9') || c == 'x' || c == 'X' || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
	{
		ss << c;
		c = next();
	}

	tokens.push_back({TokenType::HEX_NUMBER, ss.str()});
}

void Lexer::tokenizeBin()
{
	std::stringstream ss;
	char c = peek();
	while(c == '0' || c == '1' || c == 'B' || c == 'b')
	{
		ss << c;
		c = next();
	}

	tokens.push_back({TokenType::BIN_NUMBER, ss.str()});
}
