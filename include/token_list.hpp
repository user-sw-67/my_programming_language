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
        IF, // if
        ELIF, // elif
        ELSE, // else
        DO, // do
        WHILE, // while 
        FOR, // for
        IN, // in
        STEP, // step
        BREAK, // break
        CONTINUE, // continue
        FUNC, // func
        RETURN, // return
        WHEN, // when
        TRY, // try
        CATCH, // catch
        FINALLY, // finally
        THROW, // throw
        USE, // use
        FROM, // from
        AS, // as
        CLASS, // class
        THIS, // this
        EXTENDS, // extends
        PRIVATE, // private
        PROTECTED, // protected
        PUBLIC, // public
        STATIC, // static
        GETTER, // getter
        SETTER, // setter
        MATCH, // match
        CASE, // case
        DEFAULT, // default
        TEST, // test
        ASSERT, // assert
    };

    enum class Symbols{
        SEMICOLON, // ;
        COMMA, // ,
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
            INT, // Int
            DOUBLE, // Double
            STR, // Str
            BOOL, // Bool
            NULL_VALUE, // Null
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

        enum class Class{
            SUPER, // super()
            NEW, // new()
            DELETE, // delete()
        };

        enum class OverTypes{
            INT, // int()
            DOUBLE, // double()
            STR, // str()
            BOOL, // bool()
            TYPE, // type()
        };
    }

    enum class Operators{
        ASSIGN, // =
        PLUS_ASSIGN, // +=
        MINUS_ASSIGN, // -=
        MULTIPLY_ASSIGN, // *=
        DIVIDE_ASSIGN, // /=
        POWER_ASSIGN, // ^=
        MOD_ASSIGN, // %=
        INT_DIVIDE_ASSIGN, // //=
        PLUS, // +
        MINUS, // -
        MULTIPLY, // *
        DIVIDE, // /
        POWER, // ^
        MOD, // %
        DIVIDE_EVENLY, // //
        EQUAL, // ==
        NOT_EQUAL, // !=
        LESS, // <
        GREATER, // >
        LESS_EQUAL, // <=
        GREATER_EQUAL, // >=
        OR, // |
        AND, // &
        NOT, // !
        DOT, // .
        ELVIS, // ?:
        SAFE_NAV, // ?.
        PIPE, // |>
        RANGE, // ..
        ARROW, // ->
        ELLIPSIS, // ...
        TERNARY_QUESTION, // ?
        TERNARY_COLON, // :
    };
}


