#include "../../include/lexer/lexer.hpp"
#include "../../include/addition/error_manager.hpp"


FiniteAutomaton::FiniteAutomaton(ErrorManager& error_manager, 
    SourceManager& source_manager, const std::vector<std::string>& lines, 
        const std::string& filename) : 
            state(StateList::START), line(1), column(0), 
            error_manager(error_manager), lines(lines),
            filename(filename), flag_run(!lines.empty()),
            source_manager(source_manager) {}

void FiniteAutomaton::add_simvol(char simvol) {
    buffer += simvol;
}

void FiniteAutomaton::add_token(TokenType type, 
    size_t start_line, size_t start_column) {
        if (buffer.empty() && type != TokenType::END_OF_FILE) {
            buffer = "undefined";
        }
        tokens.emplace_back(type, 
            SourceLocation(start_line, start_column, filename), buffer);
        buffer.clear();
        state = StateList::START;
}

void FiniteAutomaton::error(const std::string& msg) {
    error_manager.add(msg, {line, column, filename}, Severity::ERROR);
    buffer.clear();
    state = StateList::START;
}

char FiniteAutomaton::next() {
    if (line_idx >= lines.size()) {
        flag_run = false;
        return '\0';
    }

    const std::string& current_line = lines[line_idx];
    if (col_idx >= current_line.size()) {
        line_idx++;
        col_idx = 0;
        line++;
        column = 0;
        return '\n';
    }

    char c = current_line[col_idx++];
    column++;
    return c;
}

void FiniteAutomaton::retreat() {
    if (line_idx == 0 && col_idx == 0) return;

    if (col_idx == 0) {
        line_idx--;
        line--;
        col_idx = lines[line_idx].size();
        column = col_idx; 
    } else {
        col_idx--;
        column--;
    }
}

char FiniteAutomaton::peek(size_t i) {
    size_t target_line = line_idx;
    size_t target_col = col_idx + i - 1;

    while (target_line < lines.size() && 
        target_col >= lines[target_line].size()) {
            target_col -= lines[target_line].size();
            target_line++;
    }

    if (target_line >= lines.size()) return '\0';
    return lines[target_line][target_col];
}

bool FiniteAutomaton::is_operator_char(char c) {
    return std::string("+-*/^%=!<>|&?:.~").find(c) != std::string::npos;
}

bool FiniteAutomaton::is_bracket_char(char c) {
    return std::string("(){}[]").find(c) != std::string::npos;
}

bool FiniteAutomaton::is_punctuation_char(char c) {
    return c == ';' || c == ',';
}

Lexer::Lexer(const std::vector<std::string>& lines, 
    const std::string& filename, ErrorManager& error_manager, 
        SourceManager& source_manager) : 
            FiniteAutomaton(error_manager, source_manager, lines, filename) {}

std::vector<Token> Lexer::get_tokens() {
    tokenize();
    return std::move(tokens);
}

void Lexer::tokenize() {
    size_t start_line = 1, start_column = 0;
    state = StateList::START;

    while (flag_run) {
        char c = next();
        if (!flag_run && c == '\0') break;
        if (state == StateList::ERROR) break;

        switch (state) {
            case StateList::START:
                handlerSTART(c, start_line, start_column);
                break;
            case StateList::IN_IDENTIFIER:
                handlerIN_IDENTIFIER(c, start_line, start_column);
                break;
            case StateList::IN_NUMBER:
                handlerIN_NUMBER(c, start_line, start_column);
                break;
            case StateList::IN_NUMBER_DOT:
                handlerIN_NUMBER_DOT(c, start_line, start_column);
                break;
            case StateList::IN_NUMBER_FRACTION:
                handlerIN_NUMBER_FRACTION(c, start_line, start_column);
                break;
            case StateList::IN_STRING:
                handlerIN_STRING(c, start_line, start_column);
                break;
            case StateList::IN_COMMENT_LINE:
                handlerIN_COMMENT_LINE(c, start_line, start_column);
                break;
            case StateList::IN_COMMENT_BLOCK:
                handlerIN_COMMENT_BLOCK(c, start_line, start_column);
                break;
            case StateList::IN_OPERATOR:
                handlerIN_OPERATOR(c, start_line, start_column);
                break;
            default: 
                break;
        }
    }
    handlerEND(start_line, start_column);
}

