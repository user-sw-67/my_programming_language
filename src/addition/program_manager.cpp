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
}

void PrintPhase::ast(const std::string& filename, 
    const std::unique_ptr<ProgramNode>& program) {
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

    auto print_info = [](std::string label, bool enabled){
        std::cout << label + ": ";
        if (enabled) {
            std::cout << "\033[1;32mДА\033[0m" << std::endl;
        } else {
            std::cout << "\033[1;31mНЕТ\033[0m" << std::endl;
        }
    };

    print_info("Вывод токенов", config.print_tokens);
    print_info("Вывод предварительного AST", config.print_ast);
    print_info("Вывод финального AST", config.print_ast);
    print_info("Вывод LLVM IR", config.print_ir);
    if(!config.dir_for_files.empty()) std::cout << 
        "Сохранение файлов в директорию: " + config.dir_for_files << "\n";

    std::cout << "------------------------------------------------" 
              << std::endl;
    std::cout << "\033[1;35mЗАПУСК КОНВЕЙЕРА ОБРАБОТКИ...\033[0m" 
              << std::endl;
}

void ProgramManager::parse_config_flags(int argc, char const *argv[]) {
    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-t" || arg == "--generate-tokens") {
            config.print_tokens = true;
            
        } else if (arg == "-a" || arg == "--generate-ast") {
            config.print_ast = true;

        } else if (arg == "-i" || arg == "--generate-ir") {
            config.print_ir = true;
        
        } else if (arg == "-dir" || arg == "--directory") {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                std::string dir = argv[++i];
                std::filesystem::create_directories(dir);
                config.dir_for_files = dir;
            } else {
                throw std::runtime_error("[" + error_code::CFG_0001 +
                    "] После флага -dir или --directory "
                    "укажите путь до директории для сохраняемых файлов");
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
    if(config.dir_for_files.empty() &&
        (config.print_ast || config.print_ir || config.print_tokens)){
            throw std::runtime_error("[" + error_code::CFG_0002 +
                "] Укажите флаг -dir или --directory");
    }
}

ProgramManager::ProgramManager(int argc, char const *argv[]){
    if (argc < 2) {
        throw std::runtime_error("[" + error_code::CFG_0003 +
            "] Не указан файл с исходным кодом");
    }
    config.input_file = argv[1];
    parse_config_flags(argc, argv);
    PrintPhase::launch(config);
}

void ProgramManager::run() {
    try{
        managers.source.is_print_tokens = config.print_tokens;
        managers.source.is_print_ast = config.print_ast;
        managers.source.is_print_ir = config.print_ir;
        managers.source.dir_print = config.dir_for_files;

        std::string file_path = managers.source.load_file(config.input_file);
        Module& mod = managers.source.modules[file_path];
        mod.is_root = true;

        Lexer lexer(mod.lines, file_path, managers);
        mod.tokens = lexer.get_tokens();
        Parser parser(mod.tokens, file_path, managers);
        mod.ast = parser.parse();

        SemanticsManager semantics_manager(mod.ast, file_path, managers);
        semantics_manager.run();

        managers.source.print_all_files();

        managers.error.printAll(managers.source);
        if(!managers.error.ok()) return;

        

    } catch(const RuntimeError& e) {
        std::cerr << "\033[31m" << "КРИТИЧЕСКАЯ ОШИБКА RNT: " 
            << e.what() << "\033[0m" << "\n";
    } catch(const CompilerError& e) {
        std::cerr << "\033[31m" << "КРИТИЧЕСКАЯ ОШИБКА CML: " 
            << e.to_string() << "\033[0m" << "\n";
    } catch(const std::exception& e) {
        throw;
    }
}