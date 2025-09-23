#include "token_stream.hpp"

namespace Chlorine::Lexer {
	TokenStream::TokenStream(std::string source) : source(source) {}

	Token TokenStream::NextToken() { // NOT IMPLEMENTED
		return Token(TokenType::END_OF_FILE, "", -1, -1);
	}

	char TokenStream::Peek() {
		if (pos >= source.size()) {
			return '\0';
		}
		return source[pos];
	}

	char TokenStream::Consume() {
		if (pos >= source.size()) {
			return '\0';
		}
		char current = source[pos++];
		if (current == '\n') {
			line++;
			column = 1;
		} else {
			column++;
		}
		return current;
	}
}