#include <stdexcept>
#include <string>
#include <vector>

#include "../include/lexer.hpp"


int main(int argc, char const *argv[]){
    if(argc < 2){
        throw std::runtime_error("Не указан файл с кодом");
    }

    std::string filename = argv[1];
    Lexer lexer(filename);
    std::vector<std::unique_ptr<TokenBase>> l = lexer.get_tokens();
    return 0;
}
