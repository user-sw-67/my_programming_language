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


class Lexer : public FileManager{
private:
public:
    Lexer(const std::string& filename) : FileManager(filename) {}

    std::vector<std::unique_ptr<TokenBase>> get_tokens() {
        std::vector<std::unique_ptr<TokenBase>> tokens;

        std::stringstream ss;
        ss << file.rdbuf();
        std::string code_string = ss.str();

        std::cout << code_string << std::endl;

        return tokens;
    }

};


#endif
