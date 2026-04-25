#ifndef TOKEN
#define TOKEN

#include <string>
#include <vector>
#include <memory>
#include <type_traits>


class Token{
    TokenType type;
    std::string value;
    size_t line;
    size_t column;
    
public:
    Token(
        const TokenType& type, 
        size_t line = 1, 
        size_t column = 1, 
        const std::string& value = std::string("undefined")) : 
            type(type), value(value), 
            line(line), column(column) {}

    std::string to_string() const {
        return token_to_string(type, value) + " " + 
            std::to_string(line) + ":" + std::to_string(column);
    }

    size_t get_line() const {return line;}
    size_t get_column() const {return column;}
    TokenType get_type() const {return type;}
    std::string get_value() const {return value;}
    
};

#endif