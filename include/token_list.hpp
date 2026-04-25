#ifndef TOKEN_LIST
#define TOKEN_LIST

#include <string>
#include <type_traits>
#include <unordered_map>


enum class TokenType {
    IDENTIFIER,
    END_OF_FILE,
    
    KW_MAKE, // make
    KW_CONST, // const
    KW_IF, // if
    KW_ELIF, // elif
    KW_ELSE, // else
    KW_DO, // do
    KW_WHILE, // while
    KW_FOR, // for
    KW_IN, // in
    KW_STEP, // step
    KW_BREAK, // break
    KW_CONTINUE, // continue
    KW_FUNC, // func
    KW_RETURN, // return
    KW_WHEN, // when
    KW_TRY, // try
    KW_CATCH, // catch
    KW_FINALLY, // finally
    KW_THROW, // throw
    KW_USE, // use
    KW_FROM, // from
    KW_AS, // as
    KW_CLASS, // class
    KW_THIS, // this
    KW_EXTENDS, // extends
    KW_PRIVATE, // private
    KW_PROTECTED, // protected
    KW_PUBLIC, // public
    KW_STATIC, // static
    KW_GETTER, // getter
    KW_SETTER, // setter
    KW_MATCH, // match
    KW_CASE, // case
    KW_DEFAULT, // default
    KW_TEST, // test
    KW_ASSERT, // assert
    
    LIT_INT, // 42, -17, 0, 255
    LIT_DOUBLE, // 3.14, -0.5, 2.0, 1e-5
    LIT_STR, // "hello", "world", "John"
    LIT_BOOL, // true, false
    LIT_NULL, // null
    
    PAREN_L, // (
    PAREN_R, // )
    BRACE_L, // {
    BRACE_R, // }
    BRACKET_L, // [
    BRACKET_R, // ]
    
    SEMICOLON, // ;
    COMMA, // ,

    OP_ASSIGN, // =
    OP_PLUS_ASSIGN, // +=
    OP_MINUS_ASSIGN, // -=
    OP_MUL_ASSIGN, // *=
    OP_DIV_ASSIGN, // /=
    OP_POW_ASSIGN, // ^=
    OP_MOD_ASSIGN, // %=
    OP_INT_DIV_ASSIGN, // //=
    OP_PLUS, // +
    OP_MINUS, // -
    OP_MUL, // *
    OP_DIV, // /
    OP_INT_DIV, // //
    OP_POW, // ^
    OP_MOD, // %
    OP_EQ, // ==
    OP_NE, // !=
    OP_LT, // <
    OP_GT, // >
    OP_LE, // <=
    OP_GE, // >=
    OP_AND, // &
    OP_OR, // |
    OP_NOT, // !
    OP_DOT, // .
    OP_SAFE_NAV, // ?.
    OP_PIPE, // |>
    OP_ELVIS, // ?:
    OP_RANGE, // ..
    OP_ARROW, // ->
    OP_ELLIPSIS, // ...
    OP_QUEST, // ?
    OP_COLON, // :
};


