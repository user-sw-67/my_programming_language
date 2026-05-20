#include "../../include/semantics/visitors/optimization_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/parser/ast.hpp"


OptimizationVisitor::OptimizationVisitor(SymbolTable& table, 
    ErrorManager& error_manager) : BaseVisitorSemantics(table, error_manager) {}

void OptimizationVisitor::visit(MakeNodeAST& node) {}

void OptimizationVisitor::visit(LiteralNodeAST& node) {}

void OptimizationVisitor::visit(IdentifierNodeAST& node) {}

void OptimizationVisitor::visit(UnaryOperationNodeAST& node) {}

void OptimizationVisitor::visit(BinaryOperationNodeAST& node) {}

void OptimizationVisitor::visit(BlockNodeAST& node) {}

void OptimizationVisitor::visit(IfElseNodeAST& node) {}

void OptimizationVisitor::visit(TernaryOperationNodeAST& node) {}

void OptimizationVisitor::visit(ExpressionStatementNodeAST& node) {}

void OptimizationVisitor::visit(FunctionNodeAST& node) {}

void OptimizationVisitor::visit(ReturnNodeAST& node) {}

void OptimizationVisitor::visit(CallOperationNodeAST& node) {}

void OptimizationVisitor::visit(WhileNodeAST& node) {}

void OptimizationVisitor::visit(ForNodeAST& node) {}

void OptimizationVisitor::visit(BreakNodeAST& node) {}

void OptimizationVisitor::visit(ContinueNodeAST& node) {}

void OptimizationVisitor::visit(ThrowNodeAST& node) {}

void OptimizationVisitor::visit(TryNodeAST& node) {}

void OptimizationVisitor::visit(UseNodeAST& node) {}

void OptimizationVisitor::visit(ClassNodeAST& node) {}

void OptimizationVisitor::visit(MatchNodeAST& node) {}

void OptimizationVisitor::visit(TestNodeAST& node) {}

void OptimizationVisitor::visit(AssertNodeAST& node) {}

void OptimizationVisitor::visit(RangeOperationNodeAST& node) {}
