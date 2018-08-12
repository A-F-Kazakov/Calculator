/**
 * @author   Казаков Андрей
 * @date     28.07.17.
 */

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H

#include <ostream>

class Token
{
	public:
		enum class Type
		{
				NONE,
				NUMBER,
				HEX_NUMBER,
				BIN_NUMBER,
				PLUS = '+',
				MINUS = '-',
				MULTIPLY = '*',
				DIVISION = '/',
				L_BRACKET = '(',
				R_BRACKET = ')'
		};

		Token();

		explicit Token(Type);

		Token(Type, const std::string&);

		Token(Type, std::string&&);

		friend std::ostream& operator<<(std::ostream&, const Token&);

		const std::string& getData() const { return data; }

		void setData(const std::string& data){ this->data = data; }
		void setData(std::string&& data){ this->data = std::move(data); }

		Type getType() const { return type; }

		void setType(Type type){ this->type = type; }

	private:
		std::string data;
		Type type;
};

#endif //CALCULATOR_TOKEN_H
