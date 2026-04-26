#ifndef AST
#define AST

#include <vector>
#include <memory>

#include "token_list.hpp"
#include "visitor.hpp"


// class WhileNodeAST : public StatementNodeAST {};
// class DoWhileNodeAST : public StatementNodeAST {};
// class BreakNodeAST : public StatementNodeAST {};
// class ContinueNodeAST : public StatementNodeAST {};
// class UseNodeAST : public StatementNodeAST {};
// class TryCatchNodeAST : public StatementNodeAST {};

// class ClassNodeAST : public StatementNodeAST {};

// class MatchCaseNodeAST : public StatementNodeAST {};

// class TestNodeAST : public StatementNodeAST {};
// class AssertNodeAST : public StatementNodeAST {};




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









class BlockNodeAST : public StatementNodeAST {
public:
    std::vector<std::unique_ptr<StatementNodeAST>> statements;

    BlockNodeAST() = default;

    void add_statement(std::unique_ptr<StatementNodeAST>&& stmt) {
        if (stmt) {
            statements.push_back(std::move(stmt));
        }
    }

    void visit(Visitor& v) override { 
        v.visit(*this); 
    }
};


class ExpressionStatementNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> expression;

    ExpressionStatementNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& expression) :
            expression(std::move(expression)) {}

    void visit(Visitor& v) override { 
        v.visit(*this); 
    }
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
            type_names(std::move(type_names)), 
            initializers(std::move(initializers)),
            is_const(is_const) {}

    void visit(Visitor& v) override {v.visit(*this);}
};


class IfElseNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> condition;
    std::unique_ptr<StatementNodeAST> then_branch;
    std::unique_ptr<StatementNodeAST> else_branch;

    IfElseNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& condition,
        std::unique_ptr<StatementNodeAST>&& then_branch,
        std::unique_ptr<StatementNodeAST>&& else_branch = nullptr): 
            condition(std::move(condition)),
            then_branch(std::move(then_branch)),
            else_branch(std::move(else_branch)) {}

    void visit(Visitor& v) override { v.visit(*this); }
};


struct Parameter {
    std::string name;
    std::string type;
    std::unique_ptr<ExpressionNodeAST> default_value;
    bool is_variadic;

    Parameter(
        const std::string& name,
        const std::string& type,
        std::unique_ptr<ExpressionNodeAST>&& default_value = nullptr,
        bool is_variadic = false) :
            name(name),
            type(type),
            default_value(std::move(default_value)),
            is_variadic(is_variadic) {}

    Parameter(Parameter&&) = default;
    Parameter& operator=(Parameter&&) = default;
    
    Parameter(const Parameter&) = delete;
    Parameter& operator=(const Parameter&) = delete;
};


class FunctionNodeAST : public StatementNodeAST {
public:
    std::string name;
    std::string return_type;
    std::vector<Parameter> parameters;
    std::unique_ptr<ExpressionNodeAST> when_condition;
    std::unique_ptr<StatementNodeAST> body;

    FunctionNodeAST(
        const std::string& name,
        const std::string& return_type,
        std::vector<Parameter>&& parameters,
        std::unique_ptr<ExpressionNodeAST>&& when_condition,
        std::unique_ptr<StatementNodeAST>&& body) :
            name(name),
            return_type(return_type),
            parameters(std::move(parameters)),
            when_condition(std::move(when_condition)),
            body(std::move(body)) {}

    void visit(Visitor& v) override { v.visit(*this); }
};


class ReturnNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> value;

    ReturnNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& value) : 
            value(std::move(value)) {}

    void visit(Visitor& v) override { v.visit(*this); }
};


class CallOperationNodeAST : public ExpressionNodeAST {
public:
    std::string name;
    std::vector<std::unique_ptr<ExpressionNodeAST>> args;

    CallOperationNodeAST(
        const std::string& name,
        std::vector<std::unique_ptr<ExpressionNodeAST>>&& args) :
            name(name),
            args(std::move(args)) {}

    void visit(Visitor& v) override { v.visit(*this); }
};


class LiteralNodeAST : public ExpressionNodeAST {
public:
    std::string value;

    LiteralNodeAST(
        const std::string& value) : 
            value(value) {}

    void visit(Visitor& v) override {v.visit(*this);}
};


class IdentifierNodeAST : public ExpressionNodeAST {
public:
    std::string name;

    IdentifierNodeAST(
        const std::string& name) : 
            name(name) {} 
    
    void visit(Visitor& v) override {v.visit(*this);}
};


class UnaryOperationNodeAST : public ExpressionNodeAST {
public:
    TokenType op;
    std::unique_ptr<ExpressionNodeAST> operand;

    UnaryOperationNodeAST(
        TokenType op, 
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

    BinaryOperationNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& left,
        TokenType op,
        std::unique_ptr<ExpressionNodeAST>&& right) : 
            op(op),
            left(std::move(left)),
            right(std::move(right)) {} 
    
    void visit(Visitor& v) override {v.visit(*this);}
};


class TernaryOperationNodeAST : public ExpressionNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> condition;
    std::unique_ptr<ExpressionNodeAST> true_branch;
    std::unique_ptr<ExpressionNodeAST> false_branch;

    TernaryOperationNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& condition,
        std::unique_ptr<ExpressionNodeAST>&& true_branch,
        std::unique_ptr<ExpressionNodeAST>&& false_branch): 
            condition(std::move(condition)),
            true_branch(std::move(true_branch)),
            false_branch(std::move(false_branch)) {}

    void visit(Visitor& v) override { v.visit(*this); }
};


#endif