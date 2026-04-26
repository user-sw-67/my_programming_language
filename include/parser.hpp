#ifndef PARSER
#define PARSER

#include <iostream>
#include <memory>
#include <stdexcept>

#include "ast.hpp"
#include "lexer.hpp"
#include "mermaid_visitor.hpp"


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
        if(cout_ast) save_ast_to_file("ast.md", program);
        return program;
    }

private:
    void save_ast_to_file(const std::string& filename, 
        const std::unique_ptr<ProgramNode>& program) const {
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка: не удалось создать файл " << 
                    filename << std::endl;
                return;
            }
            file << "```mermaid\n";
            MermaidVisitor visualizer(file);
            visualizer.start();
            program->visit(visualizer);
            file << "```\n";
            file.close();
            std::cout << "AST дерево сохранено в " << filename << std::endl;
    }

    enum class Priorities {
        NONE = 0,
        ASSIGN = 10, // =, +=, -= ...
        TERNARY = 15, // ?
        LOGICAL_OR = 20, // |
        LOGICAL_AND = 30, // &
        EQUALS = 40, // ==, !=
        COMPARE = 50, // <, >, <=, >=
        SUM = 60, // +, -
        PRODUCT = 70, // *, /, //, %
        RANGE = 75, // ..
        POW = 80, // ^
        UNARY = 90, // -, ! (в префиксах)
        CALL = 100 // . (доступ)
    };

    int get_priority(TokenType type) const {
        switch (type) {
            case TokenType::OP_DOT: 
                return static_cast<int>(Priorities::CALL);
            case TokenType::OP_POW:
                return static_cast<int>(Priorities::POW);
            case TokenType::OP_MUL: case TokenType::OP_DIV:
            case TokenType::OP_INT_DIV: case TokenType::OP_MOD:
                return static_cast<int>(Priorities::PRODUCT);
            case TokenType::OP_PLUS: case TokenType::OP_MINUS:
                return static_cast<int>(Priorities::SUM);
            case TokenType::OP_RANGE:
                return static_cast<int>(Priorities::RANGE);
            case TokenType::OP_LT: case TokenType::OP_GT:
            case TokenType::OP_LE: case TokenType::OP_GE:
                return static_cast<int>(Priorities::COMPARE);
            case TokenType::OP_EQ: case TokenType::OP_NE:
                return static_cast<int>(Priorities::EQUALS);
            case TokenType::OP_AND:
                return static_cast<int>(Priorities::LOGICAL_AND);
            case TokenType::OP_OR:
                return static_cast<int>(Priorities::LOGICAL_OR);
            case TokenType::OP_QUEST:
                return static_cast<int>(Priorities::TERNARY);
            case TokenType::OP_ASSIGN: case TokenType::OP_PLUS_ASSIGN:
            case TokenType::OP_MINUS_ASSIGN: case TokenType::OP_MUL_ASSIGN:
            case TokenType::OP_DIV_ASSIGN: case TokenType::OP_INT_DIV_ASSIGN:
            case TokenType::OP_MOD_ASSIGN: case TokenType::OP_POW_ASSIGN:
                return static_cast<int>(Priorities::ASSIGN);
            default:
                return static_cast<int>(Priorities::NONE);
        }
    }

    std::unique_ptr<ExpressionNodeAST> get_prefix() {
        if(match(TokenType::LIT_INT) || match(TokenType::LIT_BOOL) || 
            match(TokenType::LIT_DOUBLE) || match(TokenType::LIT_NULL) || 
                match(TokenType::LIT_STR)) {
                    return std::make_unique<LiteralNodeAST>(
                        peek(-1).get_value());
                }

        if(match(TokenType::IDENTIFIER)) {
            std::string name = peek(-1).get_value();
            if(match(TokenType::PAREN_L)) {
                std::vector<std::unique_ptr<ExpressionNodeAST>> args;
                if(current().get_type() != TokenType::PAREN_R){
                    do{
                        auto arg = parse_expression(
                            static_cast<int>(Priorities::NONE));
                        args.push_back(std::move(arg));
                    } while (match(TokenType::COMMA));
                }
                consume(TokenType::PAREN_R, "Ожидалась закрывающая скобка ')'");
                return std::make_unique<CallOperationNodeAST>(
                    name, std::move(args));
            }
            return std::make_unique<IdentifierNodeAST>(name);
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

    std::unique_ptr<StatementNodeAST> parse_statement() {
        if(current().get_type() == TokenType::BRACE_L) return parse_block();
        if(match(TokenType::KW_MAKE)) return parse_make();
        if(match(TokenType::KW_IF)) return parse_if();
        if(match(TokenType::KW_FUNC)) return parse_func();
        if(match(TokenType::KW_RETURN)) return parse_return();
        if(match(TokenType::KW_WHILE)) return parse_while(false);
        if(match(TokenType::KW_DO)) return parse_while(true);
        if(match(TokenType::KW_FOR)) return parse_for();
        if(match(TokenType::KW_TRY)) return parse_try();
        if(match(TokenType::KW_THROW)) return parse_throw();
        if(match(TokenType::KW_USE)) return parse_use();
        if (match(TokenType::KW_BREAK)) {
            consume(TokenType::SEMICOLON, "Ожидалась ';' после break");
            return std::make_unique<BreakNodeAST>();
        }
        if (match(TokenType::KW_CONTINUE)) {
            consume(TokenType::SEMICOLON, "Ожидалась ';' после continue");
            return std::make_unique<ContinueNodeAST>();
        }

        auto expr = parse_expression(static_cast<int>(Priorities::NONE));
        consume(TokenType::SEMICOLON, "Ожидалась ';' после выражения");
        return std::make_unique<ExpressionStatementNodeAST>(std::move(expr));
    }

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

            if (op == TokenType::OP_RANGE) {
                auto right = parse_expression(new_priority);
                left = std::make_unique<RangeNodeAST>(
                    std::move(left), std::move(right));
                continue;
            }

            if (op == TokenType::OP_QUEST) {
                auto true_expr = parse_expression(
                    static_cast<int>(Priorities::NONE));
                consume(TokenType::OP_COLON, 
                    "Ожидалось ':' в тернарном операторе");
                auto false_expr = parse_expression(
                    static_cast<int>(Priorities::TERNARY) - 1);
                left = std::make_unique<TernaryOperationNodeAST>(
                    std::move(left), std::move(true_expr), std::move(false_expr)
                );
                continue;
            }

            auto right = parse_expression(new_priority);
            left = std::make_unique<BinaryOperationNodeAST>(
                std::move(left), op, std::move(right));
        }
        return left;
    }

    std::unique_ptr<StatementNodeAST> parse_block() {
        auto block = std::make_unique<BlockNodeAST>();
        consume(TokenType::BRACE_L, "Ожидалась '{' в начале блока");

        while (!is_end() && current().get_type() != TokenType::BRACE_R) {
            block->add_statement(std::move(parse_statement()));
        }

        consume(TokenType::BRACE_R, "Ожидалась '}' в конце блока");
        return block;
    }

    std::unique_ptr<StatementNodeAST> parse_make() {
        bool is_const = match(TokenType::KW_CONST);

        std::vector<std::string> names;
        std::vector<std::string> type_names;
        do{
            names.push_back(consume(TokenType::IDENTIFIER, 
                "Отсутствует идентификатор (имя переменной)").get_value());
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

    std::unique_ptr<StatementNodeAST> parse_if() {
        consume(TokenType::PAREN_L, "Ожидается условие в '()'");
        std::unique_ptr<ExpressionNodeAST> condition = 
            parse_expression(static_cast<int>(Priorities::NONE));
        consume(TokenType::PAREN_R, "Ожидается закрывающая ')'");

        std::unique_ptr<StatementNodeAST> then_branch = parse_block();
        std::unique_ptr<StatementNodeAST> else_branch = nullptr;
        if(match(TokenType::KW_ELIF)) {
            else_branch = parse_if();
        } else if(match(TokenType::KW_ELSE)) {
            else_branch = parse_block();
        }

        return std::make_unique<IfElseNodeAST>(std::move(condition), 
            std::move(then_branch), std::move(else_branch));
    }

    std::unique_ptr<StatementNodeAST> parse_func() {
        std::string name = consume(
            TokenType::IDENTIFIER, 
                "Ожидается идентификатор (имя функции)").get_value();
        consume(TokenType::PAREN_L, "Ожидается '(' после идентификатора");

        std::vector<Parameter> parameters;
        if(!match(TokenType::PAREN_R)) {
            do{
                bool is_variadic = match(TokenType::OP_ELLIPSIS);
                std::string par_name = consume(TokenType::IDENTIFIER, 
                    "Ожидалось имя параметра").get_value();
                std::string par_type("auto");
                if(match(TokenType::OP_ARROW)) {
                    par_type = consume(TokenType::IDENTIFIER, 
                        "Ожидался тип параметра после '->'").get_value();
                }
                std::unique_ptr<ExpressionNodeAST> par_default_val = nullptr;
                if(match(TokenType::OP_ASSIGN)){
                    par_default_val = parse_expression(
                        static_cast<int>(Priorities::NONE));
                }
                parameters.emplace_back(par_name, par_type, 
                    std::move(par_default_val), is_variadic);
                if(is_variadic) break;
            } while (match(TokenType::COMMA));
            consume(TokenType::PAREN_R, "Ожидается закрывающая ')'"); 
        }

        std::string return_type("auto");
        if(current().get_type() == TokenType::OP_ARROW && 
            peek(1).get_type() == TokenType::IDENTIFIER && (
                peek(2).get_type() == TokenType::BRACE_L || 
                    peek(2).get_type() == TokenType::KW_WHEN ||
                        peek(2).get_type() == TokenType::OP_ARROW)) {
                            advance();
                            return_type = advance().get_value();
                        }

        std::unique_ptr<ExpressionNodeAST> when_condition = nullptr;
        if(match(TokenType::KW_WHEN)) {
            consume(TokenType::PAREN_L, "Ожидалась '(' после when");
            when_condition = parse_expression(
                static_cast<int>(Priorities::NONE));
            consume(TokenType::PAREN_R, "Ожидалась ')' после условия when");
        }

        std::unique_ptr<StatementNodeAST> body;
        if(match(TokenType::OP_ARROW)){
            auto expr = parse_expression(static_cast<int>(Priorities::NONE));
            consume(TokenType::SEMICOLON, "Ожидалась ';' после выражения");
            body = std::make_unique<ReturnNodeAST>(std::move(expr));
        } else {
            body = parse_block();
        }

        return std::make_unique<FunctionNodeAST>(name, return_type,
            std::move(parameters), std::move(when_condition), std::move(body));            
    }

    std::unique_ptr<StatementNodeAST> parse_return() {
        std::unique_ptr<ExpressionNodeAST> value = nullptr;
        if(!match(TokenType::SEMICOLON)){
            value = parse_expression(static_cast<int>(Priorities::NONE));
            consume(TokenType::SEMICOLON, "Ожидалась ';'");
        }
        return std::make_unique<ReturnNodeAST>(std::move(value));
    }

    std::unique_ptr<StatementNodeAST> parse_while(bool is_do_while) {
        std::unique_ptr<StatementNodeAST> body;
        std::unique_ptr<ExpressionNodeAST> condition;

        if(is_do_while){
            body = parse_block();
            consume(TokenType::KW_WHILE, "Ожидается 'while'");
            consume(TokenType::PAREN_L, "Ожидалась '(' после while");
            condition = parse_expression(
                    static_cast<int>(Priorities::NONE));
            consume(TokenType::PAREN_R, "Ожидалась ')'");
            consume(TokenType::SEMICOLON, "Ожидалась ';'");
        } else {
            consume(TokenType::PAREN_L, "Ожидалась '(' после while");
            condition = parse_expression(
                    static_cast<int>(Priorities::NONE));
            consume(TokenType::PAREN_R, "Ожидалась ')'");
            body = parse_block();
        }

        return std::make_unique<WhileNodeAST>(std::move(condition), 
            std::move(body), is_do_while);
    }

    std::unique_ptr<StatementNodeAST> parse_for() {
        consume(TokenType::PAREN_L, "Ожидалась '(' после for");
        std::string name_var = consume(TokenType::IDENTIFIER, 
            "Ожидается идентификатор").get_value();
        consume(TokenType::KW_IN, "Ожидается 'in'");
        auto iterable = parse_expression(static_cast<int>(Priorities::NONE));
        std::unique_ptr<ExpressionNodeAST> step = nullptr;
        if(match(TokenType::KW_STEP)){
            step = parse_expression(static_cast<int>(Priorities::NONE));
        }
        consume(TokenType::PAREN_R, "Ожидалась ')'");

        auto body = parse_block();
        return std::make_unique<ForNodeAST>(name_var, std::move(iterable),
            std::move(step), std::move(body));
    }

    std::unique_ptr<StatementNodeAST> parse_try() {
        auto try_block = parse_block();

        consume(TokenType::KW_CATCH, "Необходим блок 'catch'");
        consume(TokenType::PAREN_L, "Ожидалась '(' после catch");
        auto catch_expr = parse_expression(static_cast<int>(Priorities::NONE));
        consume(TokenType::PAREN_R, "Ожидалась ')'");
        auto catch_block = parse_block();

        std::unique_ptr<StatementNodeAST> finally_block = nullptr;
        if(match(TokenType::KW_FINALLY)){
            finally_block = parse_block();
        }

        return std::make_unique<TryNodeAST>(std::move(try_block), 
            std::move(catch_expr), std::move(catch_block), 
                std::move(finally_block));
    }

    std::unique_ptr<StatementNodeAST> parse_throw() {
        std::unique_ptr<ExpressionNodeAST> value = nullptr;
        if(!match(TokenType::SEMICOLON)){
            value = parse_expression(static_cast<int>(Priorities::NONE));
            consume(TokenType::SEMICOLON, "Ожидалась ';'");
        }
        return std::make_unique<ThrowNodeAST>(std::move(value));
    }

    std::unique_ptr<StatementNodeAST> parse_use() {
        std::string path_lib;
        std::vector<ImportObject> objects;
        std::string as_name("");

        if(match(TokenType::BRACE_L)){
            do{
                std::string internal_name = consume(TokenType::IDENTIFIER, 
                    "Ожидается идентификатор объекта").get_value();
                std::string alias("");
                if(match(TokenType::KW_AS)){
                    alias = consume(TokenType::IDENTIFIER, 
                        "Ожидается новый идентификатор объекта").get_value();
                }
                objects.emplace_back(internal_name, alias);
            } while (match(TokenType::COMMA));
            consume(TokenType::BRACE_R, "Ожидалась '}'");
            consume(TokenType::KW_FROM, "Требуется 'from'");
            path_lib = consume(TokenType::LIT_STR, 
                "Требуется имя файла").get_value();
        } else {
            path_lib = consume(TokenType::LIT_STR, 
                "Требуется имя файла").get_value();
            if(match(TokenType::KW_AS)){
                as_name = consume(TokenType::IDENTIFIER, 
                    "Ожидается новый псевдоним файла").get_value();
            }
        }
        consume(TokenType::SEMICOLON, "Ожидалась ';'");
        return std::make_unique<UseNodeAST>(
            path_lib, std::move(objects), as_name);
    }
};

#endif