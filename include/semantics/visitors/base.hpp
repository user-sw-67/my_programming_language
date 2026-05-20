#ifndef BASE_VISITOR_SEMANTICS_HPP
#define BASE_VISITOR_SEMANTICS_HPP

#include "../../base/visitor.hpp"

#include <memory>


class SymbolTable;
class ErrorManager;
class ProgramNode;


class BaseVisitorSemantics : public Visitor {
protected:
    SymbolTable& table;
    ErrorManager& error_manager;

    BaseVisitorSemantics(SymbolTable& table, ErrorManager& error_manager);

public:

    void visit(ProgramNode& node) override;

};

#endif