inline std::string token_to_string(TokenType type, 
    const std::string& value = "undefined") {
        switch (type) {
            case TokenType::IDENTIFIER: return "IDENTIFIER : '" + value + "'";
            case TokenType::END_OF_FILE: return "END_OF_FILE";
            
            case TokenType::KW_MAKE: return "MAKE";
            case TokenType::KW_CONST: return "CONST";
            case TokenType::KW_IF: return "IF";
            case TokenType::KW_ELIF: return "ELIF";
            case TokenType::KW_ELSE: return "ELSE";
            case TokenType::KW_DO: return "DO";
            case TokenType::KW_WHILE: return "WHILE";
            case TokenType::KW_FOR: return "FOR";
            case TokenType::KW_IN: return "IN";
            case TokenType::KW_STEP: return "STEP";
            case TokenType::KW_BREAK: return "BREAK";
            case TokenType::KW_CONTINUE: return "CONTINUE";
            case TokenType::KW_FUNC: return "FUNC";
            case TokenType::KW_RETURN: return "RETURN";
            case TokenType::KW_WHEN: return "WHEN";
            case TokenType::KW_TRY: return "TRY";
            case TokenType::KW_CATCH: return "CATCH";
            case TokenType::KW_FINALLY: return "FINALLY";
            case TokenType::KW_THROW: return "THROW";
            case TokenType::KW_USE: return "USE";
            case TokenType::KW_FROM: return "FROM";
            case TokenType::KW_AS: return "AS";
            case TokenType::KW_CLASS: return "CLASS";
            case TokenType::KW_THIS: return "THIS";
            case TokenType::KW_EXTENDS: return "EXTENDS";
            case TokenType::KW_PRIVATE: return "PRIVATE";
            case TokenType::KW_PROTECTED: return "PROTECTED";
            case TokenType::KW_PUBLIC: return "PUBLIC";
            case TokenType::KW_STATIC: return "STATIC";
            case TokenType::KW_GETTER: return "GETTER";
            case TokenType::KW_SETTER: return "SETTER";
            case TokenType::KW_MATCH: return "MATCH";
            case TokenType::KW_CASE: return "CASE";
            case TokenType::KW_DEFAULT: return "DEFAULT";
            case TokenType::KW_TEST: return "TEST";
            case TokenType::KW_ASSERT: return "ASSERT";
            
            case TokenType::LIT_INT: return "LIT_INT : '" + value + "'";
            case TokenType::LIT_DOUBLE: return "LIT_DOUBLE : '" + value + "'";
            case TokenType::LIT_STR: return "LIT_STR : '" + value + "'";
            case TokenType::LIT_BOOL: return "LIT_BOOL : '" + value + "'";
            case TokenType::LIT_NULL: return "LIT_NULL";
            
            case TokenType::PAREN_L: return "PAREN_L";
            case TokenType::PAREN_R: return "PAREN_R";
            case TokenType::BRACE_L: return "BRACE_L";
            case TokenType::BRACE_R: return "BRACE_R";
            case TokenType::BRACKET_L: return "BRACKET_L";
            case TokenType::BRACKET_R: return "BRACKET_R";
            
            case TokenType::SEMICOLON: return "SEMICOLON";
            case TokenType::COMMA: return "COMMA";
            
            case TokenType::OP_ASSIGN: return "OPERATOR =";
            case TokenType::OP_PLUS_ASSIGN: return "OPERATOR +=";
            case TokenType::OP_MINUS_ASSIGN: return "OPERATOR -=";
            case TokenType::OP_MUL_ASSIGN: return "OPERATOR *=";
            case TokenType::OP_DIV_ASSIGN: return "OPERATOR /=";
            case TokenType::OP_POW_ASSIGN: return "OPERATOR ^=";
            case TokenType::OP_MOD_ASSIGN: return "OPERATOR %=";
            case TokenType::OP_INT_DIV_ASSIGN: return "OPERATOR //=";
            case TokenType::OP_PLUS: return "OPERATOR +";
            case TokenType::OP_MINUS: return "OPERATOR -";
            case TokenType::OP_MUL: return "OPERATOR *";
            case TokenType::OP_DIV: return "OPERATOR /";
            case TokenType::OP_INT_DIV: return "OPERATOR //";
            case TokenType::OP_POW: return "OPERATOR ^";
            case TokenType::OP_MOD: return "OPERATOR %";
            case TokenType::OP_EQ: return "OPERATOR ==";
            case TokenType::OP_NE: return "OPERATOR !=";
            case TokenType::OP_LT: return "OPERATOR <";
            case TokenType::OP_GT: return "OPERATOR >";
            case TokenType::OP_LE: return "OPERATOR <=";
            case TokenType::OP_GE: return "OPERATOR >=";
            case TokenType::OP_AND: return "OPERATOR &";
            case TokenType::OP_OR: return "OPERATOR |";
            case TokenType::OP_NOT: return "OPERATOR !";
            case TokenType::OP_DOT: return "OPERATOR .";
            case TokenType::OP_ELVIS: return "OPERATOR ?:";
            case TokenType::OP_SAFE_NAV: return "OPERATOR ?.";
            case TokenType::OP_PIPE: return "OPERATOR |>";
            case TokenType::OP_RANGE: return "OPERATOR ..";
            case TokenType::OP_ARROW: return "OPERATOR ->";
            case TokenType::OP_ELLIPSIS: return "OPERATOR ...";
            case TokenType::OP_QUEST: return "OPERATOR ?";
            case TokenType::OP_COLON: return "OPERATOR :";
            
            default: return "UNKNOWN";
        }
}