enum class StateList{
    START,
    ERROR,
    IN_NUMBER, // обычное число: 123
    IN_NUMBER_DOT, // прочитали точку: 123.
    IN_NUMBER_FRACTION, // дробная часть: 123.45
    IN_STRING, // обычная строка: "hello"
    IN_IDENTIFIER, // идентификатор(любой): буквы, цифры, _
    IN_OPERATOR, // оператор 
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
            case token_list::Brackets::BRACKET_L: 
                return "Brackets : BRACKET_L : '" + value + "'";
            case token_list::Brackets::BRACKET_R: 
                return "Brackets : BRACKET_R : '" + value + "'";
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
            case token_list::SpecialWords::IF: 
                return "SpecialWords : IF : '" + value + "'";
            case token_list::SpecialWords::ELIF: 
                return "SpecialWords : ELIF : '" + value + "'";
            case token_list::SpecialWords::ELSE: 
                return "SpecialWords : ELSE : '" + value + "'";
            case token_list::SpecialWords::DO: 
                return "SpecialWords : DO : '" + value + "'";
            case token_list::SpecialWords::WHILE: 
                return "SpecialWords : WHILE : '" + value + "'";
            case token_list::SpecialWords::FOR: 
                return "SpecialWords : FOR : '" + value + "'";
            case token_list::SpecialWords::IN: 
                return "SpecialWords : IN : '" + value + "'";
            case token_list::SpecialWords::STEP: 
                return "SpecialWords : STEP : '" + value + "'";
            case token_list::SpecialWords::BREAK: 
                return "SpecialWords : BREAK : '" + value + "'";
            case token_list::SpecialWords::CONTINUE: 
                return "SpecialWords : CONTINUE : '" + value + "'";
            case token_list::SpecialWords::FUNC: 
                return "SpecialWords : FUNC : '" + value + "'";
            case token_list::SpecialWords::RETURN: 
                return "SpecialWords : RETURN : '" + value + "'";
            case token_list::SpecialWords::WHEN: 
                return "SpecialWords : WHEN : '" + value + "'";
            case token_list::SpecialWords::TRY: 
                return "SpecialWords : TRY : '" + value + "'";
            case token_list::SpecialWords::CATCH: 
                return "SpecialWords : CATCH : '" + value + "'";
            case token_list::SpecialWords::FINALLY: 
                return "SpecialWords : FINALLY : '" + value + "'";
            case token_list::SpecialWords::THROW: 
                return "SpecialWords : THROW : '" + value + "'";
            case token_list::SpecialWords::USE: 
                return "SpecialWords : USE : '" + value + "'";
            case token_list::SpecialWords::FROM: 
                return "SpecialWords : FROM : '" + value + "'";
            case token_list::SpecialWords::AS: 
                return "SpecialWords : AS : '" + value + "'";
            case token_list::SpecialWords::CLASS: 
                return "SpecialWords : CLASS : '" + value + "'";
            case token_list::SpecialWords::EXTENDS: 
                return "SpecialWords : EXTENDS : '" + value + "'";
            case token_list::SpecialWords::THIS: 
                return "SpecialWords : THIS : '" + value + "'";
            case token_list::SpecialWords::PRIVATE: 
                return "SpecialWords : PRIVATE : '" + value + "'";
            case token_list::SpecialWords::PUBLIC: 
                return "SpecialWords : PUBLIC : '" + value + "'";
            case token_list::SpecialWords::PROTECTED: 
                return "SpecialWords : PROTECTED : '" + value + "'";
            case token_list::SpecialWords::STATIC: 
                return "SpecialWords : STATIC : '" + value + "'";
            case token_list::SpecialWords::GETTER: 
                return "SpecialWords : GETTER : '" + value + "'";
            case token_list::SpecialWords::SETTER:
                return "SpecialWords : SETTER : '" + value + "'";
            case token_list::SpecialWords::MATCH:
                return "SpecialWords : MATCH : '" + value + "'";
            case token_list::SpecialWords::CASE:
                return "SpecialWords : CASE : '" + value + "'";
            case token_list::SpecialWords::DEFAULT:
                return "SpecialWords : DEFAULT : '" + value + "'";
            case token_list::SpecialWords::TEST:
                return "SpecialWords : TEST : '" + value + "'";
            case token_list::SpecialWords::ASSERT:
                return "SpecialWords : ASSERT : '" + value + "'";
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

inline std::string token_to_string(token_list::Operators type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::Operators::ASSIGN:
                return "Operator : ASSIGN : '" + value + "'";
            case token_list::Operators::PLUS_ASSIGN:
                return "Operator : PLUS_ASSIGN : '" + value + "'";
            case token_list::Operators::MINUS_ASSIGN:
                return "Operator : MINUS_ASSIGN : '" + value + "'";
            case token_list::Operators::MULTIPLY_ASSIGN:
                return "Operator : MULTIPLY_ASSIGN : '" + value + "'";
            case token_list::Operators::DIVIDE_ASSIGN:
                return "Operator : DIVIDE_ASSIGN : '" + value + "'";
            case token_list::Operators::POWER_ASSIGN:
                return "Operator : POWER_ASSIGN : '" + value + "'";
            case token_list::Operators::MOD_ASSIGN:
                return "Operator : MOD_ASSIGN : '" + value + "'";
            case token_list::Operators::INT_DIVIDE_ASSIGN:
                return "Operator : INT_DIVIDE_ASSIGN : '" + value + "'";
            case token_list::Operators::PLUS:
                return "Operator : PLUS : '" + value + "'";
            case token_list::Operators::MINUS:
                return "Operator : MINUS : '" + value + "'";
            case token_list::Operators::MULTIPLY:
                return "Operator : MULTIPLY : '" + value + "'";
            case token_list::Operators::DIVIDE:
                return "Operator : DIVIDE : '" + value + "'";
            case token_list::Operators::DIVIDE_EVENLY:
                return "Operator : DIVIDE_EVENLY : '" + value + "'";
            case token_list::Operators::POWER:
                return "Operator : POWER : '" + value + "'";
            case token_list::Operators::MOD:
                return "Operator : MOD : '" + value + "'";
            case token_list::Operators::EQUAL:
                return "Operator : EQUAL : '" + value + "'";
            case token_list::Operators::NOT_EQUAL:
                return "Operator : NOT_EQUAL : '" + value + "'";
            case token_list::Operators::LESS:
                return "Operator : LESS : '" + value + "'";
            case token_list::Operators::GREATER:
                return "Operator : GREATER : '" + value + "'";
            case token_list::Operators::LESS_EQUAL:
                return "Operator : LESS_EQUAL : '" + value + "'";
            case token_list::Operators::GREATER_EQUAL:
                return "Operator : GREATER_EQUAL : '" + value + "'";
            case token_list::Operators::AND:
                return "Operator : AND : '" + value + "'";
            case token_list::Operators::OR:
                return "Operator : OR : '" + value + "'";
            case token_list::Operators::NOT:
                return "Operator : NOT : '" + value + "'";
            case token_list::Operators::DOT:
                return "Operator : DOT : '" + value + "'";
            case token_list::Operators::ELVIS:
                return "Operator : ELVIS : '" + value + "'";
            case token_list::Operators::SAFE_NAV:
                return "Operator : SAFE_NAV : '" + value + "'";
            case token_list::Operators::PIPE:
                return "Operator : PIPE : '" + value + "'";
            case token_list::Operators::RANGE:
                return "Operator : RANGE : '" + value + "'";
            case token_list::Operators::ARROW:
                return "Operator : ARROW : '" + value + "'";
            case token_list::Operators::ELLIPSIS:
                return "Operator : ELLIPSIS : '" + value + "'";
            case token_list::Operators::TERNARY_QUESTION:
                return "Operator : TERNARY_QUESTION : '" + value + "'";
            case token_list::Operators::TERNARY_COLON:
                return "Operator : TERNARY_COLON : '" + value + "'";
            default: 
                return "Operator : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(
    token_list::built_functions::StandardStreams type, 
        const std::string& value = "undefined") {
            switch (type) {
                case token_list::built_functions::StandardStreams::PRINT: 
                    return "Function StandardStreams : PRINT : '" 
                        + value + "'";
                case token_list::built_functions::StandardStreams::PRINTLN: 
                    return "Function StandardStreams : PRINTLN : '" 
                        + value + "'";
                case token_list::built_functions::StandardStreams::PRINTERR: 
                    return "Function StandardStreams : PRINTERR : '" 
                        + value + "'";
                case token_list::built_functions::StandardStreams::PRINTERRLN: 
                    return "Function StandardStreams : PRINTERRLN : '" 
                        + value + "'";
                case token_list::built_functions::StandardStreams::INPUT: 
                    return "Function StandardStreams : INPUT : '" 
                        + value + "'";
                default: 
                    return "Function StandardStreams : Unknown : '" 
                        + value + "'";
            }
}

inline std::string token_to_string(token_list::built_functions::Class type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::built_functions::Class::SUPER: 
                return "Function Class : SUPER : '" + value + "'";
            case token_list::built_functions::Class::NEW: 
                return "Function Class : NEW : '" + value + "'";
            case token_list::built_functions::Class::DELETE: 
                return "Function Class : DELETE : '" + value + "'";
            default: 
                return "Function Class : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::built_functions::OverTypes type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::built_functions::OverTypes::INT: 
                return "Function OverTypes : INT : '" + value + "'";
            case token_list::built_functions::OverTypes::DOUBLE: 
                return "Function OverTypes : DOUBLE : '" + value + "'";
            case token_list::built_functions::OverTypes::BOOL: 
                return "Function OverTypes : BOOL : '" + value + "'";
            case token_list::built_functions::OverTypes::STR: 
                return "Function OverTypes : STR : '" + value + "'";
            case token_list::built_functions::OverTypes::TYPE:
                return "Function OverTypes : TYPE : '" + value + "'";
            default: 
                return "Function OverTypes : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::data_types::Primitive type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::data_types::Primitive::INT: 
                return "DataType Primitive : INT : '" + value + "'";
            case token_list::data_types::Primitive::DOUBLE:     
                return "DataType Primitive : DOUBLE : '" + value + "'";
            case token_list::data_types::Primitive::STR: 
                return "DataType Primitive : STR : '" + value + "'";
            case token_list::data_types::Primitive::BOOL: 
                return "DataType Primitive : BOOL : '" + value + "'";
            case token_list::data_types::Primitive::NULL_VALUE: 
                return "DataType Primitive : NULL : '" + value + "'";
            default: 
                return "DataType Primitive : Unknown : '" + value + "'";
        }
}


