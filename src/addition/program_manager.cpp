#include "../../include/addition/program_manager.hpp"
#include "../../include/addition/mermaid_visitor.hpp"
#include "../../include/lexer/lexer.hpp"
#include "../../include/parser/parser.hpp"
#include "../../include/semantics/semantics_manager.hpp"

#include <fstream>
#include <filesystem>


void PrintPhase::tokens(const std::string& filename, 
    const std::vector<Token>& tokens) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " 
                << filename << std::endl;
            return;
        }
        for (const auto& token : tokens) {
            file << token.to_string() << std::endl;
        }
        std::cout << "\n\033[1;34mСохранено " << tokens.size() 
            << " токенов в " << filename << "\033[0m" << std::endl;
}

void PrintPhase::ast(const std::string& filename, 
    const std::unique_ptr<ProgramNode>& program, const std::string& type) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " 
                << filename << std::endl;
            return;
        }
        file << "```mermaid\n";
        MermaidVisitor visualizer(file);
        visualizer.start();
        program->accept(visualizer);
        file << "```\n";
        file.close();
        std::cout << "\n\033[1;34m" + type + " AST дерево сохранено в " 
            << filename << "\033[0m" << std::endl;
}

void PrintPhase::launch(const CompilerConfig& config) {
    std::cout << "\n\033[1;36mКОНФИГУРАЦИЯ КОМПИЛЯТОРА ATM\033[0m" 
        << std::endl;
    std::cout << "------------------------------------------------" 
        << std::endl;

    std::cout << "Исходный файл: " << config.input_file << std::endl;
    std::cout << "Режим работы: " << (config.mode == RunMode::INTERPRET ? 
            "ИНТЕРПРЕТАЦИЯ" : "КОМПИЛЯЦИЯ (LLVM)") << std::endl;
    std::cout << "------------------------------------------------" 
        << std::endl;

    auto print_info = [](std::string label, bool enabled, std::string path){
        std::cout << label + ": ";
        if (enabled) {
            std::cout << "\033[1;32mДА\033[0m -> " << path << std::endl;
        } else {
            std::cout << "\033[1;31mНЕТ\033[0m" << std::endl;
        }
    };

    print_info("Вывод токенов", config.print_tokens, config.tokens_path);
    print_info("Вывод предварительного AST", 
        config.print_ast, config.ast_path_pre);
    print_info("Вывод финального AST", 
        config.print_ast, config.ast_path_post);
    print_info("Вывод LLVM IR", config.print_ir, config.ir_path);

    std::cout << "------------------------------------------------" 
              << std::endl;
    std::cout << "\033[1;35mЗАПУСК КОНВЕЙЕРА ОБРАБОТКИ...\033[0m" 
              << std::endl;
}

void ProgramManager::parse_config_flags(int argc, char const *argv[]) {
    auto insert_before_extension = [](const std::string& filename, 
        const std::string& suffix) {
            std::filesystem::path path(filename);

            std::filesystem::path parent = path.parent_path();
            std::string stem = path.stem().string();
            std::string ext = path.extension().string();

            std::filesystem::path result = parent / (stem + suffix + ext);
            return result.string();
    };

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-t" || arg == "--generate-tokens") {
            config.print_tokens = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                std::string name = argv[++i];
                config.tokens_path = name;
            }
            
        } else if (arg == "-a" || arg == "--generate-ast") {
            config.print_ast = true;
            if (i + 1 < argc && argv[i+1][0] != '-') {
                std::string name = argv[++i];
                config.ast_path_post = insert_before_extension(name, "_post");
                config.ast_path_pre = insert_before_extension(name, "_pre");
            }

        } else if (arg == "-i" || arg == "--generate-ir") {
            config.print_ir = true;
            if (i + 1 < argc && argv[i+1][0] != '-') {
                std::string name = argv[++i];
                config.ir_path = name;
            }

        } else if (arg == "-C") {
            config.mode = RunMode::COMPILE;

        } else if (arg == "-I") {
            config.mode = RunMode::INTERPRET;

        } else {
            std::cerr << "Предупреждение: Неизвестный флаг " 
                      << arg << "\n";
        }
    }
}

ProgramManager::ProgramManager(int argc, char const *argv[]) :
    error_manager(), 
    source_manager(error_manager) {
    if (argc < 2) {
        throw std::runtime_error("Не указан файл с исходным кодом");
    }
    config.input_file = argv[1];
    parse_config_flags(argc, argv);
    PrintPhase::launch(config);
}

void ProgramManager::run() {
    try{
        std::string file_path = source_manager.load_file(config.input_file);
        const auto& lines = source_manager.get_file_content(file_path);

        Lexer lexer(lines, file_path, error_manager, source_manager);
        std::vector<Token> tokens = lexer.get_tokens();

        error_manager.printAll(source_manager);
        if(!error_manager.ok()) return;

        if(config.print_tokens) {
            PrintPhase::tokens(config.tokens_path, tokens);
        }

        Parser parser(tokens, file_path, error_manager, source_manager);
        source_manager.modules[file_path].ast = parser.parse();

        error_manager.printAll(source_manager);
        if(!error_manager.ok()) return;

        if(config.print_ast) {
            PrintPhase::ast(config.ast_path_pre, 
                source_manager.modules[file_path].ast, "Предварительное");
        }

        SemanticsManager semantics_manager(
            source_manager.modules[file_path].ast, source_manager, 
                error_manager, file_path);
        semantics_manager.run();

        error_manager.printAll(source_manager);
        if(!error_manager.ok()) return;

        if(config.print_ast) {
            PrintPhase::ast(config.ast_path_post, 
                source_manager.modules[file_path].ast, "Финальное");
        }

    } catch(const CompilerError& e) {
        std::cerr << e.to_string() << "\n";
    } catch(const std::exception& e) {
        throw;
    }
}