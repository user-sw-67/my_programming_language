#include "../../include/addition/source_manager.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/parser/ast.hpp"

#include <filesystem>
#include <string>

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
                SourceLocation(0, 0, file_path), *this);
        }

        if (std::filesystem::path(file_path).extension() != ".atm") {
            throw PreparationError("Расширение файла должно быть .atm", 
                SourceLocation(0, 0, file_path), *this);
        }

        if (modules.find(file_path) != modules.end()) {
            return file_path;
        }

        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw PreparationError("Файл " + file_path + 
                " не удалось прочитать", 
                    SourceLocation(0, 0, file_path), *this);
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