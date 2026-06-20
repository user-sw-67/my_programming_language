#include "../../include/parser/parser.hpp"
#include "../../include/addition/program_manager.hpp"

#include <vector>
#include <string>
#include <memory>

ParserBase::ParserBase(const std::vector<Token>& tokens, 
    const std::string& filename, Managers& managers) : 
            tokens(tokens), filename(filename), 
                pos_tokens(0), managers(managers) {}

bool ParserBase::is_end() const {
    if (pos_tokens >= tokens.size()) {
        return true;
    }
    return tokens[pos_tokens].get_type() == TokenType::END_OF_FILE;
}

const Token& ParserBase::current() const {
    if(is_end()) return tokens.back();
    return tokens[pos_tokens];
}

const Token& ParserBase::peek(size_t n) const {
    if(is_end() || tokens.size() <= pos_tokens + n) {
        return tokens.back();
    }
    return tokens[pos_tokens + n];
}

const Token& ParserBase::advance() {
    if(!is_end()) {
        TokenType consumed = tokens[pos_tokens].get_type();
        ++pos_tokens;
        if (consumed == TokenType::BRACE_L) ++brace_depth;
        else if (consumed == TokenType::BRACE_R) --brace_depth;
    }
    return tokens[pos_tokens - 1];
}

bool ParserBase::match(TokenType type) {
    if(current().get_type() == type) {
        advance();
        return true;
    }
    return false;
}

const Token& ParserBase::consume(TokenType type, const std::string& err_msg,
    const std::string& code) {
        if(current().get_type() == type) {
            return advance();
        }
        error(err_msg, code);
        return current();
}

void ParserBase::error(const std::string& msg, const std::string& code) {
    managers.error.add(msg, get_loc(current()), Severity::ERROR, code);
    throw ParseError();
}

SourceLocation ParserBase::get_loc(const Token& token) {
    return SourceLocation(token.get_line(), token.get_column(), filename);
}

Parser::Parser(const std::vector<Token>& tokens, const std::string& filename, 
    Managers& managers) : 
        ParserBase(tokens, filename, managers) {}

bool Parser::is_sync_point(TokenType type) const {
    switch (type) {
        case TokenType::KW_CLASS:
        case TokenType::KW_FUNC:
        case TokenType::KW_USE:
        case TokenType::KW_TEST:
        case TokenType::KW_MAKE:
        case TokenType::KW_FOR:
        case TokenType::KW_WHILE:
        case TokenType::KW_DO:
        case TokenType::KW_IF:
        case TokenType::KW_RETURN:
        case TokenType::KW_MATCH:
        case TokenType::KW_TRY:
        case TokenType::KW_THROW:
        case TokenType::KW_ASSERT:
        case TokenType::KW_BREAK:
        case TokenType::KW_CONTINUE:
        case TokenType::BRACE_L:
            return true;
        default:
            return false;
    }
}

void Parser::synchronize(bool in_block, int target_depth) {
    if (in_block && !is_end() &&
        peek().get_type() == TokenType::BRACE_R &&
        brace_depth == target_depth) {
        return;
    }

    advance();

    while (!is_end()) {
        if (peek(-1).get_type() == TokenType::SEMICOLON) return;

        if (peek().get_type() == TokenType::BRACE_R) {
            if (in_block && brace_depth == target_depth) return;
        } else if (is_sync_point(peek().get_type())) {
            return;
        }
        advance();
    }
}

std::unique_ptr<ProgramNode> Parser::parse() {
    auto program = std::make_unique<ProgramNode>(
        SourceLocation(0, 0, filename));

    while (!is_end()) {
        try{
            if(match(TokenType::KW_CLASS)){
                program->statements.push_back(parse_class());
            } else if (match(TokenType::KW_MAKE)){
                program->statements.push_back(parse_make(false));
            } else if (match(TokenType::KW_USE)){
                program->statements.push_back(parse_use());
            } else if (match(TokenType::KW_FUNC)){
                program->statements.push_back(parse_func());
            } else if (match(TokenType::KW_TEST)){
                program->statements.push_back(parse_test());
            } else {
                error("Исполняемый код вне функций запрещен. "
                "Разрешены только объявления (use, func, class, make, test).",
                    error_code::PAR_1001);
            }
        }catch(const ParseError&){
            synchronize();
        }
    }
    return program;
}

