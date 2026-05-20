#include "../../include/semantics/semantics_manager.hpp"
#include "../../include/semantics/semantics_visitor.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/addition/source_manager.hpp"
#include "../../include/parser/ast.hpp"


SemanticsManager::SemanticsManager(std::unique_ptr<ProgramNode>& program, 
    SourceManager& source_manager, ErrorManager& error_manager, 
        const std::string& filename) : 
            program(program), source_manager(source_manager), 
                error_manager(error_manager), filename(filename) {}

void SemanticsManager::run() {
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

std::vector<BuiltinData> SemanticsManager::get_builtin_data() {
    std::vector<BuiltinData> objects;
    objects.push_back(BuiltinFunctionData{
        "print", 0, true, builtin_data::functions::print});
    objects.push_back(BuiltinFunctionData{
        "is_type", 1, false, builtin_data::functions::is_type});
    return objects;
}
