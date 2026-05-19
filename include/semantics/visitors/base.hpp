#ifndef BASE_VISITOR_SEMANTICS_HPP
#define BASE_VISITOR_SEMANTICS_HPP

#include "../../base/visitor.hpp"
#include "../symbol_table.hpp"
#include "../../addition/error_manager.hpp"

#include <memory>


class BaseVisitorSemantics : public Visitor {
protected:
    SymbolTable& table;
    ErrorManager& error_manager;

    BaseVisitorSemantics(SymbolTable& table, ErrorManager& error_manager) : 
        table(table), error_manager(error_manager) {} 

public:
    void visit(ProgramNode& node) override {
        for (auto& n : node.statements) {
            n->accept(*this);
        }
    }
};

#endif