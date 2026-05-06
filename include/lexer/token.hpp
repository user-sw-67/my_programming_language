#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "token_list.hpp"
#include "../addition/source_manager.hpp"

class Token {
private:
    TokenType type;
    std::string value;
    SourceLocation location;
    
public:
    Token(const TokenType& type, const SourceLocation& location, 
        const std::string& value = std::string("undefined"));

    std::string to_string() const;

    size_t get_line() const;
    size_t get_column() const;
    TokenType get_type() const;
    std::string get_value() const;
    std::string get_file() const;
};

#endif