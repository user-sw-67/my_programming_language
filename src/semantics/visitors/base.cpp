#include "../../include/semantics/visitors/base.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/parser/ast.hpp"


BaseVisitorSemantics::BaseVisitorSemantics(SymbolTable& table, 
    ErrorManager& error_manager) : table(table), error_manager(error_manager) {} 

void BaseVisitorSemantics::visit(ProgramNode& node) {
    for (auto& n : node.statements) {
        n->accept(*this);
    }
}
