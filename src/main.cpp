#include <stdexcept>
#include <string>
#include <vector>

#include "../include/lexer.hpp"


int main(int argc, char const *argv[]){
    if(argc < 2){
        throw std::runtime_error("Не указан файл с кодом");
    }
    std::string filename = argv[1];

    bool pr_tokens = false;
    bool pr_ast = false;
    bool pr_ir = false;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--generate-tokens" || arg == "-t") {
            pr_tokens = true;
        } else if (arg == "--generate-ast" || arg == "-a") {
            pr_ast = true;
        } else if (arg == "--generate-ir" || arg == "-i") {
            pr_ir = true;
        }
    }

    Lexer lexer(filename);
    std::vector<std::unique_ptr<TokenBase>> l = lexer.get_tokens(pr_tokens);
    return 0;
}
