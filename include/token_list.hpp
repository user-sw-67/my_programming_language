#ifndef TOKEN_LIST
#define TOKEN_LIST

#include <string>
#include <type_traits>
#include <unordered_map>


namespace token_list{

    enum class Special{
        IDENTIFIER, // Идентификатор
        END_OF_FILE, // Конец файла
    };

    enum class SpecialWords{
        MAKE, // make
        CONST, // const
    };

    enum class Symbols{
        SEMICOLON, // ;
        COMMA, // ,
        DOT, // .
    };
    
    enum class Literals {
        INT, // 2
        DOUBLE, // 2.5
        STR, // "ecece"
        BOOL, // true
        NULL_VALUE, // null
    };

    enum class Brackets{
        PARENTHESIS_L, // (
        PARENTHESIS_R, // )
        BRACE_L, // {
        BRACE_R, // }
        BRACKET_L, // [
        BRACKET_R, // ]
    };

    namespace data_types{
        enum class Primitive{
            INT, // int
            DOUBLE, // double
            STR, // str
            BOOL, // bool
            NULL_VALUE, // null
        };
    }
    
    
    namespace built_functions{

        enum class StandardStreams{
            PRINT, // print()
            PRINTLN, // println()
            PRINTERR, // printerr()
            PRINTERRLN, // printerrln()
            INPUT // input()
        };
    }

    namespace operators{

        enum class Assignment{
            SIMPLE, // =
        };
        
    }
    

}


enum class StateList{
    START,
    ERROR,
    IN_NUMBER, // обычное число: 123
    IN_NUMBER_DOT, // прочитали точку: 123.
    IN_NUMBER_FRACTION, // дробная часть: 123.45
    IN_STRING, // обычная строка: "hello"
    IN_IDENTIFIER, // идентификатор: буквы, цифры, _
    IN_OPERATOR, // односимвольный: = + - * /
    IN_COMMENT_LINE, // # до конца строки
    IN_COMMENT_BLOCK, // /* ... */
};


inline std::string token_to_string(token_list::Brackets type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::Brackets::BRACE_L: 
                return "Brackets : BRACE_L : '" + value + "'";
            case token_list::Brackets::BRACE_R: 
                return "Brackets : BRACE_R : '" + value + "'";
            case token_list::Brackets::PARENTHESIS_L: 
                return "Brackets : PARENTHESIS_L : '" + value + "'";
            case token_list::Brackets::PARENTHESIS_R: 
                return "Brackets : PARENTHESIS_R : '" + value + "'";
            default: 
                return "Brackets : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::Literals type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::Literals::INT: 
                return "Literals : INT : '" + value + "'";
            case token_list::Literals::DOUBLE: 
                return "Literals : DOUBLE : '" + value + "'";
            case token_list::Literals::STR: 
                return "Literals : STR : '" + value + "'";
            case token_list::Literals::BOOL: 
                return "Literals : BOOL : '" + value + "'";
            case token_list::Literals::NULL_VALUE: 
                return "Literals : NULL : '" + value + "'";
            default: 
                return "Literals : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::Special type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::Special::IDENTIFIER: 
                return "Special : IDENTIFIER : '" + value + "'";
            case token_list::Special::END_OF_FILE: 
                return "Special : END_OF_FILE : '" + value + "'";
            default: 
                return "Special : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::SpecialWords type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::SpecialWords::MAKE: 
                return "SpecialWords : MAKE : '" + value + "'";
            case token_list::SpecialWords::CONST: 
                return "SpecialWords : CONST : '" + value + "'";
            default: 
                return "SpecialWords : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::Symbols type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::Symbols::SEMICOLON: 
                return "Symbols : SEMICOLON : '" + value + "'";
            case token_list::Symbols::COMMA: 
                return "Symbols : COMMA : '" + value + "'";
            default: 
                return "Symbols : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(
    token_list::built_functions::StandardStreams type, 
        const std::string& value = "undefined") {
            switch (type) {
                case token_list::built_functions::StandardStreams::PRINT: 
                    return "StandardStreams : PRINT : '" + value + "'";
                case token_list::built_functions::StandardStreams::PRINTLN: 
                    return "StandardStreams : PRINTLN : '" + value + "'";
                case token_list::built_functions::StandardStreams::PRINTERR: 
                    return "StandardStreams : PRINTERR : '" + value + "'";
                case token_list::built_functions::StandardStreams::PRINTERRLN: 
                    return "StandardStreams : PRINTERRLN : '" + value + "'";
                case token_list::built_functions::StandardStreams::INPUT: 
                    return "StandardStreams : INPUT : '" + value + "'";
                default: 
                    return "StandardStreams : Unknown : '" + value + "'";
            }
}

