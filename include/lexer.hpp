#ifndef LEXER
#define LEXER

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iostream>
#include <cctype>
#include <sstream>
#include <memory>
#include <stdexcept>

#include "token_list.hpp"
#include "token.hpp"


class FileManager{
protected:
    std::ifstream file;
public:
    FileManager(const std::string& filename) : 
        file(filename, std::ios::binary) {
            if(!std::filesystem::exists(filename)){
                throw std::runtime_error("Файл не существует");
            }
            if(std::filesystem::path(filename).extension() != ".atm") {
                throw std::runtime_error("Расширение файла должно быть .atm");
            }
            if(!file.is_open()){
                throw std::runtime_error("Файл невозможно открыть");
            }
    }

    FileManager(const FileManager& other) = delete;
    FileManager operator = (const FileManager& other) = delete;
};


class FiniteAutomaton{
protected:

    enum class StateList{
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

    FiniteAutomaton() : 
        state(StateList::START), line(1), column(0), tokens(), buffer() {}

    FiniteAutomaton(const FiniteAutomaton& other) = delete;
    FiniteAutomaton operator = (const FiniteAutomaton& other) = delete;

    void add_simvol(char simvol) {
        buffer += simvol;
    }

    void add_token(TokenType type, size_t start_line, size_t start_column){
        if (buffer.empty()){
            buffer = "undefined";
        }
        tokens.emplace_back(type, start_line, start_column, buffer);
        buffer.clear();
        state = StateList::START;
    }
    
    void error(const std::string& msg) const {
        throw std::runtime_error(
            msg + " в " + std::to_string(line) + ":" + std::to_string(column)
        );
    };

    char next(const std::string& code, size_t i) const {
        if (i + 1 >= code.size()) {
            return '\0';
        }
        return code[i + 1];
    }

    bool is_operator_char(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || 
            c == '^' || c == '%' || c == '=' || c == '!' ||
            c == '<' || c == '>' || c == '&' || c == '|' ||
            c == ':' || c == '?' || c == '.' || c == '~';
    }

    bool is_bracket_char(char c) {
        switch (c) {
            case '(': case ')':
            case '{': case '}':
            case '[': case ']':
                return true;
            default:
                return false;
        }
    }

    bool is_punctuation_char(char c) {
        switch (c) {
            case ';': case ',': 
                return true;
            default:
                return false;
        }
    }
};


class Lexer : public FileManager, public FiniteAutomaton{
private:
public:
    Lexer(const std::string& filename) : 
        FileManager(filename), FiniteAutomaton() {}

    Lexer(const Lexer& other) = delete;
    Lexer operator = (const Lexer& other) = delete;

    std::vector<Token> get_tokens(bool cout_tokens) {
        std::stringstream ss;
        ss << file.rdbuf();
        std::string code_string = ss.str();
        tokenize(code_string);
        if (cout_tokens) save_tokens_to_file("tokens.txt");
        return std::move(tokens);
    }

    void tokenize(const std::string& code) {
        size_t start_line;
        size_t start_column;
        state = StateList::START;
        for (size_t i = 0; i < code.size(); ++i) {
            char c = code[i];
            ++column;
            if (c == '\n') {
                ++line;
                column = 0;
            }
            if(state == StateList::ERROR) break;
            switch (state){
                case StateList::START:
                    handlerSTART(c, i, start_line, start_column, code);
                    break;
                case StateList::IN_IDENTIFIER:
                    handlerIN_IDENTIFIER(c, i, start_line, start_column, code);
                    break;
                case StateList::IN_NUMBER:
                    handlerIN_NUMBER(c, i, start_line, start_column, code);
                    break;
                case StateList::IN_NUMBER_DOT:
                    handlerIN_NUMBER_DOT(c, i, start_line, start_column, code);
                    break;
                case StateList::IN_NUMBER_FRACTION:
                    handlerIN_NUMBER_FRACTION(
                        c, i, start_line, start_column, code);
                    break;
                case StateList::IN_STRING:
                    handlerIN_STRING(c, i, start_line, start_column, code);
                    break;
                case StateList::IN_COMMENT_LINE:
                    handlerIN_COMMENT_LINE(
                        c, i, start_line, start_column, code);
                    break;
                case StateList::IN_COMMENT_BLOCK:
                    handlerIN_COMMENT_BLOCK(
                        c, i, start_line, start_column, code);
                    break;
                case StateList::IN_OPERATOR:
                    handlerIN_OPERATOR(c, i, start_line, start_column, code);
                    break;
                default:
                    break;
            }
        }
        handlerEND(start_line, start_column);
    }

private:
    void save_tokens_to_file(
        const std::string& filename) const {
            std::ofstream file(filename);
            for (const auto& token : tokens) {
                file << token.to_string() << std::endl;
            }
            std::cout << "Сохранено " << tokens.size() << " токенов в " 
                << filename << std::endl;
    }

