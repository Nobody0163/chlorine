#pragma once

#include <unordered_map>
#include <string>

namespace Chlorine::Lexer {
	enum class TokenType {
		LITERAL_INT,
		LITERAL_FLOAT,
		LITERAL_STRING,
		LITERAL_CHAR,
		KEYWORD,
		IDENTIFIER,
		OPERATOR,
		PARENTHESIS,
		END_OF_FILE
	};

	extern std::unordered_map<TokenType, std::string> tokenTypeToString;
}