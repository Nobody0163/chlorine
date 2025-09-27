#pragma once

#include <vector>

#include "token.hpp"

namespace Chlorine::Lexer {
	extern std::vector<std::string> keywords;
	extern std::vector<std::string> operators;

	class TokenStream {
	public:
		std::string source;

		TokenStream(std::string source);

		Token NextToken();
		std::vector<Token> GetAll();
		bool IsKeyword(std::string identifier);

		TokenStream& operator>>(Token& dest);
	private:
		uint64_t pos = 0;
		uint64_t line = 1;
		uint64_t column = 1;

		[[nodiscard]] char Peek(int64_t lookahead = 0) const;
		char Consume(uint64_t count = 1);
		Token LiteralChar();
		Token LiteralString();
		Token LiteralNum();
		Token Parenthesis();
		Token Identifier();
	};
}