void Lexer::handlerSTART(char c, size_t& sl, size_t& sc) {
    if (std::isspace(c)) return;

    sl = line; 
    sc = column;

    if (std::isdigit(c)) {
        state = StateList::IN_NUMBER;
        add_simvol(c);
    } else if (std::isalpha(c) || c == '_') {
        state = StateList::IN_IDENTIFIER;
        add_simvol(c);
    } else if (c == '"') {
        state = StateList::IN_STRING;
    } else if (c == '#') {
        state = StateList::IN_COMMENT_LINE;
    } else if (c == '/' && peek(1) == '*') {
        state = StateList::IN_COMMENT_BLOCK;
    } else if (is_bracket_char(c) || is_punctuation_char(c)) {
        add_simvol(c);
        auto it = punctuation_map.find(buffer);
        if (it != punctuation_map.end()) {
            add_token(it->second, sl, sc);
        } else {
            error("Неизвестный знак пунктуации '" + 
                std::string(1, c) + "'");
        }
    } else if (is_operator_char(c)) {
        state = StateList::IN_OPERATOR;
        add_simvol(c);
    } else {
        error("Неизвестный символ");
    }
}

void Lexer::handlerIN_IDENTIFIER(char c, size_t sl, size_t sc) {
    if (std::isalnum(c) || c == '_') {
        add_simvol(c);
    } else {
        process_identifier(sl, sc);
        retreat();
    }
}

void Lexer::handlerIN_NUMBER(char c, size_t sl, size_t sc) {
    if (std::isdigit(c)) {
        add_simvol(c);
    } else if (c == '.' && std::isdigit(peek(1))) {
        add_simvol(c);
        state = StateList::IN_NUMBER_DOT;
    } else {
        add_token(TokenType::LIT_INT, sl, sc);
        retreat();
    }
}

void Lexer::handlerIN_NUMBER_DOT(char c, size_t sl, size_t sc) {
    if (std::isdigit(c)) {
        add_simvol(c);
        state = StateList::IN_NUMBER_FRACTION;
    } else {
        error("Ожидалась цифра после точки");
    }
}

void Lexer::handlerIN_NUMBER_FRACTION(char c, size_t sl, size_t sc) {
    if (std::isdigit(c)) {
        add_simvol(c);
    } else {
        add_token(TokenType::LIT_DOUBLE, sl, sc);
        retreat();
    }
}

void Lexer::handlerIN_STRING(char c, size_t sl, size_t sc) {
    if (c == '"') {
        add_token(TokenType::LIT_STR, sl, sc);
    } else if (c == '\n' || c == '\0') {
        error("Незакрытая строка");
    } else {
        add_simvol(c);
    }
}

void Lexer::handlerIN_COMMENT_LINE(char c, size_t sl, size_t sc) {
    if (c == '\n') state = StateList::START;
}

void Lexer::handlerIN_COMMENT_BLOCK(char c, size_t sl, size_t sc) {
    if (c == '*' && peek(1) == '/') {
        next();
        state = StateList::START;
    }
}

void Lexer::handlerIN_OPERATOR(char c, size_t sl, size_t sc) {
    if (is_operator_char(c)) {
        std::string temp = buffer + c;
        if (operator_map.count(temp)) {
            add_simvol(c);
            return;
        }
    }
    process_operator(sl, sc);
    retreat();
}

void Lexer::handlerEND(size_t sl, size_t sc) {
    switch (state) {
        case StateList::IN_IDENTIFIER:
            process_identifier(sl, sc);
            state = StateList::START; 
            break;
        case StateList::IN_NUMBER:
            add_token(TokenType::LIT_INT, sl, sc);
            state = StateList::START; 
            break;
        case StateList::IN_NUMBER_FRACTION:
            add_token(TokenType::LIT_DOUBLE, sl, sc);
            state = StateList::START; 
            break;
        case StateList::IN_OPERATOR:
            process_operator(sl, sc);
            state = StateList::START;
            break;
        case StateList::IN_COMMENT_LINE:
            state = StateList::START; 
            break;
        case StateList::IN_NUMBER_DOT:
            error("Незаконченная дробная часть числа в конце файла");
            break;
        case StateList::IN_STRING:
            error("Незакрытая строка в конце файла");
            break;
        case StateList::IN_COMMENT_BLOCK:
            error("Незакрытый многострочный комментарий в конце файла");
            break;
        case StateList::ERROR: case StateList::START: default:
            break;
    }
    add_token(TokenType::END_OF_FILE, line, column);
}

void Lexer::process_identifier(size_t sl, size_t sc) {
    auto it = keyword_map.find(buffer);
    add_token(it != keyword_map.end() ? it->second : 
        TokenType::IDENTIFIER, sl, sc);
}

void Lexer::process_operator(size_t sl, size_t sc) {
    auto it = operator_map.find(buffer);
    if (it != operator_map.end()) add_token(it->second, sl, sc);
    else error("Неизвестный оператор: " + buffer);
}
