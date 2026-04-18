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
    StateList state;
    std::vector<std::unique_ptr<TokenBase>> tokens;
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

    template<typename EnumType>
    void add_token(EnumType type, size_t start_line, size_t start_column){
        tokens.push_back(std::make_unique<Token<EnumType>>(
            type, start_line, start_column, buffer));
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
            case '.': case ':': 
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

    std::vector<std::unique_ptr<TokenBase>> get_tokens(bool cout_tokens) {
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
            if(state == StateList::ERROR) return;
            switch (state){
                case StateList::START:
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
                            int category = it->second.first;
                            int value = it->second.second;
                            switch (category) {
                                case 0:
                                    add_token(static_cast<token_list::Brackets>(
                                        value), start_line, start_column);
                                    break;
                                case 1:
                                    add_token(static_cast<token_list::Symbols>(
                                        value), start_line, start_column);
                                    break;
                            }
                        } else {
                            state = StateList::ERROR;
                        }
                    } else if (is_operator_char(c)) {
                        start_line = line;
                        start_column = column;
                        state = StateList::IN_OPERATOR;
                        add_simvol(c);
                    } 
                    break;
                case StateList::IN_IDENTIFIER:
                    if (std::isalnum(c) || c == '_') {
                        add_simvol(c);
                    } else {
                        auto it = keyword_map.find(buffer);
                        if (it != keyword_map.end()){
                            int category = it->second.first;
                            int value = it->second.second;
                            switch (category) {
                                case 0:
                                    add_token(static_cast<
                                        token_list::SpecialWords>(value), 
                                            start_line, start_column);
                                    break;
                                case 1:
                                    add_token(static_cast<
                                        token_list::Literals>(value), 
                                            start_line, start_column);
                                    break;
                                case 2:
                                    add_token(static_cast<
                                        token_list::built_functions::
                                            StandardStreams>(value), 
                                                start_line, start_column);
                                    break;
                                case 3:
                                    add_token(static_cast<
                                        token_list::data_types::
                                            Primitive>(value), 
                                                start_line, start_column);
                                    break;  
                            }
                        } else {
                            add_token(token_list::Special::IDENTIFIER, 
                                start_line, start_column);
                        }
                        --i;
                        --column;
                    }
                    break;
                case StateList::IN_NUMBER:
                    if (std::isdigit(c)) {
                        add_simvol(c);
                    } else if (c == '.') {
                        add_simvol(c);
                        state = StateList::IN_NUMBER_DOT;
                    } else {
                        add_token(token_list::Literals::INT, 
                            start_line, start_column);
                        --i;
                        --column;
                    }
                    break;
                case StateList::IN_NUMBER_DOT:
                    if (std::isdigit(c)) {
                        add_simvol(c);
                        state = StateList::IN_NUMBER_FRACTION;
                    } else {
                        state = StateList::ERROR;
                    }
                    break;
                case StateList::IN_NUMBER_FRACTION:
                    if (std::isdigit(c)) {
                        add_simvol(c);
                    } else {
                        add_token(token_list::Literals::DOUBLE, 
                            start_line, start_column);
                        --i;
                        --column;
                    }
                    break;
                case StateList::IN_STRING:
                    if (c != '"') {
                        add_simvol(c);
                    } else {
                        add_token(token_list::Literals::STR, 
                            start_line, start_column);
                    }
                    break;
                case StateList::IN_COMMENT_LINE:
                    if (c == '\n') {
                        state = StateList::START;
                    }
                    break;
                case StateList::IN_COMMENT_BLOCK:
                    if (c == '*' && next(code, i) == '/') {
                        state = StateList::START;
                    }
                    break;
                case StateList::IN_OPERATOR:
                    if (is_operator_char(next(code, i))) {
                        add_simvol(c);
                    } else {
                        auto it = operator_map.find(buffer);
                        if (it != operator_map.end()) {
                            int category = it->second.first;
                            int value = it->second.second;
                            switch (category) {
                                case 0:
                                    add_token(static_cast<
                                            token_list::operators::Assignment>(
                                                value), start_line, 
                                                    start_column);
                                    break;
                            }
                        } else {
                            state = StateList::ERROR;
                        }
                        --i;
                        --column;
                    }
                    break;
                default:
                    break;
            }
        }
        switch (state){
            case StateList::START: case StateList::IN_COMMENT_LINE:
                add_token(token_list::Special::END_OF_FILE, 0, 0);
                break;
            default:
                break;
        }

    }

    void save_tokens_to_file(
        const std::string& filename) const {
            std::ofstream file(filename);
            for (const auto& token : tokens) {
                file << token->to_string() << std::endl;
            }
            std::cout << "Сохранено " << tokens.size() << " токенов в " 
                << filename << std::endl;
    }
};


#endif
