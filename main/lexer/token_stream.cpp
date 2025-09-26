#include "token_stream.hpp"

#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace Chlorine::Lexer {
	std::vector<std::string> keywords = {
		"abstract", "bool", "break", "case", "char", "class", "continue", "default", "else", "f32", "f64", "false", "for", "function", "i8", "i16", "i32", "i64", "if", "import", "null", "private", "public", "return", "self", "string", "switch", "true", "u8", "u16", "u32", "u64", "void", "while", 
	};

	std::vector<std::string> operators = {
		"+", "-", "*", "/", "%", "+=", "-=", "*=", "/=", "%=", "++", "--"
		"&", "|", "^", "~", "<<", ">>", "&=", "|=", "^=", "<<=", ">>=",
		"&&", "||", "!", "<", ">", "<=", ">=", "==", "!=",
		",", ".", ":", "=", "->"
	};

	TokenStream::TokenStream(std::string source) : source(source) {}

	Token TokenStream::NextToken() {
		if (this->Peek() == '\0') {
			return Token(TokenType::END_OF_FILE, "\0", line, column);
		}

		if (std::isspace(this->Peek())) {
			this->Consume();
			return this->NextToken();
		}

		if (this->Peek() == '/' && this->Peek(1) == '/') {
			this->Consume(2);
			while (true) {
				char c = this->Consume();

				if (c == '\n' || c == '\0') break;
			}
			return this->NextToken();
		}

		if (std::isdigit(this->Peek())) {
			return this->LiteralNum();
		}

		switch (this->Peek()) {
		case '"':
			return this->LiteralString();
		case '\'':
			return this->LiteralChar();
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
			return this->Parenthesis();
		}

		if (std::isalpha(this->Peek()) || this->Peek() == '_') {
			return this->Identifier();
		}

		std::string bestMatch;
		
		for (auto &op : operators) {
			bool match = true;
			for (size_t i = 0; i < op.size(); i++) {
				if (this->Peek(i) != op[i]) {
					match = false;
					break;
				}
			}
			if (match && op.size() > bestMatch.size()) {
				bestMatch = op;
			}
		}

		if (!bestMatch.empty()) {
			Token token = Token(TokenType::OPERATOR, "", this->line, this->column);
			for (size_t i = 0; i < bestMatch.size(); i++) {
				token.lexeme += this->Consume();
			}
			return token;
		}

		throw std::runtime_error(std::string("Unrecognized character: \"") + this->Consume() + "\" at (" + std::to_string(this->line) + ":" + std::to_string(this->column) + ")");
	}

	std::vector<Token> TokenStream::GetAll() {
		std::vector<Token> tokens;

		while (true) {
			Token token = this->NextToken();
			tokens.push_back(token);
			if (token.type == TokenType::END_OF_FILE) {
				break;
			}
		}

		return tokens;
	}

	bool TokenStream::IsKeyword(std::string identifier) {
		return std::count(keywords.begin(), keywords.end(), identifier);
	}

	TokenStream& TokenStream::operator>>(Token& dest) {
		dest = this->NextToken();
		return *this;
	}

	char TokenStream::Peek(int64_t lookahead) const {
		if (this->pos + lookahead >= source.size()) {
			return '\0';
		}
		return this->source[this->pos + lookahead];
	}

	char TokenStream::Consume(uint64_t count) {
		char current;
		for (uint64_t i = 0; i < count; i++) {
			if (this->pos >= this->source.size()) {
				return '\0';
			}
			current = this->source[this->pos++];
			if (current == '\n') {
				this->line++;
				this->column = 1;
			} else {
				this->column++;
			}
		}
		return current;
	}

	Token TokenStream::LiteralChar() {
		Token token = Token(TokenType::LITERAL_CHAR, "", this->line, this->column);
		token.lexeme += this->Consume();
		while (this->Peek() != '\0' && (this->Peek() != '\'' || this->Peek(-1) == '\\')) {
			token.lexeme += this->Consume();
		}
		token.lexeme += this->Consume();
		return token;
	}

	Token TokenStream::LiteralString() {
		Token token = Token(TokenType::LITERAL_STRING, "", this->line, this->column);
		token.lexeme += this->Consume();
		while (this->Peek() != '\0' && (this->Peek() != '"' || this->Peek(-1) == '\\')) {
			token.lexeme += this->Consume();
		}
		token.lexeme += this->Consume();
		return token;
	}

	Token TokenStream::LiteralNum() {
		Token token = Token(TokenType::LITERAL_INT, "", this->line, this->column);
		token.lexeme += this->Consume();

		while (std::isdigit(this->Peek()) || this->Peek() == '.') {
			if (this->Peek() == '.') {
				if (token.type == TokenType::LITERAL_FLOAT) {
					throw std::runtime_error("Too many decimal points in float literal.");
				}
				token.type = TokenType::LITERAL_FLOAT;
			}

			token.lexeme += this->Consume();
		}

		return token;
	}

	Token TokenStream::Parenthesis() {
		return Token(TokenType::PARENTHESIS, std::string(1, this->Consume()), this->line, this->column);
	}

	Token TokenStream::Identifier() {
		Token token = Token(TokenType::IDENTIFIER, "", this->line, this->column);
		token.lexeme += this->Consume();

		while (std::isalnum(this->Peek()) || this->Peek() == '_') {
			token.lexeme += this->Consume();
		}

		if (this->IsKeyword(token.lexeme)) {
			token.type = TokenType::KEYWORD;
		}

		return token;
	}
}