#ifndef OPTIMIZATION_VISITOR_HPP
#define OPTIMIZATION_VISITOR_HPP

#include "base.hpp"


class OptimizationVisitor : public BaseVisitorSemantics{
private:

public:
    OptimizationVisitor(SymbolTable& table, Managers& managers);
    
    void visit(MakeNodeAST& node) override;
    void visit(LiteralNodeAST& node) override;
    void visit(IdentifierNodeAST& node) override;
    void visit(UnaryOperationNodeAST& node) override;
    void visit(BinaryOperationNodeAST& node) override;
    void visit(BlockNodeAST& node) override;
    void visit(IfElseNodeAST& node) override;
    void visit(TernaryOperationNodeAST& node) override;
    void visit(ExpressionStatementNodeAST& node) override;
    void visit(FunctionNodeAST& node) override;
    void visit(ReturnNodeAST& node) override;
    void visit(CallOperationNodeAST& node) override;
    void visit(WhileNodeAST& node) override;
    void visit(ForNodeAST& node) override;
    void visit(BreakNodeAST& node) override;
    void visit(ContinueNodeAST& node) override;
    void visit(ThrowNodeAST& node) override;
    void visit(TryNodeAST& node) override;
    void visit(UseNodeAST& node) override;
    void visit(ClassNodeAST& node) override;
    void visit(MatchNodeAST& node) override;
    void visit(TestNodeAST& node) override;
    void visit(AssertNodeAST& node) override;
    void visit(RangeOperationNodeAST& node) override;
};

#endif