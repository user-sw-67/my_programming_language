#ifndef AST
#define AST

#include <vector>
#include <memory>

#include "token_list.hpp"
#include "visitor.hpp"

// class ForNodeAST : public StatementNodeAST {};
// class WhileNodeAST : public StatementNodeAST {};
// class DoWhileNodeAST : public StatementNodeAST {};
// class BreakNodeAST : public StatementNodeAST {};
// class ContinueNodeAST : public StatementNodeAST {};
// class UseNodeAST : public StatementNodeAST {};
// class FunctionsNodeAST : public StatementNodeAST {};
// class TryCatchNodeAST : public StatementNodeAST {};

// class ClassNodeAST : public StatementNodeAST {};

// class MatchCaseNodeAST : public StatementNodeAST {};

// class TestNodeAST : public StatementNodeAST {};
// class AssertNodeAST : public StatementNodeAST {};

// class TernaryOperationNodeAST : public ExpressionNodeAST{};



class NodeAST{
public:
    virtual ~NodeAST() = default;

    virtual void visit(Visitor& v) = 0;
};

class ExpressionNodeAST : public NodeAST {};

class StatementNodeAST : public NodeAST {};

class ProgramNode : public NodeAST {
public:
    std::vector<std::unique_ptr<StatementNodeAST>> statements;

    void visit(Visitor& v) override {v.visit(*this);}
};






class MakeNodeAST : public StatementNodeAST {
public:
    std::vector<std::string> names;
    std::vector<std::string> type_names;
    std::vector<std::unique_ptr<ExpressionNodeAST>> initializers;
    bool is_const;

    MakeNodeAST(
        std::vector<std::string>&& names, 
        std::vector<std::string>&& type_names,
        std::vector<std::unique_ptr<ExpressionNodeAST>>&& initializers,
        bool is_const) : 
            names(std::move(names)), 
            type_names(type_names), 
            initializers(std::move(initializers)),
            is_const(is_const) {}

    void visit(Visitor& v) override {v.visit(*this);}
};


// class BlockNodeAST : public StatementNodeAST {};
// class IfElseNodeAST : public StatementNodeAST {};







class LiteralNodeAST : public ExpressionNodeAST {
public:
    std::string value;

    LiteralNodeAST(const std::string& value) : value(value) {}

    void visit(Visitor& v) override {v.visit(*this);}
};


class IdentifierNodeAST : public ExpressionNodeAST {
public:
    std::string name;

    IdentifierNodeAST(const std::string& name) : name(name) {} 
    
    void visit(Visitor& v) override {v.visit(*this);}
};


class UnaryOperationNodeAST : public ExpressionNodeAST {
public:
    TokenType op;
    std::unique_ptr<ExpressionNodeAST> operand;

    UnaryOperationNodeAST(TokenType op, 
        std::unique_ptr<ExpressionNodeAST>&& operand) : 
            op(op),
            operand(std::move(operand)) {} 
    
    void visit(Visitor& v) override {v.visit(*this);}
};


class BinaryOperationNodeAST : public ExpressionNodeAST {
public:
    TokenType op;
    std::unique_ptr<ExpressionNodeAST> left;
    std::unique_ptr<ExpressionNodeAST> right;

    BinaryOperationNodeAST(std::unique_ptr<ExpressionNodeAST>&& left,
        TokenType op, std::unique_ptr<ExpressionNodeAST>&& right) : 
            op(op),
            left(std::move(left)),
            right(std::move(right)) {} 
    
    void visit(Visitor& v) override {v.visit(*this);}
};

#endif