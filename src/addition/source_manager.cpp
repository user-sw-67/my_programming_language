#include "../../include/addition/source_manager.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/parser/ast.hpp"

#include <filesystem>
#include <string>
#include <iomanip>

SourceLocation::SourceLocation(
    size_t line, 
    size_t column,
    const std::string& file_path) : 
        line(line), 
        column(column),
        file_path(file_path) {}

bool SourceLocation::operator==(const SourceLocation& other) const {
    return (other.line == line) && 
        (other.column == column) && 
        (file_path == other.file_path);
}

bool SourceLocation::operator!=(const SourceLocation& other) const {
    return !(*this == other);
}

SourceManager::SourceManager(ErrorManager& error_manager) : 
    error_manager(error_manager) {}

std::string SourceManager::resolve_canonical_path(
    const std::string& import_path, const std::string& current_file_path) {
        try {
            std::filesystem::path current_dir = 
                std::filesystem::path(current_file_path).parent_path();
            std::filesystem::path full_path = current_dir / import_path;
            if (!std::filesystem::exists(full_path)) return "";
            return std::filesystem::canonical(full_path).string();
        } catch (...) {
            return "";
        }
}

std::string SourceManager::load_file(const std::string& file_atm) {
        std::string file_path;
        try{
            file_path = std::filesystem::canonical(file_atm).string();
        }catch(...){
            throw PreparationError("Файл не существует: " + file_path,
                SourceLocation(0, 0, file_path), *this, error_code::PRE_0001);
        }

        if (std::filesystem::path(file_path).extension() != ".atm") {
            throw PreparationError("Расширение файла должно быть .atm",
                SourceLocation(0, 0, file_path), *this, error_code::PRE_0002);
        }

        if (modules.find(file_path) != modules.end()) {
            return file_path;
        }

        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw PreparationError("Файл " + file_path +
                " не удалось прочитать",
                    SourceLocation(0, 0, file_path), *this,
                        error_code::PRE_0003);
        }

        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        Module mod;
        mod.lines = std::move(lines);
        mod.ast = nullptr;
        mod.scope = nullptr;

        modules[file_path] = std::move(mod);
        return file_path;
}

const std::vector<std::string>& SourceManager::get_file_content(
    const std::string& file_path) const {
    return modules.at(file_path).lines;
}

void SourceManager::active_index(Module& mod){
    mod.index = next_index;
    ++next_index;
}

std::string SourceManager::get_line(
    const std::string& file_path, size_t i) const {
    auto it = modules.find(file_path);
    if (it == modules.end() || i <= 0 || it->second.lines.empty()) {
        return "";
    }
    if(it->second.lines.size() < i) {
        return it->second.lines.back();
    }
    return it->second.lines[i - 1];
}

void SourceManager::print_tokens(const std::string& file, Module& mod){
    if(is_print_tokens && !mod.tokens.empty()){
        std::string file_name = "tokens_" + std::to_string(mod.index) + ".txt";
        std::string file_path = dir_print / file_name;
        files_print[file_path] = file;
        PrintPhase::tokens(file_path, mod.tokens);
    }
    return;
}

void SourceManager::print_ast(const std::string& file, Module& mod, 
    const std::string& type_ast){
        if(is_print_ast && mod.ast){
            std::string file_name = "ast_" + type_ast + "_" + 
                std::to_string(mod.index) + ".md";
            std::string file_path = dir_print / file_name;
            files_print[file_path] = file;
            PrintPhase::ast(file_path, mod.ast);
        }
        return;
}

void SourceManager::print_ir(const std::string& file, Module& mod){}

void SourceManager::print_all_files() {
    if (files_print.empty()) return;

    auto utf8_length = [](const std::string& str) -> size_t {
        size_t len = 0;
        for (unsigned char c : str) {
            if ((c & 0xC0) != 0x80) ++len;
        }
        return len;
    };
    
    auto print_left = [&](const std::string& str, size_t width) {
        std::cout << str;
        size_t actual_len = utf8_length(str);
        if (width > actual_len) {
            std::cout << std::string(width - actual_len, ' ');
        }
    };

    const size_t column_width = 35;

    std::cout << "\n\033[1;36mСГЕНЕРИРОВАННЫЕ АРТЕФАКТЫ\033[0m\n";
    std::cout << "-------------------------------------"
        "---------------------------------\n";
    print_left("ИСХОДНЫЙ ФАЙЛ", column_width);
    std::cout << "| СГЕНЕРИРОВАННЫЙ ФАЙЛ\n";
    std::cout << "--------------------------------------"
        "--------------------------------\n";
    for (const auto& [file_prog, source_file_path] : files_print) {
        std::string rel_path = std::filesystem::relative(
            source_file_path).string();
        print_left(rel_path, column_width);
        std::cout << "| \033[1;32m" << file_prog << "\033[0m\n";
    }
    
    std::cout << "---------------------------------"
        "-------------------------------------\n";
}