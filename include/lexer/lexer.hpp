#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

#include <string>
#include <vector>


class ErrorManager;
class SourceManager;


class FiniteAutomaton {
protected:
    enum class StateList {
        START,
        ERROR,
        IN_NUMBER,
        IN_NUMBER_DOT,
        IN_NUMBER_FRACTION,
        IN_STRING,
        IN_IDENTIFIER,
        IN_OPERATOR,
        IN_COMMENT_LINE,
        IN_COMMENT_BLOCK,
    };

    StateList state;
    std::vector<Token> tokens;
    std::string buffer;
    
    size_t line;
    size_t column;
    
    size_t line_idx = 0;
    size_t col_idx = 0;

    ErrorManager& error_manager;
    SourceManager& source_manager;
    const std::vector<std::string>& lines;
    std::string filename;
    bool flag_run;

    FiniteAutomaton(ErrorManager& error_manager, SourceManager& source_manager,
        const std::vector<std::string>& lines, const std::string& filename);

    void add_simvol(char simvol);

    void add_token(TokenType type, size_t start_line, size_t start_column);
    
    void error(const std::string& msg);

    char next();
    void retreat();
    char peek(size_t i);

    bool is_operator_char(char c);
    bool is_bracket_char(char c);
    bool is_punctuation_char(char c);
};


class Lexer : public FiniteAutomaton {
public:
    Lexer(const std::vector<std::string>& lines, 
        const std::string& filename, ErrorManager& error_manager, 
            SourceManager& source_manager);

    std::vector<Token> get_tokens();

private:
    void tokenize();

    void handlerSTART(char c, size_t& sl, size_t& sc);
    void handlerIN_IDENTIFIER(char c, size_t sl, size_t sc);
    void handlerIN_NUMBER(char c, size_t sl, size_t sc);
    void handlerIN_NUMBER_DOT(char c, size_t sl, size_t sc);
    void handlerIN_NUMBER_FRACTION(char c, size_t sl, size_t sc);
    void handlerIN_STRING(char c, size_t sl, size_t sc);
    void handlerIN_COMMENT_LINE(char c, size_t sl, size_t sc);
    void handlerIN_COMMENT_BLOCK(char c, size_t sl, size_t sc);
    void handlerIN_OPERATOR(char c, size_t sl, size_t sc);
    void handlerEND(size_t sl, size_t sc);
    
    void process_identifier(size_t sl, size_t sc);
    void process_operator(size_t sl, size_t sc);
};

#endif