namespace id_keyword{
    constexpr int SpecialWords = 0;
    constexpr int Literals = 1;
    constexpr int DataTypePrimitive = 2;
    constexpr int Operators = 3;
    constexpr int Brackets = 4;
    constexpr int Separators = 5;
    constexpr int FunctionsStandardStreams = 6;
    constexpr int FunctionsClass = 7;
    constexpr int FunctionsOverTypes = 8;
}



static const std::unordered_map<std::string, std::pair<int, int>> 
    keyword_map = {
        // Специальные слова
        {"make", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::MAKE)}},
        {"const", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::CONST)}},
        {"if", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::IF)}},
        {"elif", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::ELIF)}},
        {"else", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::ELSE)}},
        {"do", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::DO)}},
        {"while", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::WHILE)}},
        {"for", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::FOR)}},
        {"in", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::IN)}},
        {"step", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::STEP)}},
        {"break", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::BREAK)}},
        {"continue", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::CONTINUE)}},
        {"func", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::FUNC)}},
        {"return", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::RETURN)}},
        {"when", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::WHEN)}},
        {"try", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::TRY)}},
        {"catch", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::CATCH)}},
        {"finally", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::FINALLY)}},
        {"throw", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::THROW)}},
        {"use", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::USE)}},
        {"from", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::FROM)}},
        {"as", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::AS)}},
        {"class", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::CLASS)}},
        {"extends", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::EXTENDS)}},
        {"this", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::THIS)}},
        {"private", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::PRIVATE)}},
        {"public", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::PUBLIC)}},
        {"protected", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::PROTECTED)}},
        {"static", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::STATIC)}},
        {"getter", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::GETTER)}},
        {"setter", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::SETTER)}},
        {"match", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::MATCH)}},
        {"case", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::CASE)}},
        {"default", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::DEFAULT)}},
        {"test", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::TEST)}},
        {"assert", {id_keyword::SpecialWords, static_cast<int>(token_list::SpecialWords::ASSERT)}},
        
        // Литералы
        {"null", {id_keyword::Literals, static_cast<int>(token_list::Literals::NULL_VALUE)}},
        {"true", {id_keyword::Literals, static_cast<int>(token_list::Literals::BOOL)}},
        {"false", {id_keyword::Literals, static_cast<int>(token_list::Literals::BOOL)}},
        
        // Типы данных примитивные
        {"Int", {id_keyword::DataTypePrimitive, static_cast<int>(token_list::data_types::Primitive::INT)}},
        {"Double", {id_keyword::DataTypePrimitive, static_cast<int>(token_list::data_types::Primitive::DOUBLE)}},
        {"Str", {id_keyword::DataTypePrimitive, static_cast<int>(token_list::data_types::Primitive::STR)}},
        {"Bool", {id_keyword::DataTypePrimitive, static_cast<int>(token_list::data_types::Primitive::BOOL)}},
        {"Null", {id_keyword::DataTypePrimitive, static_cast<int>(token_list::data_types::Primitive::NULL_VALUE)}},

        // Встроенные функции потока
        {"print", {id_keyword::FunctionsStandardStreams, static_cast<int>(token_list::built_functions::StandardStreams::PRINT)}},
        {"println", {id_keyword::FunctionsStandardStreams, static_cast<int>(token_list::built_functions::StandardStreams::PRINTLN)}},
        {"printerr", {id_keyword::FunctionsStandardStreams, static_cast<int>(token_list::built_functions::StandardStreams::PRINTERR)}},
        {"printerrln", {id_keyword::FunctionsStandardStreams, static_cast<int>(token_list::built_functions::StandardStreams::PRINTERRLN)}},
        {"input", {id_keyword::FunctionsStandardStreams, static_cast<int>(token_list::built_functions::StandardStreams::INPUT)}},

        // Встроенные функции класса
        {"super", {id_keyword::FunctionsClass, static_cast<int>(token_list::built_functions::Class::SUPER)}},
        {"new", {id_keyword::FunctionsClass, static_cast<int>(token_list::built_functions::Class::NEW)}},
        {"delete", {id_keyword::FunctionsClass, static_cast<int>(token_list::built_functions::Class::DELETE)}},

        // Встроенные функции над типами
        {"int", {id_keyword::FunctionsOverTypes, static_cast<int>(token_list::built_functions::OverTypes::INT)}},
        {"double", {id_keyword::FunctionsOverTypes, static_cast<int>(token_list::built_functions::OverTypes::DOUBLE)}},
        {"bool", {id_keyword::FunctionsOverTypes, static_cast<int>(token_list::built_functions::OverTypes::BOOL)}},
        {"str", {id_keyword::FunctionsOverTypes, static_cast<int>(token_list::built_functions::OverTypes::STR)}},
        {"type", {id_keyword::FunctionsOverTypes, static_cast<int>(token_list::built_functions::OverTypes::TYPE)}},

};

