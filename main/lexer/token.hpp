#pragma once

#include <cstdint>
#include <string>

#include "token_type.hpp"

namespace Chlorine::Lexer {
	class Token {
	public:
		TokenType type;
		std::string lexeme;
		uint64_t line;
		uint64_t column;

		Token(TokenType type, std::string lexeme, uint64_t line, uint64_t column);

		std::string ToString() const;
	};
}