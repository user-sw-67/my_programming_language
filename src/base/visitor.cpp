#include "../../include/base/visitor.hpp"
#include "../../include/parser/ast.hpp"

std::unique_ptr<NodeAST> VisitorCarve::dispatch(std::unique_ptr<NodeAST> node) {
    if (!node) return nullptr;

    if (dynamic_cast<MakeNodeAST*>(node.get())) {
        return visit(std::unique_ptr<MakeNodeAST>(
            static_cast<MakeNodeAST*>(node.release())));
    }
    if (dynamic_cast<LiteralNodeAST*>(node.get())) {
        return visit(std::unique_ptr<LiteralNodeAST>(
            static_cast<LiteralNodeAST*>(node.release())));
    }
    if (dynamic_cast<IdentifierNodeAST*>(node.get())) {
        return visit(std::unique_ptr<IdentifierNodeAST>(
            static_cast<IdentifierNodeAST*>(node.release())));
    }
    if (dynamic_cast<UnaryOperationNodeAST*>(node.get())) {
        return visit(std::unique_ptr<UnaryOperationNodeAST>(
            static_cast<UnaryOperationNodeAST*>(node.release())));
    }
    if (dynamic_cast<BinaryOperationNodeAST*>(node.get())) {
        return visit(std::unique_ptr<BinaryOperationNodeAST>(
            static_cast<BinaryOperationNodeAST*>(node.release())));
    }
    if (dynamic_cast<BlockNodeAST*>(node.get())) {
        return visit(std::unique_ptr<BlockNodeAST>(
            static_cast<BlockNodeAST*>(node.release())));
    }
    if (dynamic_cast<IfElseNodeAST*>(node.get())) {
        return visit(std::unique_ptr<IfElseNodeAST>(
            static_cast<IfElseNodeAST*>(node.release())));
    }
    if (dynamic_cast<TernaryOperationNodeAST*>(node.get())) {
        return visit(std::unique_ptr<TernaryOperationNodeAST>(
            static_cast<TernaryOperationNodeAST*>(node.release())));
    }
    if (dynamic_cast<ExpressionStatementNodeAST*>(node.get())) {
        return visit(std::unique_ptr<ExpressionStatementNodeAST>(
            static_cast<ExpressionStatementNodeAST*>(node.release())));
    }
    if (dynamic_cast<FunctionNodeAST*>(node.get())) {
        return visit(std::unique_ptr<FunctionNodeAST>(
            static_cast<FunctionNodeAST*>(node.release())));
    }
    if (dynamic_cast<ReturnNodeAST*>(node.get())) {
        return visit(std::unique_ptr<ReturnNodeAST>(
            static_cast<ReturnNodeAST*>(node.release())));
    }
    if (dynamic_cast<CallOperationNodeAST*>(node.get())) {
        return visit(std::unique_ptr<CallOperationNodeAST>(
            static_cast<CallOperationNodeAST*>(node.release())));
    }
    if (dynamic_cast<WhileNodeAST*>(node.get())) {
        return visit(std::unique_ptr<WhileNodeAST>(
            static_cast<WhileNodeAST*>(node.release())));
    }
    if (dynamic_cast<ForNodeAST*>(node.get())) {
        return visit(std::unique_ptr<ForNodeAST>(
            static_cast<ForNodeAST*>(node.release())));
    }
    if (dynamic_cast<BreakNodeAST*>(node.get())) {
        return visit(std::unique_ptr<BreakNodeAST>(
            static_cast<BreakNodeAST*>(node.release())));
    }
    if (dynamic_cast<ContinueNodeAST*>(node.get())) {
        return visit(std::unique_ptr<ContinueNodeAST>(
            static_cast<ContinueNodeAST*>(node.release())));
    }
    if (dynamic_cast<ThrowNodeAST*>(node.get())) {
        return visit(std::unique_ptr<ThrowNodeAST>(
            static_cast<ThrowNodeAST*>(node.release())));
    }
    if (dynamic_cast<TryNodeAST*>(node.get())) {
        return visit(std::unique_ptr<TryNodeAST>(
            static_cast<TryNodeAST*>(node.release())));
    }
    if (dynamic_cast<UseNodeAST*>(node.get())) {
        return visit(std::unique_ptr<UseNodeAST>(
            static_cast<UseNodeAST*>(node.release())));
    }
    if (dynamic_cast<ClassNodeAST*>(node.get())) {
        return visit(std::unique_ptr<ClassNodeAST>(
            static_cast<ClassNodeAST*>(node.release())));
    }
    if (dynamic_cast<MatchNodeAST*>(node.get())) {
        return visit(std::unique_ptr<MatchNodeAST>(
            static_cast<MatchNodeAST*>(node.release())));
    }
    if (dynamic_cast<TestNodeAST*>(node.get())) {
        return visit(std::unique_ptr<TestNodeAST>(
            static_cast<TestNodeAST*>(node.release())));
    }
    if (dynamic_cast<AssertNodeAST*>(node.get())) {
        return visit(std::unique_ptr<AssertNodeAST>(
            static_cast<AssertNodeAST*>(node.release())));
    }
    if (dynamic_cast<RangeOperationNodeAST*>(node.get())) {
        return visit(std::unique_ptr<RangeOperationNodeAST>(
            static_cast<RangeOperationNodeAST*>(node.release())));
    }

    return node;
}