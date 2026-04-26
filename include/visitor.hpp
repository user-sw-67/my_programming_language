#ifndef VISITOR
#define VISITOR

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
class RangeNodeAST;
class BreakNodeAST;
class ContinueNodeAST;
class ThrowNodeAST;
class TryNodeAST;
class UseNodeAST;

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
    virtual void visit(RangeNodeAST& node) = 0;
    virtual void visit(BreakNodeAST& node) = 0;
    virtual void visit(ContinueNodeAST& node) = 0;
    virtual void visit(ThrowNodeAST& node) = 0;
    virtual void visit(TryNodeAST& node) = 0;
    virtual void visit(UseNodeAST& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;
    // virtual void visit(& node) = 0;

};

#endif