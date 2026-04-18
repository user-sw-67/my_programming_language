#ifndef TOKEN
#define TOKEN

#include <string>
#include <vector>
#include <memory>
#include <type_traits>


template<typename T>
struct is_enum_class{
    static const bool value = 
        std::is_enum_v<T> && !std::is_convertible_v<T, int>;
};

template<typename T>
constexpr bool is_enum_class_v = is_enum_class<T>::value;


class TokenBase{
public:
    virtual ~TokenBase() = default;

    virtual std::string to_string() const = 0;
};

template<typename TokenType, 
    std::enable_if_t<is_enum_class_v<TokenType>, int> = 0>
class Token : public TokenBase {
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

    std::pair<TokenType, std::string> get_data() const {
        return std::pair<TokenType, std::string>(type, value);
    }

    std::pair<size_t, size_t> get_coord() const {
        return std::pair<size_t, size_t>(line, column);
    }

    std::string to_string() const override {
        return token_to_string(type, value) + " " + 
            std::to_string(line) + ":" + std::to_string(column);
    }
};

#endif