#ifndef PARSER
#define PARSER

#include <iostream>
#include <memory>
#include <stdexcept>

#include "ast.hpp"
#include "lexer.hpp"


class ParserBase{
public:
    ParserBase(std::vector<Token>&& tokens) : 
        tokens(std::move(tokens)), pos_tokens(0) {}

protected:
    std::vector<Token> tokens;
    size_t pos_tokens;

    bool is_end() const {
        if (pos_tokens >= tokens.size()) {
            return true;
        }
        return tokens[pos_tokens].get_type() == TokenType::END_OF_FILE;
    }

    const Token& current() const {
        if(is_end()) return tokens.back();
        return tokens[pos_tokens];
    }

    const Token& peek(size_t n = 0) const {
        if(is_end() || tokens.size() <= pos_tokens + n) {
            return tokens.back();
        }
        return tokens[pos_tokens + n];
    }

    const Token& advance() {
        if(!is_end()) ++pos_tokens;
        return tokens[pos_tokens - 1];
    }

    bool match(TokenType type) {
        if(current().get_type() == type) {
            advance();
            return true;
        }
        return false;
    }

    const Token& consume(TokenType type, const std::string& msg) {
        if(current().get_type() == type) {
            return advance();
        }
        error(msg);
        return current();
    }

    void error(const std::string& msg) {
        throw std::runtime_error(msg + " в " + 
            std::to_string(current().get_line()) + ":" + 
                std::to_string(current().get_column()));
    }
};


class Parser : public ParserBase{
public:
    Parser(std::vector<Token>&& tokens) : ParserBase(std::move(tokens)) {}

    std::unique_ptr<ProgramNode> parse(bool cout_ast) {
        auto program = std::make_unique<ProgramNode>();
        while (!is_end()) {
            program->statements.push_back(parse_statement());
        }
        if(cout_ast) save_ast_to_file("ast.txt");
        return program;
    }

private:
    void save_ast_to_file(const std::string& filename) const {}

    std::unique_ptr<StatementNodeAST> parse_statement() {
        if(match(TokenType::KW_MAKE)) return parse_make();
        return std::unique_ptr<StatementNodeAST>();
    }

    enum class Priorities {
        NONE = 0,
        ASSIGN = 10, // =, +=, -= ...
        LOGICAL_OR = 20, // |
        LOGICAL_AND = 30, // &
        EQUALS = 40, // ==, !=
        COMPARE = 50, // <, >, <=, >=
        SUM = 60, // +, -
        PRODUCT = 70, // *, /, //, %
        POW = 80, // ^
        UNARY = 90, // -, ! (в префиксах)
        CALL = 100 // . (доступ)
    };

    int get_priority(TokenType type) const {
        switch (type){
            case TokenType::OP_PLUS: case TokenType::OP_MINUS:
                return static_cast<int>(Priorities::SUM);
            case TokenType::OP_MUL: case TokenType::OP_DIV:
            case TokenType::OP_INT_DIV: case TokenType::OP_MOD:
                return static_cast<int>(Priorities::PRODUCT);            
            default:
                return static_cast<int>(Priorities::NONE);
        }
    };

    std::unique_ptr<ExpressionNodeAST> parse_expression(int priority) {
        auto left = get_prefix();
        while (get_priority(current().get_type()) > priority) {
            TokenType op = current().get_type();
            int new_priority = get_priority(op);
            advance();

            if (op == TokenType::OP_POW || 
                (op >= TokenType::OP_ASSIGN && 
                    op <= TokenType::OP_INT_DIV_ASSIGN)){
                        --new_priority;
            }

            auto right = parse_expression(new_priority);
            left = std::make_unique<BinaryOperationNodeAST>(
                std::move(left), op, std::move(right));
        }
        return left;
    }

    std::unique_ptr<ExpressionNodeAST> get_prefix() {
        if(match(TokenType::LIT_INT) || match(TokenType::LIT_BOOL) || 
            match(TokenType::LIT_DOUBLE) || match(TokenType::LIT_NULL) || 
                match(TokenType::LIT_STR)) {
                    return std::make_unique<LiteralNodeAST>(
                        peek(-1).get_value());
                }

        if(match(TokenType::IDENTIFIER)) {
            return std::make_unique<IdentifierNodeAST>(peek(-1).get_value());
        }

        if (match(TokenType::OP_NOT) || match(TokenType::OP_MINUS)) {
            TokenType op = peek(-1).get_type();
            auto operand = parse_expression(
                static_cast<int>(Priorities::UNARY));
            return std::make_unique<UnaryOperationNodeAST>(
                op, std::move(operand));
        }

        if (match(TokenType::PAREN_L)) {
            auto expr = parse_expression(static_cast<int>(Priorities::NONE));
            if (!match(TokenType::PAREN_R)) {
                error("Ожидалась закрывающая скобка ')' после выражения");
            }
            return expr;
        }

        error("Ожидалось выражение");
        return nullptr;
    }

    std::unique_ptr<StatementNodeAST> parse_make() {
        bool is_const = match(TokenType::KW_CONST);

        std::vector<std::string> names;
        std::vector<std::string> type_names;
        do{
            names.push_back(consume(TokenType::IDENTIFIER, 
                "Отсутствует идентификатор").get_value());
            std::string type_name_current("auto");
            if(match(TokenType::OP_ARROW)) {
                type_name_current = consume(TokenType::IDENTIFIER, 
                    "Ожидался идентификатор типа после '->'").get_value();
            }
            type_names.push_back(type_name_current);
        } while (match(TokenType::COMMA));

        std::vector<std::unique_ptr<ExpressionNodeAST>> initializers;
        if(match(TokenType::OP_ASSIGN)) {
            do{
                initializers.push_back(
                    parse_expression(static_cast<int>(Priorities::NONE)));
            } while (match(TokenType::COMMA));
        }

        consume(TokenType::SEMICOLON, "Ожидалась ';'");
        if (!initializers.empty() && names.size() != initializers.size()) {
            error("Количество переменных (" 
                + std::to_string(names.size()) + 
                    ") не совпадает с количеством значений (" + 
                        std::to_string(initializers.size()) + ")");
        }
        
        return std::make_unique<MakeNodeAST>(
            std::move(names), std::move(type_names), 
            std::move(initializers), is_const);
    }
};

#endif