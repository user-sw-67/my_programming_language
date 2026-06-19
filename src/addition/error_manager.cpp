#include "../../include/addition/error_manager.hpp"
#include "../../include/addition/source_manager.hpp"

#include <sstream>
#include <iostream>
#include <algorithm>

CompilerError::CompilerError(const std::string& msg, const SourceLocation& loc,
    SourceManager& source_manager, const std::string& code)
        : message(msg), loc(loc), source_manager(source_manager), code(code) {}

const char* CompilerError::what() const noexcept {
    return message.c_str();
}

int CompilerError::get_line() const {return loc.line;}

int CompilerError::get_column() const {return loc.column;}

const std::string& CompilerError::get_code() const {return code;}

std::string CompilerError::to_string() const {
    std::string line_code = source_manager.get_line(loc.file_path, loc.line);
    std::stringstream ss;
    
    ss << "\n\033[1;31m┌─ Ошибка компиляции\033[0m\n";
    ss << "\033[1;31m│\033[0m\n";
    
    ss << "\033[1;31m├─\033[0m \033[1;31mФайл:\033[0m " 
       << loc.file_path << ":" << loc.line << ":" << loc.column << "\n";
    
    ss << "\033[1;31m├─\033[0m \033[1;31m" << message << "\033[0m"
       << " \033[90m[" << code << "]\033[0m\n";
    
    if (!line_code.empty()) {
        ss << "\033[1;31m├─\033[0m \033[1;31mКод:\033[0m\n";
        ss << "\033[1;31m│\033[0m   \033[32m" << line_code << "\033[0m\n";
        std::string indent = "";
        if (loc.column > 0) {
            indent = std::string(loc.column - 1, ' ');
        }
        ss << "\033[1;31m│\033[0m   \033[31m" << indent << "▲\033[0m\n";
        ss << "\033[1;31m│\033[0m   \033[31m" << indent 
           << "└─ \033[1mОшибка\033[0m\n";
    }
    
    ss << "\033[1;31m└──────────────────────────────────────────\033[0m\n";
    return ss.str();
}

PreparationError::PreparationError(const std::string& msg,
    const SourceLocation& loc, SourceManager& source_manager,
        const std::string& code) :
        CompilerError("Ошибка подготовки запуска: " + msg,
            loc, source_manager, code) {}

void ErrorManager::format_error(const Error& err, 
    const SourceManager& source_manager) const {
        std::stringstream ss;
        
        const char* color = "\033[1;31m";
        const char* severity_text = "Ошибка";
        if (err.lvl == Severity::WARNING) {
            color = "\033[1;33m";
            severity_text = "Предупреждение";
        } else if (err.lvl == Severity::NOTE) {
            color = "\033[1;36m";
            severity_text = "Заметка";
        }

        ss << color << severity_text << "\033[0m"
           << " : " << err.location.file_path
           << ":" << err.location.line 
           << ":" << err.location.column << "\n";

        std::string line_code = source_manager.get_line(
            err.location.file_path, err.location.line);
        if (!line_code.empty()) {
            ss << "    \033[90m│\033[0m " << line_code << "\n";
            std::string indent = "";
            if (err.location.column > 0) {
                indent = std::string(err.location.column - 1, ' ');
            }
            
            ss << "    \033[90m│\033[0m   " << indent << "\033[1;31m^\033[0m\n";
        }
        ss << "    \033[90m└─\033[0m " << err.msg 
           << " \033[90m[" << err.code << "]\033[0m\n\n";
           
        std::cerr << ss.str();
}

void ErrorManager::add(const std::string& msg, const SourceLocation& loc, 
    const Severity& sev, const std::string& code_error) {
        errors.push_back({sev, loc, msg, code_error});
        if (sev == Severity::ERROR) ++count_errors;
}

bool ErrorManager::ok() const {
    return count_errors == 0;
}

void ErrorManager::printAll(const SourceManager& source_manager) const {
    std::vector<Error> sorted_errors = errors;

    auto file_rank = [&source_manager](const std::string& file_path) {
        auto it = source_manager.modules.find(file_path);
        if (it == source_manager.modules.end()) return SIZE_MAX;
        if (it->second.is_root) return static_cast<size_t>(0);
        return it->second.index + 1;
    };

    std::stable_sort(sorted_errors.begin(), sorted_errors.end(),
        [&file_rank](const Error& a, const Error& b) {
            size_t rank_a = file_rank(a.location.file_path);
            size_t rank_b = file_rank(b.location.file_path);
            if (rank_a != rank_b) return rank_a < rank_b;
            if (a.location.line != b.location.line)
                return a.location.line < b.location.line;
            return a.location.column < b.location.column;
        });

    for(const auto& err : sorted_errors) {
        format_error(err, source_manager);
    }
}

RuntimeError::RuntimeError(const std::string& msg, const std::string& code) :
    msg(msg), code(code) {}

const char* RuntimeError::what() const noexcept {return msg.c_str();}

const std::string& RuntimeError::get_code() const {return code;}

TypeError::TypeError(const std::string& msg, const std::string& code) :
    RuntimeError(msg, code) {}