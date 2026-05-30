#include "../../include/semantics/visitors/base.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"


BaseVisitorSemantics::BaseVisitorSemantics(SymbolTable& table, 
    Managers& managers) : table(table), managers(managers) {} 

void BaseVisitorSemantics::visit(ProgramNode& node) {
    for (auto& n : node.statements) {
        if(n) n->accept(*this);
    }
}