static const std::unordered_map<std::string, TokenType> keyword_map = {
    {"make", TokenType::KW_MAKE},
    {"const", TokenType::KW_CONST},
    {"if", TokenType::KW_IF},
    {"elif", TokenType::KW_ELIF},
    {"else", TokenType::KW_ELSE},
    {"do", TokenType::KW_DO},
    {"while", TokenType::KW_WHILE},
    {"for", TokenType::KW_FOR},
    {"in", TokenType::KW_IN},
    {"step", TokenType::KW_STEP},
    {"break", TokenType::KW_BREAK},
    {"continue", TokenType::KW_CONTINUE},
    {"func", TokenType::KW_FUNC},
    {"return", TokenType::KW_RETURN},
    {"when", TokenType::KW_WHEN},
    {"try", TokenType::KW_TRY},
    {"catch", TokenType::KW_CATCH},
    {"finally", TokenType::KW_FINALLY},
    {"throw", TokenType::KW_THROW},
    {"use", TokenType::KW_USE},
    {"from", TokenType::KW_FROM},
    {"as", TokenType::KW_AS},
    {"class", TokenType::KW_CLASS},
    {"this", TokenType::KW_THIS},
    {"extends", TokenType::KW_EXTENDS},
    {"private", TokenType::KW_PRIVATE},
    {"protected", TokenType::KW_PROTECTED},
    {"public", TokenType::KW_PUBLIC},
    {"static", TokenType::KW_STATIC},
    {"getter", TokenType::KW_GETTER},
    {"setter", TokenType::KW_SETTER},
    {"match", TokenType::KW_MATCH},
    {"case", TokenType::KW_CASE},
    {"default", TokenType::KW_DEFAULT},
    {"test", TokenType::KW_TEST},
    {"assert", TokenType::KW_ASSERT},
    
    {"null", TokenType::LIT_NULL},
    {"true", TokenType::LIT_BOOL},
    {"false", TokenType::LIT_BOOL},
};


static const std::unordered_map<std::string, TokenType> operator_map = {
    {"=", TokenType::OP_ASSIGN},
    {"+=", TokenType::OP_PLUS_ASSIGN},
    {"-=", TokenType::OP_MINUS_ASSIGN},
    {"*=", TokenType::OP_MUL_ASSIGN},
    {"/=", TokenType::OP_DIV_ASSIGN},
    {"^=", TokenType::OP_POW_ASSIGN},
    {"%=", TokenType::OP_MOD_ASSIGN},
    {"//=", TokenType::OP_INT_DIV_ASSIGN},
    {"+", TokenType::OP_PLUS},
    {"-", TokenType::OP_MINUS},
    {"*", TokenType::OP_MUL},
    {"/", TokenType::OP_DIV},
    {"//", TokenType::OP_INT_DIV},
    {"^", TokenType::OP_POW},
    {"%", TokenType::OP_MOD},
    {"==", TokenType::OP_EQ},
    {"!=", TokenType::OP_NE},
    {"<", TokenType::OP_LT},
    {">", TokenType::OP_GT},
    {"<=", TokenType::OP_LE},
    {">=", TokenType::OP_GE},
    {"&", TokenType::OP_AND},
    {"|", TokenType::OP_OR},
    {"!", TokenType::OP_NOT},
    {".", TokenType::OP_DOT},
    {"?:", TokenType::OP_ELVIS},
    {"?.", TokenType::OP_SAFE_NAV},
    {"|>", TokenType::OP_PIPE},
    {"..", TokenType::OP_RANGE},
    {"->", TokenType::OP_ARROW},
    {"...", TokenType::OP_ELLIPSIS},
    {"?", TokenType::OP_QUEST},
    {":", TokenType::OP_COLON},
};


static const std::unordered_map<std::string, TokenType> punctuation_map = {
    {"(", TokenType::PAREN_L},
    {")", TokenType::PAREN_R},
    {"{", TokenType::BRACE_L},
    {"}", TokenType::BRACE_R},
    {"[", TokenType::BRACKET_L},
    {"]", TokenType::BRACKET_R},
    {";", TokenType::SEMICOLON},
    {",", TokenType::COMMA},
};


#endif