#ifndef PROGRAM_MANAGER_HPP
#define PROGRAM_MANAGER_HPP

#include "error_manager.hpp"
#include "source_manager.hpp"
#include "../lexer/token.hpp"
#include "../parser/ast.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>


enum class RunMode { 
    INTERPRET, 
    COMPILE
};

struct CompilerConfig {
    std::string input_file;
    RunMode mode = RunMode::COMPILE;

    bool print_tokens = false;
    bool print_ast = false;
    bool print_ir = false;

    std::string tokens_path = "tokens.txt";
    std::string ast_path_pre = "ast_pre.md";
    std::string ast_path_post = "ast_post.md";
    std::string ir_path = "output.ll";
};

class PrintPhase {
public:
    static void tokens(const std::string& filename, 
        const std::vector<Token>& tokens);
    
    static void ast(const std::string& filename, 
        const std::unique_ptr<ProgramNode>& program, const std::string& type);
    
    static void launch(const CompilerConfig& config);
};

class ProgramManager {
public:
    ProgramManager(int argc, char const *argv[]);
    
    void run();

private:
    ErrorManager error_manager;
    SourceManager source_manager;
    CompilerConfig config;

    void parse_config_flags(int argc, char const *argv[]);
};

#endif