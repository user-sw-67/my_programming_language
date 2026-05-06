#ifndef PARSER_HPP
#define PARSER_HPP

#include "../lexer/token.hpp"
#include "ast.hpp"

#include <vector>
#include <string>
#include <memory>


class ErrorManager;
class SourceManager;


class ParserBase{
public:
    ParserBase(const std::vector<Token>& tokens, 
        const std::string& filename, ErrorManager& error_manager, 
            SourceManager& source_manager);

protected:
    const std::vector<Token>& tokens;
    std::string filename;
    size_t pos_tokens;
    ErrorManager& error_manager;
    SourceManager& source_manager;

    bool is_end() const;

    const Token& current() const;

    const Token& peek(size_t n = 0) const;

    const Token& advance();

    bool match(TokenType type);

    const Token& consume(TokenType type, const std::string& msg);

    void error(const std::string& msg);

    SourceLocation get_loc(const Token& token);
};


class Parser : public ParserBase{
public:
    Parser(const std::vector<Token>& tokens, const std::string& filename, 
        ErrorManager& error_manager, SourceManager& source_manager);

    std::unique_ptr<ProgramNode> parse();

private:
    enum class Priorities {
        NONE = 0,
        ASSIGN = 10, // =, +=, -= ...
        PIPE = 20, // |> 
        ELVIS = 30, // ?:
        TERNARY = 40, // ?
        LOGICAL_OR = 50, // |
        LOGICAL_AND = 60, // &
        EQUALS = 70, // ==, !=
        COMPARE = 80, // <, >, <=, >=
        SUM = 90, // +, -
        PRODUCT = 100, // *, /, //, %
        RANGE = 110, // ..
        POW = 120, // ^
        UNARY = 130, // -, ! 
        CALL = 140 // . , ?. 
    };

    int get_priority(TokenType type) const;

    std::unique_ptr<ExpressionNodeAST> get_prefix();

    std::unique_ptr<StatementNodeAST> parse_statement();
    std::unique_ptr<ExpressionNodeAST> parse_expression(int priority);

    std::unique_ptr<StatementNodeAST> parse_block();
    std::unique_ptr<StatementNodeAST> parse_make(bool in_class = false);
    std::unique_ptr<StatementNodeAST> parse_if();
    std::unique_ptr<StatementNodeAST> parse_func(bool in_class = false);
    std::unique_ptr<StatementNodeAST> parse_return();
    std::unique_ptr<StatementNodeAST> parse_while(bool is_do_while);
    std::unique_ptr<StatementNodeAST> parse_for();
    std::unique_ptr<StatementNodeAST> parse_try();
    std::unique_ptr<StatementNodeAST> parse_throw();
    std::unique_ptr<StatementNodeAST> parse_use();
    std::unique_ptr<StatementNodeAST> parse_class();
    std::unique_ptr<StatementNodeAST> parse_match();
    std::unique_ptr<StatementNodeAST> parse_test();
    std::unique_ptr<StatementNodeAST> parse_assert();
};

#endif