int Parser::get_priority(TokenType type) const {
    switch (type) {
        case TokenType::PAREN_L: case TokenType::OP_DOT: 
        case TokenType::OP_SAFE_NAV:
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
        case TokenType::OP_ELVIS:
            return static_cast<int>(Priorities::ELVIS);
        case TokenType::OP_PIPE:
            return static_cast<int>(Priorities::PIPE);
        case TokenType::OP_ASSIGN: case TokenType::OP_PLUS_ASSIGN:
        case TokenType::OP_MINUS_ASSIGN: case TokenType::OP_MUL_ASSIGN:
        case TokenType::OP_DIV_ASSIGN: case TokenType::OP_INT_DIV_ASSIGN:
        case TokenType::OP_MOD_ASSIGN: case TokenType::OP_POW_ASSIGN:
            return static_cast<int>(Priorities::ASSIGN);
        default:
            return static_cast<int>(Priorities::NONE);
    }
}

std::unique_ptr<ExpressionNodeAST> Parser::get_prefix() {
    if(match(TokenType::LIT_INT) || match(TokenType::LIT_BOOL) || 
        match(TokenType::LIT_DOUBLE) || match(TokenType::LIT_NULL) || 
            match(TokenType::LIT_STR)) {
                return std::make_unique<LiteralNodeAST>(
                    peek(-1).get_value(), peek(-1).get_type(), 
                    get_loc(peek(-1)));
            }
                
    if(match(TokenType::IDENTIFIER)) {
        const Token& token = peek(-1);
        std::string name = token.get_value();
        return std::make_unique<IdentifierNodeAST>(name, get_loc(token));
    }

    if (match(TokenType::OP_NOT) || match(TokenType::OP_MINUS)) {
        const Token& token = peek(-1);
        TokenType op = token.get_type();
        auto operand = parse_expression(
            static_cast<int>(Priorities::UNARY));
        return std::make_unique<UnaryOperationNodeAST>(
            op, std::move(operand), get_loc(token));
    }

    if (match(TokenType::PAREN_L)) {
        auto expr = parse_expression(static_cast<int>(Priorities::NONE));
        if (!match(TokenType::PAREN_R)) {
            error("Ожидалась закрывающая скобка ')' после выражения",
                error_code::PAR_2001);
        }
        return expr;
    }

    error("Ожидалось выражение", error_code::PAR_2002);
    return nullptr;
}

std::unique_ptr<StatementNodeAST> Parser::parse_statement() {
    if(current().get_type() == TokenType::BRACE_L) return parse_block();
    if(match(TokenType::KW_MAKE)) return parse_make();
    if(match(TokenType::KW_IF)) return parse_if();
    if(match(TokenType::KW_FUNC)) error("Объявления функций разрешены только "
        "в глобальной области видимости или в классе", error_code::PAR_1002);
    if(match(TokenType::KW_RETURN)) return parse_return();
    if(match(TokenType::KW_WHILE)) return parse_while(false);
    if(match(TokenType::KW_DO)) return parse_while(true);
    if(match(TokenType::KW_FOR)) return parse_for();
    if(match(TokenType::KW_TRY)) return parse_try();
    if(match(TokenType::KW_THROW)) return parse_throw();
    if(match(TokenType::KW_MATCH)) return parse_match();
    if(match(TokenType::KW_USE)) error(
        "usе-импорты разрешены только в глобальной области видимости",
            error_code::PAR_1003);
    if(match(TokenType::KW_CLASS)) error(
        "Объявления классов разрешены только в глобальной области видимости",
            error_code::PAR_1004);
    if(match(TokenType::KW_TEST)) error(
        "Объявления тестов разрешены только в глобальной области видимости",
            error_code::PAR_1005);
    if(match(TokenType::KW_ASSERT)) return parse_assert();
    if (match(TokenType::KW_BREAK)) {
        SourceLocation break_loc = get_loc(peek(-1));
        consume(TokenType::SEMICOLON, "Ожидалась ';' после break",
            error_code::PAR_2003);
        return std::make_unique<BreakNodeAST>(break_loc);
    }
    if (match(TokenType::KW_CONTINUE)) {
        SourceLocation continue_loc = get_loc(peek(-1));
        consume(TokenType::SEMICOLON, "Ожидалась ';' после continue",
            error_code::PAR_2004);
        return std::make_unique<ContinueNodeAST>(continue_loc);
    }

    auto expr = parse_expression(static_cast<int>(Priorities::NONE));
    auto loc = expr->location;
    consume(TokenType::SEMICOLON, "Ожидалась ';' после выражения",
        error_code::PAR_2005);
    return std::make_unique<ExpressionStatementNodeAST>(
        std::move(expr), loc);
}

