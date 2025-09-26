#include "token_type.hpp"

namespace Chlorine::Lexer {
	std::unordered_map<TokenType, std::string> tokenTypeToString = {
		{TokenType::LITERAL_INT, "LITERAL_INT"},
		{TokenType::LITERAL_FLOAT, "LITERAL_FLOAT"},
		{TokenType::LITERAL_STRING, "LITERAL_STRING"},
		{TokenType::LITERAL_CHAR, "LITERAL_CHAR"},
		{TokenType::KEYWORD, "KEYWORD"},
		{TokenType::IDENTIFIER, "IDENTIFIER"},
		{TokenType::OPERATOR, "OPERATOR"},
		{TokenType::PARENTHESIS, "PARENTHESIS"},
		{TokenType::END_OF_FILE, "END_OF_FILE"}
	};
}