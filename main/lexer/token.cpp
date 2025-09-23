#include "token.hpp"

namespace Chlorine::Lexer {
	Token::Token(TokenType type, std::string lexeme, uint64_t line, uint64_t column) : type(type), lexeme(lexeme), line(line), column(column) {}
}