std::unique_ptr<ExpressionNodeAST> Parser::parse_expression(int priority) {
    auto left = get_prefix();
    SourceLocation loc = left->location;
    while (get_priority(current().get_type()) > priority) {
        TokenType op = current().get_type();
        int new_priority = get_priority(op);
        
        if (op == TokenType::PAREN_L) {
            advance();
            std::vector<std::unique_ptr<ExpressionNodeAST>> args;
            if(current().get_type() != TokenType::PAREN_R){
                do {
                    auto arg = parse_expression(
                        static_cast<int>(Priorities::NONE));
                    args.push_back(std::move(arg));
                } while (match(TokenType::COMMA));
            }
            consume(TokenType::PAREN_R, "Ожидалась закрывающая скобка ')'",
                error_code::PAR_2006);
            left = std::make_unique<CallOperationNodeAST>(
                std::move(left), std::move(args), loc);
            continue;
        }

        advance();

        if (op == TokenType::OP_POW || 
            (op >= TokenType::OP_ASSIGN && 
                op <= TokenType::OP_INT_DIV_ASSIGN)){
                    --new_priority;
        }

        if (op == TokenType::OP_RANGE) {
            auto right = parse_expression(new_priority);
            std::unique_ptr<ExpressionNodeAST> step = nullptr;
            if (match(TokenType::KW_STEP)){
                step = parse_expression(static_cast<int>(Priorities::NONE));
            }
            left = std::make_unique<RangeOperationNodeAST>(
                std::move(left), std::move(right), std::move(step), loc);
            continue;
        }

        if (op == TokenType::OP_QUEST) {
            auto true_expr = parse_expression(
                static_cast<int>(Priorities::NONE));
            consume(TokenType::OP_COLON,
                "Ожидалось ':' в тернарном операторе", error_code::PAR_2007);
            auto false_expr = parse_expression(
                static_cast<int>(Priorities::TERNARY) - 1);
            left = std::make_unique<TernaryOperationNodeAST>(
                std::move(left), std::move(true_expr), 
                std::move(false_expr), loc);
            continue;
        }

        auto right = parse_expression(new_priority);
        left = std::make_unique<BinaryOperationNodeAST>(
            std::move(left), op, std::move(right), loc);
    }
    return left;
}

std::unique_ptr<StatementNodeAST> Parser::parse_block() {
    SourceLocation loc = get_loc(current());
    auto block = std::make_unique<BlockNodeAST>(loc);
    consume(TokenType::BRACE_L, "Ожидалась '{' в начале блока",
        error_code::PAR_1006);
    int my_depth = brace_depth;

    while (!is_end() && current().get_type() != TokenType::BRACE_R) {
        try {
            auto stmt = parse_statement();
            if (stmt) {
                block->add_statement(std::move(stmt));
            }
        } catch (const ParseError&) {
            synchronize(true, my_depth);
        }
    }

    consume(TokenType::BRACE_R, "Ожидалась '}' в конце блока",
        error_code::PAR_1007);
    return block;
}

