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

    namespace operators{

        enum class Assignment{
            SIMPLE, // =
            PLUS_ASSIGN, // +=
            MINUS_ASSIGN, // -=
            MULTIPLY_ASSIGN, // *=
            DIVIDE_ASSIGN, // /=
            POWER_ASSIGN, // ^=
            MOD_ASSIGN, // %=
            INT_DIVIDE_ASSIGN, // //=
        };
        
        enum class Arithmetic{
            PLUS, // +
            MINUS, // -
            MULTIPLY, // *
            DIVIDE, // /
            POWER, // ^
            MOD, // %
            DIVIDE_EVENLY, // //
        };

        enum class Comparison{
            EQUAL, // ==
            NOT_EQUAL, // !=
            LESS, // <
            GREATER, // >
            LESS_EQUAL, // <=
            GREATER_EQUAL, // >=
        };

        enum class Logical{
            OR, // |
            AND, // &
            NOT // !
        };
        
        enum class Special{
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
    

}


enum class StateList{
    START,
    ERROR,
    IN_NUMBER, // обычное число: 123
    IN_NUMBER_DOT, // прочитали точку: 123.
    IN_NUMBER_FRACTION, // дробная часть: 123.45
    IN_STRING, // обычная строка: "hello"
    IN_IDENTIFIER, // идентификатор(любой): буквы, цифры, _
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

inline std::string token_to_string(token_list::operators::Assignment type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::operators::Assignment::SIMPLE: 
                return "Operator Assignment : SIMPLE : '" + value + "'";
            case token_list::operators::Assignment::PLUS_ASSIGN: 
                return "Operator Assignment : PLUS_ASSIGN : '" + value + "'";
            case token_list::operators::Assignment::MINUS_ASSIGN: 
                return "Operator Assignment : MINUS_ASSIGN : '" + value + "'";
            case token_list::operators::Assignment::MULTIPLY_ASSIGN: 
                return "Operator Assignment : MULTIPLY_ASSIGN : '" + value + "'";
            case token_list::operators::Assignment::DIVIDE_ASSIGN: 
                return "Operator Assignment : DIVIDE_ASSIGN : '" + value + "'";
            case token_list::operators::Assignment::POWER_ASSIGN: 
                return "Operator Assignment : POWER_ASSIGN : '" + value + "'";
            case token_list::operators::Assignment::MOD_ASSIGN: 
                return "Operator Assignment : MOD_ASSIGN : '" + value + "'";
            case token_list::operators::Assignment::INT_DIVIDE_ASSIGN: 
                return "Operator Assignment : INT_DIVIDE_ASSIGN : '" + value + "'";
            default: 
                return "Operator Assignment : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::operators::Arithmetic type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::operators::Arithmetic::PLUS: 
                return "Operator Assignment : PLUS : '" + value + "'";
            case token_list::operators::Arithmetic::MINUS: 
                return "Operator Assignment : MINUS : '" + value + "'";
            case token_list::operators::Arithmetic::MULTIPLY: 
                return "Operator Assignment : MULTIPLY : '" + value + "'";
            case token_list::operators::Arithmetic::DIVIDE: 
                return "Operator Assignment : DIVIDE : '" + value + "'";
            case token_list::operators::Arithmetic::MOD: 
                return "Operator Assignment : MOD : '" + value + "'";
            case token_list::operators::Arithmetic::POWER:
                return "Operator Assignment : POWER : '" + value + "'";
            case token_list::operators::Arithmetic::DIVIDE_EVENLY:
                return "Operator Assignment : DIVIDE_EVENLY : '" + value + "'";
            default: 
                return "Operator Assignment : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::operators::Comparison type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::operators::Comparison::EQUAL: 
                return "Operator Comparison : EQUAL : '" + value + "'";
            case token_list::operators::Comparison::NOT_EQUAL: 
                return "Operator Comparison : NOT_EQUAL : '" + value + "'";
            case token_list::operators::Comparison::GREATER:
                return "Operator Comparison : GREATER : '" + value + "'";
            case token_list::operators::Comparison::GREATER_EQUAL:
                return "Operator Comparison : GREATER_EQUAL : '" + value + "'";
            case token_list::operators::Comparison::LESS:
                return "Operator Comparison : LESS : '" + value + "'";
            case token_list::operators::Comparison::LESS_EQUAL:
                return "Operator Comparison : LESS_EQUAL : '" + value + "'";
            default: 
                return "Operator Comparison : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::operators::Logical type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::operators::Logical::OR: 
                return "Operator Logical : OR : '" + value + "'";
            case token_list::operators::Logical::AND: 
                return "Operator Logical : AND : '" + value + "'";
            case token_list::operators::Logical::NOT:
                return "Operator Logical : NOT : '" + value + "'";
            default: 
                return "Operator Logical : Unknown : '" + value + "'";
        }
}

inline std::string token_to_string(token_list::operators::Special type, 
    const std::string& value = "undefined") {
        switch (type) {
            case token_list::operators::Special::DOT:
                return "Operator Special : DOT : '" + value + "'";
            case token_list::operators::Special::ELVIS:
                return "Operator Special : ELVIS : '" + value + "'";
            case token_list::operators::Special::SAFE_NAV:
                return "Operator Special : SAFE_NAV : '" + value + "'";
            case token_list::operators::Special::PIPE:
                return "Operator Special : PIPE : '" + value + "'";
            case token_list::operators::Special::RANGE:
                return "Operator Special : RANGE : '" + value + "'";
            case token_list::operators::Special::ARROW:
                return "Operator Special : ARROW : '" + value + "'";
            case token_list::operators::Special::ELLIPSIS:
                return "Operator Special : ELLIPSIS : '" + value + "'";
            case token_list::operators::Special::TERNARY_COLON:
                return "Operator Special : TERNARY_COLON : '" + value + "'";
            case token_list::operators::Special::TERNARY_QUESTION:
                return "Operator Special : TERNARY_QUESTION : '" + value + "'";
            default: 
                return "Operator Special : Unknown : '" + value + "'";
        }
}


static const std::unordered_map<std::string, std::pair<int, int>> 
    keyword_map = {
        // Специальные слова
        {"make", {0, static_cast<int>(token_list::SpecialWords::MAKE)}},
        {"const", {0, static_cast<int>(token_list::SpecialWords::CONST)}},
        {"if", {0, static_cast<int>(token_list::SpecialWords::IF)}},
        {"elif", {0, static_cast<int>(token_list::SpecialWords::ELIF)}},
        {"else", {0, static_cast<int>(token_list::SpecialWords::ELSE)}},
        {"do", {0, static_cast<int>(token_list::SpecialWords::DO)}},
        {"while", {0, static_cast<int>(token_list::SpecialWords::WHILE)}},
        {"for", {0, static_cast<int>(token_list::SpecialWords::FOR)}},
        {"in", {0, static_cast<int>(token_list::SpecialWords::IN)}},
        {"step", {0, static_cast<int>(token_list::SpecialWords::STEP)}},
        {"break", {0, static_cast<int>(token_list::SpecialWords::BREAK)}},
        {"continue", {0, static_cast<int>(token_list::SpecialWords::CONTINUE)}},
        {"func", {0, static_cast<int>(token_list::SpecialWords::FUNC)}},
        {"return", {0, static_cast<int>(token_list::SpecialWords::RETURN)}},
        {"when", {0, static_cast<int>(token_list::SpecialWords::WHEN)}},
        {"try", {0, static_cast<int>(token_list::SpecialWords::TRY)}},
        {"catch", {0, static_cast<int>(token_list::SpecialWords::CATCH)}},
        {"finally", {0, static_cast<int>(token_list::SpecialWords::FINALLY)}},
        {"throw", {0, static_cast<int>(token_list::SpecialWords::THROW)}},
        {"use", {0, static_cast<int>(token_list::SpecialWords::USE)}},
        {"from", {0, static_cast<int>(token_list::SpecialWords::FROM)}},
        {"as", {0, static_cast<int>(token_list::SpecialWords::AS)}},
        {"class", {0, static_cast<int>(token_list::SpecialWords::CLASS)}},
        {"extends", {0, static_cast<int>(token_list::SpecialWords::EXTENDS)}},
        {"this", {0, static_cast<int>(token_list::SpecialWords::THIS)}},
        {"private", {0, static_cast<int>(token_list::SpecialWords::PRIVATE)}},
        {"public", {0, static_cast<int>(token_list::SpecialWords::PUBLIC)}},
        {"protected", {0, static_cast<int>(
            token_list::SpecialWords::PROTECTED)}},
        {"static", {0, static_cast<int>(token_list::SpecialWords::STATIC)}},
        {"getter", {0, static_cast<int>(token_list::SpecialWords::GETTER)}},
        {"setter", {0, static_cast<int>(token_list::SpecialWords::SETTER)}},
        {"match", {0, static_cast<int>(token_list::SpecialWords::MATCH)}},
        {"case", {0, static_cast<int>(token_list::SpecialWords::CASE)}},
        {"default", {0, static_cast<int>(token_list::SpecialWords::DEFAULT)}},
        {"test", {0, static_cast<int>(token_list::SpecialWords::TEST)}},
        {"assert", {0, static_cast<int>(token_list::SpecialWords::ASSERT)}},

        
        // Литералы
        {"null", {1, static_cast<int>(token_list::Literals::NULL_VALUE)}},
        {"true", {1, static_cast<int>(token_list::Literals::BOOL)}},
        {"false", {1, static_cast<int>(token_list::Literals::BOOL)}},
        
        // Типы данных
        {"Int", {2, static_cast<int>(token_list::data_types::Primitive::INT)}},
        {"Double", {2, static_cast<int>(
            token_list::data_types::Primitive::DOUBLE)}},
        {"Str", {2, static_cast<int>(token_list::data_types::Primitive::STR)}},
        {"Bool", {2, static_cast<int>(
            token_list::data_types::Primitive::BOOL)}},
        {"Null", {2, static_cast<int>(
            token_list::data_types::Primitive::NULL_VALUE)}},

        // Встроенные функции потока
        {"print", {3, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINT)}},
        {"println", {3, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINTLN)}},
        {"printerr", {3, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINTERR)}},
        {"printerrln", {3, static_cast<int>(
            token_list::built_functions::StandardStreams::PRINTERRLN)}},
        {"input", {3, static_cast<int>(
            token_list::built_functions::StandardStreams::INPUT)}},

        // Встроенные функции класса
        {"super", {4, static_cast<int>(
            token_list::built_functions::Class::SUPER)}},
        {"new", {4, static_cast<int>(
            token_list::built_functions::Class::NEW)}},
        {"delete", {4, static_cast<int>(
            token_list::built_functions::Class::DELETE)}},

        // Встроенные функции над типами
        {"int", {5, static_cast<int>(
            token_list::built_functions::OverTypes::INT)}},
        {"double", {5, static_cast<int>(
            token_list::built_functions::OverTypes::DOUBLE)}},
        {"bool", {5, static_cast<int>(
            token_list::built_functions::OverTypes::BOOL)}},
        {"str", {5, static_cast<int>(
            token_list::built_functions::OverTypes::STR)}},
        {"type", {5, static_cast<int>(
            token_list::built_functions::OverTypes::TYPE)}},
};