    void handlerSTART(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (std::isdigit(c)) {
                start_line = line;
                start_column = column;
                state = StateList::IN_NUMBER;
                add_simvol(c);
            } else if (std::isalpha(c) || c == '_') {
                start_line = line;
                start_column = column;
                state = StateList::IN_IDENTIFIER;
                add_simvol(c);
            } else if (c == '"') {
                start_line = line;
                start_column = column + 1;
                state = StateList::IN_STRING;
            } else if (c == '#') {
                state = StateList::IN_COMMENT_LINE;
            } else if (c == '/' && next(code, i) == '*') {
                state = StateList::IN_COMMENT_BLOCK;
            } else if (is_bracket_char(c) || is_punctuation_char(c)) {
                start_line = line;
                start_column = column;
                add_simvol(c);
                auto it = punctuation_map.find(std::string(1, c));
                if (it != punctuation_map.end()) {
                    add_token(it->second, start_line, start_column);
                } else {
                    state = StateList::ERROR;
                    error("Неизвестный знак пунктуации: '" + 
                        std::string(1, c) + "'");
                }
            } else if (is_operator_char(c)) {
                start_line = line;
                start_column = column;
                state = StateList::IN_OPERATOR;
                add_simvol(c);
            } else if (std::isspace(c)) {
                return; 
            } else {
                state = StateList::ERROR;
                error("Неизвестный символ");
            }
    }

    void handlerIN_IDENTIFIER(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (std::isalnum(c) || c == '_') {
                add_simvol(c);
            } else {
                process_identifier(start_line, start_column);
                if (c != '\n') {
                    --i;
                    --column;
                }
            }
    }

    void handlerIN_NUMBER(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (std::isdigit(c)) {
                add_simvol(c);
            } else if (c == '.' && next(code, i) != '.') {
                add_simvol(c);
                state = StateList::IN_NUMBER_DOT;
            } else if (std::isspace(c) || is_operator_char(c) 
                || is_punctuation_char(c) || is_bracket_char(c)) {
                    add_token(TokenType::LIT_INT, start_line, start_column);
                    if (c != '\n') {
                        --i;
                        --column;
                    }
            } else {
                state = StateList::ERROR;
                error("Некорректное число " + buffer);
            }
        }

    void handlerIN_NUMBER_DOT(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (std::isdigit(c)) {
                add_simvol(c);
                state = StateList::IN_NUMBER_FRACTION;
            } else {
                state = StateList::ERROR;
                error("После точки в числе должна быть хотя бы одна цифра");
            }
        }

    void handlerIN_NUMBER_FRACTION(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (std::isdigit(c)) {
                add_simvol(c);
            } else if ((std::isspace(c) || is_operator_char(c) 
                || is_punctuation_char(c) || is_bracket_char(c)) && c != '.') {
                    add_token(TokenType::LIT_DOUBLE, start_line, start_column);
                    if (c != '\n') {
                        --i;
                        --column;
                    }
            } else {
                state = StateList::ERROR;
                error("Некорректное число " + buffer);
            }
        }

    void handlerIN_STRING(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (c != '"') {
                add_simvol(c);
            } else {
                add_token(TokenType::LIT_STR, start_line, start_column);
                
            }
        }

    void handlerIN_COMMENT_LINE(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (c == '\n') {
                state = StateList::START;
            }
        }

    void handlerIN_COMMENT_BLOCK(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if (c == '*' && next(code, i) == '/') {
                state = StateList::START;
                ++i;
                ++column;
            }
        }

    void handlerIN_OPERATOR(const char& c, size_t& i, size_t& start_line, 
        size_t& start_column, const std::string& code) {
            if ((is_operator_char(c) && buffer.size() < 2) || 
                (buffer == ".." && c == '.') || (buffer == "//" && c == '=')) {
                    add_simvol(c);
            } else {
                process_operator(start_line, start_column);
                if (c != '\n') {
                    --i;
                    --column;
                }
            }
        }

    void handlerEND(size_t& start_line, size_t& start_column) {
        switch (state) {
            case StateList::START:
                break;
            case StateList::IN_NUMBER:
                add_token(TokenType::LIT_INT, start_line, start_column);
                break;
            case StateList::IN_NUMBER_DOT:
                state = StateList::START;
                error("Незаконченная дробная часть числа в конце файла");
            case StateList::IN_NUMBER_FRACTION:
                add_token(TokenType::LIT_DOUBLE, start_line, start_column);
                break;
            case StateList::IN_STRING:
                state = StateList::START;
                error("Незакрытая строка в конце файла");
            case StateList::IN_IDENTIFIER:
                process_identifier(start_line, start_column);
                break;
            case StateList::IN_OPERATOR:
                process_operator(start_line, start_column);
                break;
            case StateList::IN_COMMENT_LINE:
                state = StateList::START;
                break;
            case StateList::IN_COMMENT_BLOCK:
                state = StateList::START;
                error("Незакрытый многострочный комментарий в конце файла");
            case StateList::ERROR:
                error("Лексический анализ выявил неизвестную ошибку");
            default:
                break;
        }
        ++column;
        add_token(TokenType::END_OF_FILE, line, column);
    }

    void process_identifier(size_t& start_line, size_t& start_column) {
        auto it = keyword_map.find(buffer);
        if (it != keyword_map.end()){
            add_token(it->second, start_line, start_column);
        } else {
            add_token(TokenType::IDENTIFIER, start_line, start_column);
            
        }
    }

    void process_operator(size_t& start_line, size_t& start_column) {
        auto it = operator_map.find(buffer);
        if (it != operator_map.end()) {
            add_token(it->second, start_line, start_column);
        } else {
            state = StateList::ERROR;
            error("Неизвестный оператор: '" + buffer + "'");
        }
    }
};


#endif
