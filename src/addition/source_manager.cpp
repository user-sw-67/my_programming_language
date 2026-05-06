#include "../../include/addition/source_manager.hpp"
#include "../../include/addition/error_manager.hpp"

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

bool SourceManager::load_file(const std::string& file_path) {
        if (!std::filesystem::exists(file_path)) {
            error_manager.except(StagesCompiler::PREPARATION,
                "Файл не существует: " + file_path, *this);
            return false;
        }

        if (std::filesystem::path(file_path).extension() != ".atm") {
            error_manager.except(StagesCompiler::PREPARATION, 
                "Расширение файла должно быть .atm", *this);
            return false;
        }

        if (files.find(file_path) != files.end()) {
            return true;
        }

        std::ifstream file(file_path);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        files[file_path] = std::move(lines);
        return true;
}

const std::vector<std::string>& SourceManager::get_file_content(
    const std::string& file_path) const {
    return files.at(file_path);
}

std::string SourceManager::get_line(
    const std::string& file_path, size_t i) const {
    auto it = files.find(file_path);
    if (it == files.end() || i <= 0 || it->second.empty()) {
        return "";
    }
    if(it->second.size() < i) {
        return it->second.back();
    }
    return it->second[i - 1];
}