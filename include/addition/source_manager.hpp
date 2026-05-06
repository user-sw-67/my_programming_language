#ifndef SOURCE_MANAGER_HPP
#define SOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <filesystem>

class ErrorManager;

struct SourceLocation {
    size_t line;
    size_t column;
    std::string file_path;

    SourceLocation(
        size_t line = 0, 
        size_t column = 0,
        const std::string& file_path = "");
    
    bool operator==(const SourceLocation& other) const;
    bool operator!=(const SourceLocation& other) const;
};


class SourceManager {
private:
    ErrorManager& error_manager;
    std::unordered_map<std::string, std::vector<std::string>> files;

public:
    SourceManager(ErrorManager& error_manager);
    
    bool load_file(const std::string& file_path);
    
    const std::vector<std::string>& get_file_content(
        const std::string& file_path) const;
    
    std::string get_line(const std::string& file_path, size_t i) const;
};

#endif