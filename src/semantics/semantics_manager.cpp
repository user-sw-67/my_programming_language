#include "../../include/semantics/semantics_manager.hpp"
#include "../../include/semantics/semantics_visitor.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"


SemanticsManager::SemanticsManager(std::unique_ptr<ProgramNode>& program, 
        const std::string& filename, Managers& managers) : 
            program(program), filename(filename), 
                    managers(managers) {}

void SemanticsManager::run() {
    auto std_lib = managers.build_in.get_standard_module("std");
    SymbolTable table_main(std_lib);
    managers.source.modules[filename].scope = table_main.get_global_scope();

    DefinitionVisitor definition_visitor(table_main, managers); 
    managers.source.modules[filename].status = ModuleStatus::LOADING;
    program->accept(definition_visitor);
    managers.source.modules[filename].status = ModuleStatus::LOADED;
}
