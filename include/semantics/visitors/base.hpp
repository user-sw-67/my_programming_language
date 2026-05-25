#ifndef BASE_VISITOR_SEMANTICS_HPP
#define BASE_VISITOR_SEMANTICS_HPP

#include "../../base/visitor.hpp"

#include <memory>


class SymbolTable;
class ErrorManager;
class ProgramNode;
class Managers;


class BaseVisitorSemantics : public Visitor {
protected:
    SymbolTable& table;
    Managers& managers;

    BaseVisitorSemantics(SymbolTable& table, Managers& managers);

public:

    void visit(ProgramNode& node) override;

};

#endif