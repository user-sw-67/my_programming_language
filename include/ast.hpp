#ifndef AST
#define AST

#include <vector>
#include <memory>

#include "token_list.hpp"
#include "visitor.hpp"


struct SourceLocation {
    size_t line;
    size_t column;

    SourceLocation(
        size_t line = 0, 
        size_t column = 0) : 
            line(line), 
            column(column) {}

    bool operator == (const SourceLocation& other) const {
        return (other.line == line) && (other.column == column);
    }

    bool operator != (const SourceLocation& other) const {
        return !(other == *this);
    }
};


class NodeAST{
public:
    SourceLocation location;

    NodeAST(SourceLocation location) : 
        location(location) {}

    virtual ~NodeAST() = default;

    virtual void accept(Visitor& v) = 0;
};


class ExpressionNodeAST : public NodeAST {
public:
    ExpressionNodeAST(SourceLocation location) : 
        NodeAST(location) {}
};


class StatementNodeAST : public NodeAST {
public:
    StatementNodeAST(SourceLocation location) : 
        NodeAST(location) {}
};


class ProgramNode : public NodeAST {
public:
    ProgramNode(SourceLocation location = SourceLocation(0, 0)) : 
        NodeAST(location) {}

    std::vector<std::unique_ptr<StatementNodeAST>> statements;

    void accept(Visitor& v) override {v.visit(*this);}
};


class BlockNodeAST : public StatementNodeAST {
public:
    BlockNodeAST(SourceLocation location) : 
        StatementNodeAST(location) {}

    std::vector<std::unique_ptr<StatementNodeAST>> statements;

    void add_statement(std::unique_ptr<StatementNodeAST>&& stmt) {
        if (stmt) {
            statements.push_back(std::move(stmt));
        }
    }

    void accept(Visitor& v) override { 
        v.visit(*this); 
    }
};


class ExpressionStatementNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> expression;

    ExpressionStatementNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& expression,
        SourceLocation location) :
            StatementNodeAST(location),
            expression(std::move(expression)) {}

    void accept(Visitor& v) override { 
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
        bool is_const,
        SourceLocation location) : 
            StatementNodeAST(location),
            names(std::move(names)), 
            type_names(std::move(type_names)), 
            initializers(std::move(initializers)),
            is_const(is_const) {}

    void accept(Visitor& v) override {v.visit(*this);}
};


class IfElseNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> condition;
    std::unique_ptr<StatementNodeAST> then_branch;
    std::unique_ptr<StatementNodeAST> else_branch;

    IfElseNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& condition,
        std::unique_ptr<StatementNodeAST>&& then_branch,
        std::unique_ptr<StatementNodeAST>&& else_branch = nullptr,
        SourceLocation location = SourceLocation(0, 0)): 
            StatementNodeAST(location),
            condition(std::move(condition)),
            then_branch(std::move(then_branch)),
            else_branch(std::move(else_branch)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


struct Parameter {
    SourceLocation location;
    std::string name;
    std::string type;
    std::unique_ptr<ExpressionNodeAST> default_value;
    bool is_variadic;

    Parameter(
        const std::string& name,
        const std::string& type,
        std::unique_ptr<ExpressionNodeAST>&& default_value = nullptr,
        bool is_variadic = false,
        SourceLocation location = SourceLocation(0, 0)) :
            location(location),
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
        std::unique_ptr<StatementNodeAST>&& body,
        SourceLocation location) :
            StatementNodeAST(location),
            name(name),
            return_type(return_type),
            parameters(std::move(parameters)),
            when_condition(std::move(when_condition)),
            body(std::move(body)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class ReturnNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> value;

    ReturnNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& value,
        SourceLocation location) : 
            StatementNodeAST(location),
            value(std::move(value)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class WhileNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> condition;
    std::unique_ptr<StatementNodeAST> body;
    bool is_do_while;

    WhileNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& condition, 
        std::unique_ptr<StatementNodeAST>&& body, 
        bool is_do_while = false,
        SourceLocation location = SourceLocation(0, 0)) : 
            StatementNodeAST(location),
            condition(std::move(condition)), 
            body(std::move(body)), 
            is_do_while(is_do_while) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class ForNodeAST : public StatementNodeAST {
public:
    std::string name_var;
    std::unique_ptr<ExpressionNodeAST> iterable;
    std::unique_ptr<StatementNodeAST> body;

    ForNodeAST(
        const std::string& name_var,
        std::unique_ptr<ExpressionNodeAST>&& iterable,
        std::unique_ptr<StatementNodeAST>&& body,
        SourceLocation location) :
            StatementNodeAST(location),
            name_var(name_var),
            iterable(std::move(iterable)),
            body(std::move(body)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class BreakNodeAST : public StatementNodeAST {
public:
    BreakNodeAST(SourceLocation location) : 
        StatementNodeAST(location) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class ContinueNodeAST : public StatementNodeAST {
public:
    ContinueNodeAST(SourceLocation location) :
        StatementNodeAST(location) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class TryNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<StatementNodeAST> try_block;
    std::unique_ptr<ExpressionNodeAST> catch_expr;
    std::unique_ptr<StatementNodeAST> catch_block;
    std::unique_ptr<StatementNodeAST> finally_block;

    TryNodeAST(
        std::unique_ptr<StatementNodeAST>&& try_block,
        std::unique_ptr<ExpressionNodeAST>&& catch_expr,
        std::unique_ptr<StatementNodeAST>&& catch_block,
        std::unique_ptr<StatementNodeAST>&& finally_block,
        SourceLocation location) :
            StatementNodeAST(location),
            try_block(std::move(try_block)),
            catch_expr(std::move(catch_expr)),
            catch_block(std::move(catch_block)),
            finally_block(std::move(finally_block)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class ThrowNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> value;

    ThrowNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& value,
        SourceLocation location) : 
            StatementNodeAST(location),
            value(std::move(value)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


struct ImportObject {
    SourceLocation location;
    std::string internal_name;
    std::string alias;

    ImportObject(
        const std::string& internal_name,
        const std::string& alias,
        SourceLocation location) :
            location(location),
            internal_name(internal_name),
            alias(alias) {}
};


class UseNodeAST : public StatementNodeAST {
public:
    std::string path_lib;
    std::vector<ImportObject> objects;
    std::string as_name;

    UseNodeAST(
        const std::string& path_lib,
        std::vector<ImportObject>&& objects,
        const std::string& as_name,
        SourceLocation location) :
            StatementNodeAST(location), 
            path_lib(path_lib),
            objects(objects),
            as_name(as_name) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


struct ClassMember {
    SourceLocation location;
    std::string access_modifier;
    bool is_static;
    bool is_getter;
    bool is_setter;
    std::unique_ptr<StatementNodeAST> member_node;

    ClassMember(
        const std::string& access_modifier,
        bool is_static,
        bool is_getter,
        bool is_setter,
        std::unique_ptr<StatementNodeAST>&& member_node,
        SourceLocation location) :
            location(location),
            access_modifier(access_modifier),
            is_static(is_static),
            is_getter(is_getter),
            is_setter(is_setter),
            member_node(std::move(member_node)) {}
};


class ClassNodeAST : public StatementNodeAST {
public:
    std::string name;
    std::string base_class_name;
    std::vector<ClassMember> members;

    ClassNodeAST(
        const std::string& name, 
        const std::string& base_class,
        std::vector<ClassMember>&& members,
        SourceLocation location) : 
            StatementNodeAST(location),
            name(name), 
            base_class_name(base_class),
            members(std::move(members)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


struct Case{
    SourceLocation location;
    std::unique_ptr<ExpressionNodeAST> value;
    std::unique_ptr<StatementNodeAST> body;

    Case(
        std::unique_ptr<ExpressionNodeAST>&& value,
        std::unique_ptr<StatementNodeAST>&& body,
        SourceLocation location) :
            location(location), 
            value(std::move(value)),
            body(std::move(body)) {}
};


class MatchNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> value;
    std::vector<Case> cases;

    MatchNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& value,
        std::vector<Case>&& cases,
        SourceLocation location) :
            StatementNodeAST(location),
            value(std::move(value)),
            cases(std::move(cases)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class TestNodeAST : public StatementNodeAST {
public:
    std::string name;
    std::unique_ptr<StatementNodeAST> body;

    TestNodeAST(
        const std::string& name,
        std::unique_ptr<StatementNodeAST>&& body,
        SourceLocation location) :
            StatementNodeAST(location), 
            name(name),
            body(std::move(body)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class AssertNodeAST : public StatementNodeAST {
public:
    std::unique_ptr<ExpressionNodeAST> value;

    AssertNodeAST(
        std::unique_ptr<ExpressionNodeAST>&& value,
        SourceLocation location) : 
            StatementNodeAST(location),
            value(std::move(value)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


class CallOperationNodeAST : public ExpressionNodeAST {
public:
    std::string name;
    std::vector<std::unique_ptr<ExpressionNodeAST>> args;

    CallOperationNodeAST(
        const std::string& name,
        std::vector<std::unique_ptr<ExpressionNodeAST>>&& args,
        SourceLocation location) :
            ExpressionNodeAST(location),
            name(name),
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
        SourceLocation location) : 
            ExpressionNodeAST(location),
            value(value),
            literal_type(literal_type) {}

    void accept(Visitor& v) override {v.visit(*this);}
};


class IdentifierNodeAST : public ExpressionNodeAST {
public:
    std::string name;

    IdentifierNodeAST(
        const std::string& name,
        SourceLocation location) : 
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
        SourceLocation location) : 
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
        SourceLocation location) : 
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
        SourceLocation location): 
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
        SourceLocation location) :
            ExpressionNodeAST(location),
            start(std::move(start)), 
            end(std::move(end)),
            step(std::move(step)) {}

    void accept(Visitor& v) override { v.visit(*this); }
};


#endif