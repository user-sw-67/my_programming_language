#ifndef AST_EXPRESSIONS_HPP
#define AST_EXPRESSIONS_HPP

#include "base.hpp"
#include "../../lexer/token_list.hpp"

class SymbolInfo;


class CallOperationNodeAST : public ExpressionNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> callee;
    std::vector<std::unique_ptr<ExpressionNodeAST>> args;

    CallOperationNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& callee,
        std::vector<std::unique_ptr<ExpressionNodeAST>>&& args,
        const SourceLocation& location) :
            ExpressionNodeAST(location),
            callee(std::move(callee)),
            args(std::move(args)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class LiteralNodeAST : public ExpressionNodeAST {
public:
    std::string value;
    TokenType literal_type;

    LiteralNodeAST(
        const std::string& value,
        const TokenType& literal_type,
        const SourceLocation& location) : 
            ExpressionNodeAST(location),
            value(value),
            literal_type(literal_type) {}

    void accept(Visitor& v) override {v.visit(*this);}
};


enum class IdentifierKind{
    LOCAL,
    GLOBAL,
    FIELD,
    CONSTANT
};


class IdentifierNodeAST : public ExpressionNodeAST {
public:
    std::string name;
    size_t slot_index = 0;
    
    IdentifierKind kind;
    SymbolInfo* resolved_symbol = nullptr;

    IdentifierNodeAST(
        const std::string& name,
        const SourceLocation& location) : 
            ExpressionNodeAST(location),
            name(name) {} 
    
    void accept(Visitor& v) override {v.visit(*this);}
};


class UnaryOperationNodeAST : public ExpressionNodeAST {
public:
    TokenType op;
    std::unique_ptr<ExpressionNodeAST> operand;

    UnaryOperationNodeAST(
        TokenType op, 
        std::unique_ptr<ExpressionNodeAST>&& operand,
        const SourceLocation& location) : 
            ExpressionNodeAST(location),
            op(op),
            operand(std::move(operand)) {} 
    
    void accept(Visitor& v) override {v.visit(*this);}
};


class BinaryOperationNodeAST : public ExpressionNodeAST {
public:
    TokenType op;
    std::unique_ptr<ExpressionNodeAST> left;
    std::unique_ptr<ExpressionNodeAST> right;

    BinaryOperationNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& left,
        TokenType op,
        std::unique_ptr<ExpressionNodeAST>&& right,
        const SourceLocation& location) : 
            ExpressionNodeAST(location),
            op(op),
            left(std::move(left)),
            right(std::move(right)) {} 
    
    void accept(Visitor& v) override {v.visit(*this);}
};


class TernaryOperationNodeAST : public ExpressionNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> condition;
    std::unique_ptr<ExpressionNodeAST> true_branch;
    std::unique_ptr<ExpressionNodeAST> false_branch;

    TernaryOperationNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& condition,
        std::unique_ptr<ExpressionNodeAST>&& true_branch,
        std::unique_ptr<ExpressionNodeAST>&& false_branch,
        const SourceLocation& location): 
            ExpressionNodeAST(location),
            condition(std::move(condition)),
            true_branch(std::move(true_branch)),
            false_branch(std::move(false_branch)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class RangeOperationNodeAST : public ExpressionNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> start;
    std::unique_ptr<ExpressionNodeAST> end;
    std::unique_ptr<ExpressionNodeAST> step;

    RangeOperationNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& start, 
        std::unique_ptr<ExpressionNodeAST>&& end,
        std::unique_ptr<ExpressionNodeAST> step,
        const SourceLocation& location) :
            ExpressionNodeAST(location),
            start(std::move(start)), 
            end(std::move(end)),
            step(std::move(step)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};

#endif