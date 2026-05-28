#ifndef SOURCE_MANAGER_HPP
#define SOURCE_MANAGER_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <filesystem>

class Scope;
class ErrorManager;
class ProgramNode;

enum class ModuleStatus {
    NOT_LOADED,
    LOADING,
    LOADED
};

struct Module {
    std::vector<std::string> lines;
    std::unique_ptr<ProgramNode> ast;
    std::shared_ptr<Scope> scope;
    bool is_root = false;
    size_t index;

    ModuleStatus status = ModuleStatus::NOT_LOADED;
};

struct ModuleReference {
    const std::string* path;
    const Module* module;
};

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
    size_t next_index = 0;

public:
    std::unordered_map<std::string, Module> modules;

    SourceManager(ErrorManager& error_manager);
    
    std::string load_file(const std::string& file_path);
    
    std::string resolve_canonical_path(
        const std::string& import_path, const std::string& current_file_path);

    const std::vector<std::string>& get_file_content(
        const std::string& file_path) const;
    
    void active_index(Module& mod);

    std::string get_line(const std::string& file_path, size_t i) const;
};

#endif