#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <memory>

class NodeAST;
class ProgramNode;
class MakeNodeAST;
class LiteralNodeAST;
class IdentifierNodeAST;
class UnaryOperationNodeAST;
class BinaryOperationNodeAST;
class BlockNodeAST;
class IfElseNodeAST;
class TernaryOperationNodeAST;
class ExpressionStatementNodeAST;
class FunctionNodeAST;
class ReturnNodeAST;
class CallOperationNodeAST;
class WhileNodeAST;
class ForNodeAST;
class BreakNodeAST;
class ContinueNodeAST;
class ThrowNodeAST;
class TryNodeAST;
class UseNodeAST;
class ClassNodeAST;
class MatchNodeAST;
class TestNodeAST;
class AssertNodeAST;
class RangeOperationNodeAST;


class Visitor{
public:
    virtual ~Visitor() = default;

    virtual void visit(ProgramNode& node) = 0;
    virtual void visit(MakeNodeAST& node) = 0;
    virtual void visit(LiteralNodeAST& node) = 0;
    virtual void visit(IdentifierNodeAST& node) = 0;
    virtual void visit(UnaryOperationNodeAST& node) = 0;
    virtual void visit(BinaryOperationNodeAST& node) = 0;
    virtual void visit(BlockNodeAST& node) = 0;
    virtual void visit(IfElseNodeAST& node) = 0;
    virtual void visit(TernaryOperationNodeAST& node) = 0;
    virtual void visit(ExpressionStatementNodeAST& node) = 0;
    virtual void visit(FunctionNodeAST& node) = 0;
    virtual void visit(ReturnNodeAST& node) = 0;
    virtual void visit(CallOperationNodeAST& node) = 0;
    virtual void visit(WhileNodeAST& node) = 0;
    virtual void visit(ForNodeAST& node) = 0;
    virtual void visit(BreakNodeAST& node) = 0;
    virtual void visit(ContinueNodeAST& node) = 0;
    virtual void visit(ThrowNodeAST& node) = 0;
    virtual void visit(TryNodeAST& node) = 0;
    virtual void visit(UseNodeAST& node) = 0;
    virtual void visit(ClassNodeAST& node) = 0;
    virtual void visit(MatchNodeAST& node) = 0;
    virtual void visit(TestNodeAST& node) = 0;
    virtual void visit(AssertNodeAST& node) = 0;
    virtual void visit(RangeOperationNodeAST& node) = 0;

};

class VisitorCarve {
protected:
    std::unique_ptr<NodeAST> dispatch(std::unique_ptr<NodeAST> node);

public:
    virtual ~VisitorCarve() = default;

    virtual void visit(
        std::unique_ptr<ProgramNode>& node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<MakeNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<LiteralNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<IdentifierNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<UnaryOperationNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<BinaryOperationNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<BlockNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<IfElseNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<TernaryOperationNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ExpressionStatementNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<FunctionNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ReturnNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<CallOperationNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<WhileNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ForNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<BreakNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ContinueNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ThrowNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<TryNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<UseNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<ClassNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<MatchNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<TestNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<AssertNodeAST> node) = 0;

    virtual std::unique_ptr<NodeAST> visit(
        std::unique_ptr<RangeOperationNodeAST> node) = 0;

};

#endif