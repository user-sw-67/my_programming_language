#ifndef SEMANTICS_MANAGER_HPP
#define SEMANTICS_MANAGER_HPP

#include "symbol_table.hpp"
#include "../builds/builds.hpp"

#include <string>
#include <memory>


class SourceManager;
class ErrorManager;
class ProgramNode;


class SemanticsManager{
private:
    SourceManager& source_manager;
    ErrorManager& error_manager;
    std::string filename;
    SymbolTable table;
    std::unique_ptr<ProgramNode>& program;

    std::vector<BuiltinData> get_builtin_data();

public:
    SemanticsManager(std::unique_ptr<ProgramNode>& program, 
        SourceManager& source_manager, ErrorManager& error_manager, 
            const std::string& filename);

    void run();

};

#endif