static const std::unordered_map<std::string, std::pair<int, int>> 
    operator_map = {
        // Присваивание
        {"=", {0, static_cast<int>(token_list::operators::Assignment::SIMPLE)}},
        {"+=", {0, static_cast<int>(
            token_list::operators::Assignment::PLUS_ASSIGN)}},
        {"-=", {0, static_cast<int>(
            token_list::operators::Assignment::MINUS_ASSIGN)}},
        {"*=", {0, static_cast<int>(
            token_list::operators::Assignment::MULTIPLY_ASSIGN)}},
        {"/=", {0, static_cast<int>(
            token_list::operators::Assignment::DIVIDE_ASSIGN)}},
        {"^=", {0, static_cast<int>(
            token_list::operators::Assignment::POWER_ASSIGN)}},
        {"%=", {0, static_cast<int>(
            token_list::operators::Assignment::MOD_ASSIGN)}},
        {"//=", {0, static_cast<int>(
            token_list::operators::Assignment::INT_DIVIDE_ASSIGN)}},

        // Арифметика
        {"+", {1, static_cast<int>(token_list::operators::Arithmetic::PLUS)}},
        {"-", {1, static_cast<int>(token_list::operators::Arithmetic::MINUS)}},
        {"*", {1, static_cast<int>(
            token_list::operators::Arithmetic::MULTIPLY)}},
        {"/", {1, static_cast<int>(token_list::operators::Arithmetic::DIVIDE)}},
        {"//", {1, static_cast<int>(
            token_list::operators::Arithmetic::DIVIDE_EVENLY)}},
        {"^", {1, static_cast<int>(token_list::operators::Arithmetic::POWER)}},
        {"%", {1, static_cast<int>(token_list::operators::Arithmetic::MOD)}},
    
        // Сравнение
        {"==", {2, static_cast<int>(
            token_list::operators::Comparison::EQUAL)}},
        {"!=", {2, static_cast<int>(
            token_list::operators::Comparison::NOT_EQUAL)}},
        {"<", {2, static_cast<int>(
            token_list::operators::Comparison::LESS)}},
        {">", {2, static_cast<int>(
            token_list::operators::Comparison::GREATER)}},
        {"<=", {2, static_cast<int>(
            token_list::operators::Comparison::LESS_EQUAL)}},
        {">=", {2, static_cast<int>(
            token_list::operators::Comparison::GREATER_EQUAL)}},
        
        // Логика
        {"&", {3, static_cast<int>(token_list::operators::Logical::AND)}},
        {"|", {3, static_cast<int>(token_list::operators::Logical::OR)}},
        {"!", {3, static_cast<int>(token_list::operators::Logical::NOT)}},
        
        // Специальные
        {".", {4, static_cast<int>(token_list::operators::Special::DOT)}},
        {"?:", {4, static_cast<int>(token_list::operators::Special::ELVIS)}},
        {"?.", {4, static_cast<int>(
            token_list::operators::Special::SAFE_NAV)}},
        {"|>", {4, static_cast<int>(token_list::operators::Special::PIPE)}},
        {"..", {4, static_cast<int>(token_list::operators::Special::RANGE)}},
        {"->", {4, static_cast<int>(token_list::operators::Special::ARROW)}},
        {"...", {4, static_cast<int>(
            token_list::operators::Special::ELLIPSIS)}},
        {":", {4, static_cast<int>(
            token_list::operators::Special::TERNARY_COLON)}},
        {"?", {4, static_cast<int>(
            token_list::operators::Special::TERNARY_QUESTION)}},

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
};


#endif