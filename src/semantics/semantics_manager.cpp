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
    SymbolTable table_main;
    if(!table_main.init_builtins(get_builtin_data())){
        error_manager.add(
            "Не удалось инициализировать встроенный функционал", 
                {0, 0, filename}, Severity::ERROR);
    }
    source_manager.modules[filename].scope = table_main.get_global_scope();

    DefinitionVisitor definition_visitor(table_main, 
        error_manager, source_manager);
    source_manager.modules[filename].status = ModuleStatus::LOADING;
    program->accept(definition_visitor);
    source_manager.modules[filename].status = ModuleStatus::LOADED;
}

std::vector<BuiltinData> SemanticsManager::get_builtin_data() {
    std::vector<BuiltinData> objects;
    objects.push_back(BuiltinFunctionData{
        "print", 0, true, builtin_data::functions::print});
    objects.push_back(BuiltinFunctionData{
        "is_type", 1, false, builtin_data::functions::is_type});
    return objects;
}
