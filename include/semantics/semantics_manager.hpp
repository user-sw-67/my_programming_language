#ifndef SEMANTICS_MANAGER_HPP
#define SEMANTICS_MANAGER_HPP

#include "symbol_table.hpp"
#include "semantics_visitor.hpp"
#include "../addition/error_manager.hpp"
#include "../addition/source_manager.hpp"


class SemanticsManager{
private:
    SourceManager& source_manager;
    ErrorManager& error_manager;
    std::string filename;
    SymbolTable table;
    std::unique_ptr<ProgramNode>& program;

public:
    SemanticsManager(std::unique_ptr<ProgramNode>& program, 
        SourceManager& source_manager, ErrorManager& error_manager, 
            const std::string& filename) : 
                program(program), source_manager(source_manager), 
                    error_manager(error_manager), filename(filename) {}

    void run() {
        if(!table.init_builtins(get_builtin_data())){
            error_manager.add(
                "Не удалось инициализировать встроенный функционал", 
                    {0, 0, filename}, Severity::ERROR);
        }

        DefinitionVisitor definition_visitor(table, error_manager);
        program->accept(definition_visitor);

        AnalysisVisitor analysis_visitor(table, error_manager);
        program->accept(analysis_visitor);

        OptimizationVisitor optimization_visitor(table, error_manager);
        program->accept(optimization_visitor);
    }

private:
    std::vector<BuiltinData> get_builtin_data() {
        std::vector<BuiltinData> objects;
        objects.push_back(BuiltinFunctionData{
            "print", 0, true, builtin_data::functions::print});
        objects.push_back(BuiltinFunctionData{
            "is_type", 1, false, builtin_data::functions::is_type});
        return objects;
    }
};

#endif