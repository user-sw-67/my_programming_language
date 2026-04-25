#ifndef VISITOR
#define VISITOR

class ProgramNode;
class MakeNodeAST;
class LiteralNodeAST;
class IdentifierNodeAST;
class UnaryOperationNodeAST;
class BinaryOperationNodeAST;

class Visitor{
public:
    virtual ~Visitor() = default;

    virtual void visit(ProgramNode& node) = 0;
    virtual void visit(MakeNodeAST& node) = 0;
    virtual void visit(LiteralNodeAST& node) = 0;
    virtual void visit(IdentifierNodeAST& node) = 0;
    virtual void visit(UnaryOperationNodeAST& node) = 0;
    virtual void visit(BinaryOperationNodeAST& node) = 0;
};

#endif