std::unique_ptr<StatementNodeAST> Parser::parse_make(bool in_class) {
    SourceLocation loc(0, 0);
    if(!in_class){
        loc = get_loc(peek(-1));
    }
    bool is_const = match(TokenType::KW_CONST);

    std::vector<std::string> names;
    std::vector<std::string> type_names;
    do{
        names.push_back(consume(TokenType::IDENTIFIER,
            "Отсутствует идентификатор (имя переменной)",
                error_code::PAR_3001).get_value());
        if(in_class && loc == SourceLocation(0, 0)){
            loc = get_loc(peek(-1));
        }
        std::string type_name_current("auto");
        if(match(TokenType::OP_ARROW)) {
            type_name_current = consume(TokenType::IDENTIFIER,
                "Ожидался идентификатор типа после '->'",
                    error_code::PAR_3002).get_value();
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

    if (!in_class && is_const && initializers.empty()) {
        error("Константа должна быть инициализирована", error_code::PAR_3003);
    }

    consume(TokenType::SEMICOLON, "Ожидалась ';'", error_code::PAR_3004);
    if (!initializers.empty() && names.size() != initializers.size()) {
        error("Количество переменных ("
            + std::to_string(names.size()) +
                ") не совпадает с количеством значений (" +
                    std::to_string(initializers.size()) + ")",
                        error_code::PAR_3005);
    }

    return std::make_unique<MakeNodeAST>(
        std::move(names), std::move(type_names), 
        std::move(initializers), is_const, loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_if() {
    SourceLocation loc = get_loc(peek(-1));
    consume(TokenType::PAREN_L, "Ожидается условие в '()'",
        error_code::PAR_5001);
    std::unique_ptr<ExpressionNodeAST> condition =
        parse_expression(static_cast<int>(Priorities::NONE));
    consume(TokenType::PAREN_R, "Ожидается закрывающая ')'",
        error_code::PAR_5002);

    std::unique_ptr<StatementNodeAST> then_branch = parse_block();
    std::unique_ptr<StatementNodeAST> else_branch = nullptr;
    if(match(TokenType::KW_ELIF)) {
        else_branch = parse_if();
    } else if(match(TokenType::KW_ELSE)) {
        else_branch = parse_block();
    }

    return std::make_unique<IfElseNodeAST>(std::move(condition), 
        std::move(then_branch), std::move(else_branch), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_func(bool in_class) {
    SourceLocation loc;
    if(!in_class){
        loc = get_loc(peek(-1));
    }
    std::string name = consume(
        TokenType::IDENTIFIER,
            "Ожидается идентификатор (имя функции)",
                error_code::PAR_4001).get_value();
    if(in_class) {
        loc = get_loc(peek(-1));
    }
    consume(TokenType::PAREN_L, "Ожидается '(' после идентификатора",
        error_code::PAR_4002);

    std::vector<Parameter> parameters;
    bool is_active_def = false;
    uint8_t count_elem_default = 0;
    if(!match(TokenType::PAREN_R)) {
        do{
            bool is_variadic = match(TokenType::OP_ELLIPSIS);
            if(is_variadic){
                const Token& par = consume(TokenType::IDENTIFIER,
                    "Ожидалось имя параметра", error_code::PAR_4003);
                std::string par_name = par.get_value();
                if(match(TokenType::OP_ARROW)) {
                    error("Параметр ..." + par_name + " не может иметь типа",
                        error_code::PAR_4004);
                }
                if(match(TokenType::OP_ASSIGN)){
                    error("Параметр ..." + par_name +
                        " не может иметь значения по умолчанию",
                            error_code::PAR_4005);
                }
                parameters.emplace_back(par_name, "auto",
                    nullptr, is_variadic, get_loc(par));
                if (current().get_type() != TokenType::PAREN_R) {
                    error("..." + par_name + " должен быть последним в списке",
                        error_code::PAR_4006);
                }
                break;
            } else {
                const Token& par = consume(TokenType::IDENTIFIER,
                    "Ожидалось имя параметра", error_code::PAR_4007);
                std::string par_name = par.get_value();
                std::string par_type("auto");
                if(match(TokenType::OP_ARROW)) {
                    par_type = consume(TokenType::IDENTIFIER,
                        "Ожидался тип параметра после '->'",
                            error_code::PAR_4008).get_value();
                }
                std::unique_ptr<ExpressionNodeAST> par_default_val = nullptr;
                if(match(TokenType::OP_ASSIGN)){
                    par_default_val = parse_expression(
                        static_cast<int>(Priorities::NONE));
                }
                if(!par_default_val && is_active_def){
                    error("Параметры со значением по умолчанию должны "
                        "идти в конце", error_code::PAR_4009);
                }
                if(par_default_val && !is_active_def) is_active_def = true;
                if(par_default_val) ++count_elem_default;
                parameters.emplace_back(par_name, par_type, 
                    std::move(par_default_val), is_variadic, get_loc(par));
            }
        } while (match(TokenType::COMMA));
        consume(TokenType::PAREN_R, "Ожидается закрывающая ')'",
            error_code::PAR_4010);
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
        consume(TokenType::PAREN_L, "Ожидалась '(' после when",
            error_code::PAR_4011);
        when_condition = parse_expression(
            static_cast<int>(Priorities::NONE));
        consume(TokenType::PAREN_R, "Ожидалась ')' после условия when",
            error_code::PAR_4012);
    }

    std::unique_ptr<StatementNodeAST> body;
    if(match(TokenType::OP_ARROW)){
        SourceLocation arrow_loc = get_loc(peek(-1));
        auto expr = parse_expression(static_cast<int>(Priorities::NONE));
        consume(TokenType::SEMICOLON, "Ожидалась ';' после выражения",
            error_code::PAR_4013);
        body = std::make_unique<ReturnNodeAST>(std::move(expr), arrow_loc);
    } else {
        body = parse_block();
    }

    return std::make_unique<FunctionNodeAST>(name, return_type,
        std::move(parameters), std::move(when_condition), 
        std::move(body), count_elem_default, loc);            
}

std::unique_ptr<StatementNodeAST> Parser::parse_return() {
    SourceLocation loc = get_loc(peek(-1));
    std::unique_ptr<ExpressionNodeAST> value = nullptr;
    if(!match(TokenType::SEMICOLON)){
        value = parse_expression(static_cast<int>(Priorities::NONE));
        consume(TokenType::SEMICOLON, "Ожидалась ';'", error_code::PAR_5003);
    }
    return std::make_unique<ReturnNodeAST>(std::move(value), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_while(bool is_do_while) {
    SourceLocation loc = get_loc(peek(-1));
    std::unique_ptr<StatementNodeAST> body;
    std::unique_ptr<ExpressionNodeAST> condition;

    if(is_do_while){
        body = parse_block();
        consume(TokenType::KW_WHILE, "Ожидается 'while'", error_code::PAR_5004);
        consume(TokenType::PAREN_L, "Ожидалась '(' после while",
            error_code::PAR_5005);
        condition = parse_expression(
                static_cast<int>(Priorities::NONE));
        consume(TokenType::PAREN_R, "Ожидалась ')'", error_code::PAR_5006);
        consume(TokenType::SEMICOLON, "Ожидалась ';'", error_code::PAR_5007);
    } else {
        consume(TokenType::PAREN_L, "Ожидалась '(' после while",
            error_code::PAR_5008);
        condition = parse_expression(
                static_cast<int>(Priorities::NONE));
        consume(TokenType::PAREN_R, "Ожидалась ')'", error_code::PAR_5009);
        body = parse_block();
    }

    return std::make_unique<WhileNodeAST>(std::move(condition), 
        std::move(body), is_do_while, loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_for() {
    SourceLocation loc = get_loc(peek(-1));
    consume(TokenType::PAREN_L, "Ожидалась '(' после for", error_code::PAR_5010);
    std::string name_var = consume(TokenType::IDENTIFIER,
        "Ожидается идентификатор", error_code::PAR_5011).get_value();
    consume(TokenType::KW_IN, "Ожидается 'in'", error_code::PAR_5012);
    auto iterable = parse_expression(static_cast<int>(Priorities::NONE));
    consume(TokenType::PAREN_R, "Ожидалась ')'", error_code::PAR_5013);
    auto body = parse_block();
    return std::make_unique<ForNodeAST>(name_var, 
        std::move(iterable), std::move(body), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_try() {
    SourceLocation loc = get_loc(peek(-1));
    auto try_block = parse_block();

    consume(TokenType::KW_CATCH, "Необходим блок 'catch'",
        error_code::PAR_5014);
    consume(TokenType::PAREN_L, "Ожидалась '(' после catch",
        error_code::PAR_5015);
    auto catch_expr = parse_expression(static_cast<int>(Priorities::NONE));
    consume(TokenType::PAREN_R, "Ожидалась ')'", error_code::PAR_5016);
    auto catch_block = parse_block();

    std::unique_ptr<StatementNodeAST> finally_block = nullptr;
    if(match(TokenType::KW_FINALLY)){
        finally_block = parse_block();
    }

    return std::make_unique<TryNodeAST>(std::move(try_block), 
        std::move(catch_expr), std::move(catch_block), 
            std::move(finally_block), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_throw() {
    SourceLocation loc = get_loc(peek(-1));
    std::unique_ptr<ExpressionNodeAST> value = nullptr;
    if(!match(TokenType::SEMICOLON)){
        value = parse_expression(static_cast<int>(Priorities::NONE));
        consume(TokenType::SEMICOLON, "Ожидалась ';'", error_code::PAR_5017);
    }
    return std::make_unique<ThrowNodeAST>(std::move(value), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_use() {
    SourceLocation loc = get_loc(peek(-1));
    std::string path_lib;
    std::vector<ImportObject> objects;
    bool is_build_in = false;

    if(match(TokenType::BRACE_L)){
        do{
            const Token& token = consume(TokenType::IDENTIFIER,
                "Ожидается идентификатор объекта", error_code::PAR_6001);
            std::string internal_name = token.get_value();
            std::string alias("");
            if(match(TokenType::KW_AS)){
                alias = consume(TokenType::IDENTIFIER,
                    "Ожидается новый идентификатор объекта",
                        error_code::PAR_6002).get_value();
            }
            objects.emplace_back(internal_name, alias, get_loc(token));
        } while (match(TokenType::COMMA));
        consume(TokenType::BRACE_R, "Ожидалась '}'", error_code::PAR_6003);
        consume(TokenType::KW_FROM, "Требуется 'from'", error_code::PAR_6004);
        path_lib = consume(TokenType::LIT_STR,
            "Требуется имя файла", error_code::PAR_6005).get_value();
    } else {
        path_lib = consume(TokenType::LIT_STR,
            "Требуется имя файла", error_code::PAR_6006).get_value();
    }

    consume(TokenType::SEMICOLON, "Ожидалась ';'", error_code::PAR_6009);

    std::string path_lib_canonical;
    if (!path_lib.empty() && path_lib[0] == '@') {
        path_lib_canonical = path_lib.erase(0, 1);
        is_build_in = true;
    }
    if(!is_build_in){
        path_lib_canonical = managers.source.resolve_canonical_path(
            path_lib, filename);
        if(path_lib_canonical.empty()){
            error("Не удалось разрешить путь импорта: " + path_lib_canonical,
                error_code::PAR_6007);
        }
        try {
            managers.source.load_file(path_lib_canonical);
        } catch (const PreparationError& e) {
            error(e.what(), error_code::PAR_6008);
        }
    }

    return std::make_unique<UseNodeAST>(
        path_lib_canonical, std::move(objects), is_build_in, loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_class() {
    SourceLocation loc = get_loc(peek(-1));
    std::string name = consume(TokenType::IDENTIFIER,
        "Ожидается имя класса", error_code::PAR_7001).get_value();
    std::string base_class_name;
    if(match(TokenType::KW_EXTENDS)){
        base_class_name = consume(TokenType::IDENTIFIER,
        "Ожидается имя класса наследника", error_code::PAR_7002).get_value();
    }
    consume(TokenType::BRACE_L, "Ожидается тело класса '{'",
        error_code::PAR_7003);

    std::vector<ClassMember> members;

    while (!match(TokenType::BRACE_R)) {

        std::string access_modifier = "public";
        bool is_static = false;

        while(true){
            if (match(TokenType::KW_STATIC)) {
                is_static = true;
            } else if (match(TokenType::KW_PRIVATE)) {
                access_modifier = "private";
            } else if (match(TokenType::KW_PROTECTED)) {
                access_modifier = "protected";
            } else if (match(TokenType::KW_PUBLIC)) {
                access_modifier = "public";
            } else {
                break;
            }
        }

        if(current().get_type() == TokenType::KW_CONST) {
            auto statement_make = parse_make(true);
            auto loc = statement_make->location;
            members.emplace_back(access_modifier, is_static,
                std::move(statement_make), loc);
        } else {
            if(current().get_type() == TokenType::IDENTIFIER) {
                if(peek(1).get_type() == TokenType::PAREN_L){
                    auto func = parse_func(true);
                    auto loc = func->location;
                    members.emplace_back(access_modifier, is_static,
                        std::move(func), loc);
                } else {
                    auto statement_make = parse_make(true);
                    auto loc = statement_make->location;
                    members.emplace_back(access_modifier, is_static,
                                std::move(statement_make), loc);
                }
            } else {
                error("Ожидается идентификатор (имя метода или поля)",
                    error_code::PAR_7004);
            }
        }
    }

    return std::make_unique<ClassNodeAST>(name, base_class_name, 
        std::move(members), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_match() {
    SourceLocation loc = get_loc(peek(-1));
    std::unique_ptr<ExpressionNodeAST> value;
    std::vector<Case> cases;
    bool exists_default = false;

    consume(TokenType::PAREN_L, "Ожидалась '(' после match",
        error_code::PAR_8001);
    value = parse_expression(static_cast<int>(Priorities::NONE));
    consume(TokenType::PAREN_R, "Ожидалась ')'", error_code::PAR_8002);
    consume(TokenType::BRACE_L, "Ожидалась '{' тело match",
        error_code::PAR_8003);

    while (current().get_type() != TokenType::BRACE_R &&
        current().get_type() != TokenType::END_OF_FILE){
            if(match(TokenType::KW_CASE)){
                auto case_expr = parse_expression(static_cast<int>(
                    Priorities::NONE));
                consume(TokenType::OP_COLON, "Требуется ':'",
                    error_code::PAR_8004);
                auto body = parse_block();
                cases.emplace_back(std::move(case_expr), std::move(body),
                    body->location);

            } else if(match(TokenType::KW_DEFAULT)){
                if(exists_default) error("Допустим только один default",
                    error_code::PAR_8005);
                exists_default = true;
                consume(TokenType::OP_COLON, "Требуется ':'",
                    error_code::PAR_8006);
                auto body = parse_block();
                cases.emplace_back(nullptr, std::move(body),
                    body->location);
            } else {
                error("В match доступны блоки только case и default",
                    error_code::PAR_8007);
            }
    }

    if (cases.empty()) {
        error("match должен содержать хотя бы один case или default",
            error_code::PAR_8008);
    }
    consume(TokenType::BRACE_R, "Ожидалась '}'", error_code::PAR_8009);
    return std::make_unique<MatchNodeAST>(
        std::move(value), std::move(cases), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_test() {
    SourceLocation loc = get_loc(peek(-1));
    std::string name = consume(TokenType::IDENTIFIER,
        "Ожидается имя теста", error_code::PAR_9001).get_value();
    auto body = parse_block();
    return std::make_unique<TestNodeAST>(name, std::move(body), loc);
}

std::unique_ptr<StatementNodeAST> Parser::parse_assert() {
    SourceLocation loc = get_loc(peek(-1));
    auto value = parse_expression(static_cast<int>(Priorities::NONE));
    consume(TokenType::SEMICOLON, "Ожидалась ';'", error_code::PAR_9002);
    return std::make_unique<AssertNodeAST>(std::move(value), loc);
}