inline std::string token_to_string(token_list::data_types::Primitive type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::data_types::Primitive::INT: 
                return "Primitive : INT : '" + value + "'";
            case token_list::data_types::Primitive::DOUBLE:     
                return "Primitive : DOUBLE : '" + value + "'";
            case token_list::data_types::Primitive::STR: 
                return "Primitive : STR : '" + value + "'";
            case token_list::data_types::Primitive::BOOL: 
                return "Primitive : BOOL : '" + value + "'";
            case token_list::data_types::Primitive::NULL_VALUE: 
                return "Primitive : NULL : '" + value + "'";
            default: 
                return "Primitive : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::operators::Assignment type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::operators::Assignment::SIMPLE: 
                return "Assignment : SIMPLE : '" + value + "'";
            default: 
                return "Assignment : Unknown : '" + value + "'";
        }
}



static const std::unordered_map<std::string, std::pair<int, int>> 
    keyword_map = {
        // Специальные слова
        {"make", {0, static_cast<int>(token_list::SpecialWords::MAKE)}},
        {"const", {0, static_cast<int>(token_list::SpecialWords::CONST)}},
        
        // Литералы
        {"null", {1, static_cast<int>(token_list::Literals::NULL_VALUE)}},
        {"true", {1, static_cast<int>(token_list::Literals::BOOL)}},
        {"false", {1, static_cast<int>(token_list::Literals::BOOL)}},
        
        // Встроенные функции StandardStreams
        {"print", {2, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINT)}},
        {"println", {2, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINTLN)}},
        {"printerr", {2, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINTERR)}},
        {"printerrln", {2, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINTERRLN)}},
        {"input", {2, static_cast<int>(
            token_list::built_functions::StandardStreams::INPUT)}},
        
        // Типы данных
        {"int", {3, static_cast<int>(token_list::data_types::Primitive::INT)}},
        {"double", {3, static_cast<int>(
            token_list::data_types::Primitive::DOUBLE)}},
        {"str", {3, static_cast<int>(token_list::data_types::Primitive::STR)}},
        {"bool", {3, static_cast<int>(
            token_list::data_types::Primitive::BOOL)}},
};

static const std::unordered_map<std::string, std::pair<int, int>> 
    operator_map = {
        // Присваивание
        {"=", {0, static_cast<int>(token_list::operators::Assignment::SIMPLE)}},
    
    // Арифметика
    // {"+", {1, static_cast<int>(token_list::operators::Arithmetic::PLUS)}},
    // {"-", {1, static_cast<int>(token_list::operators::Arithmetic::MINUS)}},
    // {"*", {1, static_cast<int>(token_list::operators::Arithmetic::MULTIPLY)}},
    // {"/", {1, static_cast<int>(token_list::operators::Arithmetic::DIVIDE)}},
    // {"^", {1, static_cast<int>(token_list::operators::Arithmetic::POWER)}},
    // {"%", {1, static_cast<int>(token_list::operators::Arithmetic::MOD)}},
    
    // Сравнение
    // {"==", {2, static_cast<int>(token_list::operators::Comparison::EQUAL)}},
    // {"!=", {2, static_cast<int>(token_list::operators::Comparison::NOT_EQUAL)}},
    // {"<", {2, static_cast<int>(token_list::operators::Comparison::LESS)}},
    // {">", {2, static_cast<int>(token_list::operators::Comparison::GREATER)}},
    // {"<=", {2, static_cast<int>(token_list::operators::Comparison::LESS_EQUAL)}},
    // {">=", {2, static_cast<int>(token_list::operators::Comparison::GREATER_EQUAL)}},
    
    // Логика
    // {"&", {3, static_cast<int>(token_list::operators::Logical::AND)}},
    // {"|", {3, static_cast<int>(token_list::operators::Logical::OR)}},
    // {"!", {3, static_cast<int>(token_list::operators::Logical::NOT)}},
    
    // Специальные
    // {":=", {4, static_cast<int>(token_list::operators::Special::ASSIGN)}},
    // {"?:", {4, static_cast<int>(token_list::operators::Special::ELVIS)}},
    // {"?.", {4, static_cast<int>(token_list::operators::Special::SAFE_NAV)}},
    // {"|>", {4, static_cast<int>(token_list::operators::Special::PIPE)}},
    // {"..", {4, static_cast<int>(token_list::operators::Special::RANGE)}},
    // {"->", {4, static_cast<int>(token_list::operators::Special::ARROW)}},
    // {"...", {4, static_cast<int>(token_list::operators::Special::ELLIPSIS)}},
};

static const std::unordered_map<std::string, std::pair<int, int>> 
    punctuation_map = {
        // Скобки
        {"(", {0, static_cast<int>(token_list::Brackets::PARENTHESIS_L)}},
        {")", {0, static_cast<int>(token_list::Brackets::PARENTHESIS_R)}},
        {"{", {0, static_cast<int>(token_list::Brackets::BRACE_L)}},
        {"}", {0, static_cast<int>(token_list::Brackets::BRACE_R)}},
        {"[", {0, static_cast<int>(token_list::Brackets::BRACKET_L)}},
        {"]", {0, static_cast<int>(token_list::Brackets::BRACKET_R)}},
        
        // Разделители
        {";", {1, static_cast<int>(token_list::Symbols::SEMICOLON)}},
        {",", {1, static_cast<int>(token_list::Symbols::COMMA)}},
        {".", {1, static_cast<int>(token_list::Symbols::DOT)}},
};


#endif