//
// Created by k on 28.07.17.
//

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H

#include <string>
#include <ostream>

enum class TokenType
{
	NONE,
	NUMBER,
	HEX_NUMBER,
	BIN_NUMBER,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVISION,
	L_BRACKET,
	R_BRACKET
};

class Token
{
	public:
		Token();
		Token(TokenType);
		Token(TokenType, const std::string&);

		friend std::ostream& operator<<(std::ostream&, const Token&);

		const std::string& getData() const;
		void setData(const std::string&);
		TokenType getType() const;
		void setType(TokenType);

	private:
		std::string data;
		TokenType type;
};

#endif //CALCULATOR_TOKEN_H
