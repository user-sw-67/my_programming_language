#include "../../include/lexer/token.hpp"


Token::Token(const TokenType& type, const SourceLocation& location, 
    const std::string& value) : 
        type(type), value(value), location(location) {}

std::string Token::to_string() const {
    return token_to_string(type, value) + " " + location.file_path + ":" +
        std::to_string(location.line) + ":" + std::to_string(location.column);
}

size_t Token::get_line() const {return location.line;}

size_t Token::get_column() const {return location.column;}

std::string Token::get_file() const {return location.file_path;}

TokenType Token::get_type() const {return type;}

std::string Token::get_value() const {return value;}