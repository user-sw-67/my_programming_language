#ifndef MERMAID_VISITOR_HPP
#define MERMAID_VISITOR_HPP

#include "../base/visitor.hpp"
#include "../parser/ast.hpp"

#include <iostream>
#include <string>
#include <stack>
#include <fstream>


class SourceLocation;


class MermaidVisitor : public Visitor {
private:
    std::ostream& out;
    int node_count = 0;
    std::stack<std::string> parent_stack;

    std::string next_id();

    std::string format_loc(const SourceLocation& loc);

    void add_node(const std::string& id, const std::string& label, 
                  const SourceLocation& loc, const std::string& shape = "[]", 
                  const std::string& link_label = "");

    void visit_child(NodeAST& node, const std::string& current_id, 
                     const std::string& label);

    std::string op_to_str(TokenType type);

public:
    MermaidVisitor(std::ostream& output = std::cout);
    
    void start();
    
    void visit(ProgramNode& node) override;
    void visit(BlockNodeAST& node) override;
    void visit(ExpressionStatementNodeAST& node) override;
    void visit(MakeNodeAST& node) override;
    void visit(FunctionNodeAST& node) override;
    void visit(ReturnNodeAST& node) override;
    void visit(IfElseNodeAST& node) override;
    void visit(BinaryOperationNodeAST& node) override;
    void visit(UnaryOperationNodeAST& node) override;
    void visit(TernaryOperationNodeAST& node) override;
    void visit(CallOperationNodeAST& node) override;
    void visit(LiteralNodeAST& node) override;
    void visit(IdentifierNodeAST& node) override;
    void visit(WhileNodeAST& node) override;
    void visit(RangeOperationNodeAST& node) override;
    void visit(ForNodeAST& node) override;
    void visit(BreakNodeAST& node) override;
    void visit(ContinueNodeAST& node) override;
    void visit(TryNodeAST& node) override;
    void visit(ThrowNodeAST& node) override;
    void visit(UseNodeAST& node) override;
    void visit(ClassNodeAST& node) override;
    void visit(MatchNodeAST& node) override;
    void visit(TestNodeAST& node) override;
    void visit(AssertNodeAST& node) override;
};

#endif