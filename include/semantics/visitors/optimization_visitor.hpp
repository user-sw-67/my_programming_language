#ifndef OPTIMIZATION_VISITOR_HPP
#define OPTIMIZATION_VISITOR_HPP

#include "base.hpp"
#include "../../lexer/lexer.hpp"


class OptimizationVisitor : public VisitorCarve{
private:
    Managers& managers;

    std::unique_ptr<LiteralNodeAST> calculate(
        LiteralNodeAST* left, TokenType op, 
            LiteralNodeAST* right, SourceLocation loc);

    bool literal_cast(LiteralNodeAST* l);

public:
    OptimizationVisitor(Managers& managers);

    void visit(
        std::unique_ptr<ProgramNode>& node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<MakeNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<LiteralNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<IdentifierNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<UnaryOperationNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<BinaryOperationNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<BlockNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<IfElseNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<TernaryOperationNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ExpressionStatementNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<FunctionNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ReturnNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<CallOperationNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<WhileNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ForNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<BreakNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ContinueNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ThrowNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<TryNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<UseNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ClassNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<MatchNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<TestNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<AssertNodeAST> node) override;

    std::unique_ptr<NodeAST> visit(
        std::unique_ptr<RangeOperationNodeAST> node) override;

};

#endif