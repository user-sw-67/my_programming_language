#include "../../include/semantics/semantics_manager.hpp"
#include "../../include/semantics/semantics_visitor.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"


SemanticsManager::SemanticsManager(std::unique_ptr<ProgramNode>& program, 
        const std::string& filename, Managers& managers) : 
            program(program), filename(filename), 
                    managers(managers) {}

void SemanticsManager::validate_entry_point(
    std::shared_ptr<Scope> scope, const std::string& filename) const {
        auto it = scope->symbols.find("main");
        if (it == scope->symbols.end()) {
            managers.error.add("Не найдена точка входа (функция main)", 
                {0, 0, filename}, Severity::ERROR);
            return;
        }

        auto main_symbol = it->second;
        if (main_symbol->type != SymbolType::FUNCTION) {
            managers.error.add("Идентификатор main должен быть функцией", 
                {0, 0, filename}, Severity::ERROR);
            return;
        }

        if (main_symbol->count_args != 0) {
            managers.error.add(
                "Функция 'main' не должна принимать аргументов", 
                    {0, 0, filename}, Severity::ERROR);
        }
        return;
}

void SemanticsManager::run() {
    auto std_lib = managers.build_in.get_standard_module("std");
    Module& mod = managers.source.modules[filename];
    SymbolTable table_main(std_lib, filename);
    mod.scope = table_main.get_global_scope();

    DefinitionVisitor definition_visitor(table_main, managers); 
    mod.status = ModuleStatus::LOADING;
    program->accept(definition_visitor);
    mod.status = ModuleStatus::LOADED;
    managers.source.active_index(mod);

    if (mod.is_root) {
        validate_entry_point(mod.scope, filename);
    }

    std::vector<ModuleReference> sort_moduls(managers.source.modules.size());
    for(const auto& [path, mod]: managers.source.modules){
        sort_moduls[mod.index] = {&path, &mod};
    }
    
    

}
