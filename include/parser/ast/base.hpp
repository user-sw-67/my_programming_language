#ifndef AST_BASE_HPP
#define AST_BASE_HPP

#include "../../addition/source_manager.hpp"
#include "../../base/visitor.hpp"

#include <memory>
#include <vector>


class NodeAST{
public:
    SourceLocation location;

    NodeAST(const SourceLocation& location) : 
        location(location) {}

    virtual ~NodeAST() = default;

    virtual void accept(Visitor& v) = 0;
};


class ExpressionNodeAST : public NodeAST {
public:
    ExpressionNodeAST(const SourceLocation& location) : 
        NodeAST(location) {}
};


class StatementNodeAST : public NodeAST {
public:
    StatementNodeAST(const SourceLocation& location) : 
        NodeAST(location) {}
};


class ProgramNode : public NodeAST {
public:
    std::vector<std::unique_ptr<StatementNodeAST>> statements;

    ProgramNode(const SourceLocation& location) : 
        NodeAST(location) {}

    void accept(Visitor& v) override {v.visit(*this);}
};

#endif