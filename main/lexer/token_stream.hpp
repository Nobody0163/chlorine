#pragma once

#include "token.hpp"

namespace Chlorine::Lexer {
	class TokenStream {
	public:
		std::string source;

		TokenStream(std::string source);

		Token NextToken();
	private:
		uint64_t pos = 0;
		uint64_t line = 1;
		uint64_t column = 1;

		[[nodiscard]] char Peek();
		char Consume();
	};
}