static const std::unordered_map<std::string, std::pair<int, int>> 
    operator_map = {
         // Операторы
        {"=", {id_keyword::Operators, static_cast<int>(token_list::Operators::ASSIGN)}},
        {"+=", {id_keyword::Operators, static_cast<int>(token_list::Operators::PLUS_ASSIGN)}},
        {"-=", {id_keyword::Operators, static_cast<int>(token_list::Operators::MINUS_ASSIGN)}},
        {"*=", {id_keyword::Operators, static_cast<int>(token_list::Operators::MULTIPLY_ASSIGN)}},
        {"/=", {id_keyword::Operators, static_cast<int>(token_list::Operators::DIVIDE_ASSIGN)}},
        {"^=", {id_keyword::Operators, static_cast<int>(token_list::Operators::POWER_ASSIGN)}},
        {"%=", {id_keyword::Operators, static_cast<int>(token_list::Operators::MOD_ASSIGN)}},
        {"//=", {id_keyword::Operators, static_cast<int>(token_list::Operators::INT_DIVIDE_ASSIGN)}},
        {"+", {id_keyword::Operators, static_cast<int>(token_list::Operators::PLUS)}},
        {"-", {id_keyword::Operators, static_cast<int>(token_list::Operators::MINUS)}},
        {"*", {id_keyword::Operators, static_cast<int>(token_list::Operators::MULTIPLY)}},
        {"/", {id_keyword::Operators, static_cast<int>(token_list::Operators::DIVIDE)}},
        {"//", {id_keyword::Operators, static_cast<int>(token_list::Operators::DIVIDE_EVENLY)}},
        {"^", {id_keyword::Operators, static_cast<int>(token_list::Operators::POWER)}},
        {"%", {id_keyword::Operators, static_cast<int>(token_list::Operators::MOD)}},
        {"==", {id_keyword::Operators, static_cast<int>(token_list::Operators::EQUAL)}},
        {"!=", {id_keyword::Operators, static_cast<int>(token_list::Operators::NOT_EQUAL)}},
        {"<", {id_keyword::Operators, static_cast<int>(token_list::Operators::LESS)}},
        {">", {id_keyword::Operators, static_cast<int>(token_list::Operators::GREATER)}},
        {"<=", {id_keyword::Operators, static_cast<int>(token_list::Operators::LESS_EQUAL)}},
        {">=", {id_keyword::Operators, static_cast<int>(token_list::Operators::GREATER_EQUAL)}},
        {"&", {id_keyword::Operators, static_cast<int>(token_list::Operators::AND)}},
        {"|", {id_keyword::Operators, static_cast<int>(token_list::Operators::OR)}},
        {"!", {id_keyword::Operators, static_cast<int>(token_list::Operators::NOT)}},
        {".", {id_keyword::Operators, static_cast<int>(token_list::Operators::DOT)}},
        {"?:", {id_keyword::Operators, static_cast<int>(token_list::Operators::ELVIS)}},
        {"?.", {id_keyword::Operators, static_cast<int>(token_list::Operators::SAFE_NAV)}},
        {"|>", {id_keyword::Operators, static_cast<int>(token_list::Operators::PIPE)}},
        {"..", {id_keyword::Operators, static_cast<int>(token_list::Operators::RANGE)}},
        {"->", {id_keyword::Operators, static_cast<int>(token_list::Operators::ARROW)}},
        {"...", {id_keyword::Operators, static_cast<int>(token_list::Operators::ELLIPSIS)}},
        {"?", {id_keyword::Operators, static_cast<int>(token_list::Operators::TERNARY_QUESTION)}},
        {":", {id_keyword::Operators, static_cast<int>(token_list::Operators::TERNARY_COLON)}},
};

static const std::unordered_map<std::string, std::pair<int, int>> 
    punctuation_map = {
        // Скобки
        {"(", {id_keyword::Brackets, static_cast<int>(token_list::Brackets::PARENTHESIS_L)}},
        {")", {id_keyword::Brackets, static_cast<int>(token_list::Brackets::PARENTHESIS_R)}},
        {"{", {id_keyword::Brackets, static_cast<int>(token_list::Brackets::BRACE_L)}},
        {"}", {id_keyword::Brackets, static_cast<int>(token_list::Brackets::BRACE_R)}},
        {"[", {id_keyword::Brackets, static_cast<int>(token_list::Brackets::BRACKET_L)}},
        {"]", {id_keyword::Brackets, static_cast<int>(token_list::Brackets::BRACKET_R)}},

        // Разделители
        {";", {id_keyword::Separators, static_cast<int>(token_list::Symbols::SEMICOLON)}},
        {",", {id_keyword::Separators, static_cast<int>(token_list::Symbols::COMMA)}},
};

#endif