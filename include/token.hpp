#ifndef TOKEN
#define TOKEN

#include <string>
#include <vector>
#include <memory>
#include <type_traits>


namespace token{
    namespace systems{
        enum class SPECIAL{
            // Специальные
            TOKEN_END_FILE,   // конец файла
            TOKEN_UNKNOWN,    // неизвестный токен 
            TOKEN_IDENTIFIER, // имена переменных 
        };

        enum class FUNCTION{
            // Функции
            PRINT, // std::cout 
            TYPE,  // python type(obj)
        };

        enum class KEYWORD{
            // Ключевые слова
            LET,    // let
            IF,     // if
            ELSE,   // else
            WHILE,  // while
            FOR,    // for
            FUNC,   // func
            RETURN, // return
        };

        enum class PUNCTUATION{
            // Пунктуация
            SEMICOLON, // ;
            COMMA,     // ,
            LPAREN,    // (
            RPAREN,    // )
            LBRACE,    // {
            RBRACE,    // }
            LBRACKET,  // [
            RBRACKET,  // ]
        };
    }

    namespace operators{
        enum class BINARY{
            // Бинарные операторы
            PLUS,     // +
            MINUS,    // -
            MULTIPLY, // *
            DIVIDE,   // /
            ASSIGN,   // =
        };

        enum class COMPARISON{
            // Операторы сравнения
            EQUAL,      // ==
            NOT_EQUAL,  // !=
            LESS,       // <
            GREATER,    // >
            LESS_EQ,    // <=
            GREATER_EQ, // >=
        };

        enum class UNARY{
            // Унарные операторы
            PLUS,      // +
            MINUS,     // -
            MULTIPLY,  // *
            AMPERSAND, // &
        };
    }

    namespace types{
        enum class CONTAINERS{
            ARRAY, // "std::vector"
        };

        enum class NUMBER{
            // Числовые
            INT,    // "int"
            DOUBLE, // "double"
        };

        enum class SYMBOLIC{
            // Символьные
            STR,  // "std::string"
            CHAR, // "char"
        };

        enum class SPECIAL{
            // Специальные
            NONE, // "void"
            BOOL, // "bool"
        };
    }

    namespace literals{
        enum class NUMBER{
            // Числовые
            INT,    // "int"
            DOUBLE, // "double"
        };

        enum class SYMBOLIC{
            // Символьные
            STR,  // "std::string"
            CHAR, // "char"
        };

        enum class SPECIAL{
            // Специальные
            NONE, // "void"
            BOOL, // "bool"
        };
    }

}


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
        const std::string& value = std::string(), 
        size_t line = 1, 
        size_t column = 1) : 
            type(type), value(value), 
            line(line), column(column) {}

    std::pair<TokenType, std::string> get_data() const {
        return std::pair<TokenType, std::string>(type, value);
    }

    std::pair<size_t, size_t> get_coord() const {
        return std::pair<size_t, size_t>(line, column);
    }

    std::string to_string() const override {
        return std::string("990");
    }

};


Token<token::systems::SPECIAL> end_file(size_t line = 1, size_t column = 1) {
    return Token<token::systems::SPECIAL>(
        token::systems::SPECIAL::TOKEN_END_FILE, std::string(), line, column);
}





#endif