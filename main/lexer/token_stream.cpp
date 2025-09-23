#include "token_stream.hpp"

namespace Chlorine::Lexer {
	TokenStream::TokenStream(std::string source) : source(source) {}

	Token TokenStream::NextToken() { // NOT IMPLEMENTED
		return Token(TokenType::END_OF_FILE, "", -1, -1);
	}
}