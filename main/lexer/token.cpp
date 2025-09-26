#include "token.hpp"

namespace Chlorine::Lexer {
	Token::Token(TokenType type, std::string lexeme, uint64_t line, uint64_t column) : type(type), lexeme(lexeme), line(line), column(column) {}

	std::string Token::ToString() const {
		return "Token(" + tokenTypeToString[this->type] + ", " + this->lexeme + ", (" + std::to_string(this->line) + ", " + std::to_string(this->column) + "))";
	}
}