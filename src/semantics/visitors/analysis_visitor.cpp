#include "../../include/semantics/visitors/analysis_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"


AnalysisVisitor::AnalysisVisitor(SymbolTable& table, Managers& managers) : 
    BaseVisitorSemantics(table, managers) {}

void AnalysisVisitor::visit(MakeNodeAST& node) {}

void AnalysisVisitor::visit(LiteralNodeAST& node) {}

void AnalysisVisitor::visit(IdentifierNodeAST& node) {}

void AnalysisVisitor::visit(UnaryOperationNodeAST& node) {}

void AnalysisVisitor::visit(BinaryOperationNodeAST& node) {}

void AnalysisVisitor::visit(BlockNodeAST& node) {}

void AnalysisVisitor::visit(IfElseNodeAST& node) {}

void AnalysisVisitor::visit(TernaryOperationNodeAST& node) {}

void AnalysisVisitor::visit(ExpressionStatementNodeAST& node) {}

void AnalysisVisitor::visit(FunctionNodeAST& node) {}

void AnalysisVisitor::visit(ReturnNodeAST& node) {}

void AnalysisVisitor::visit(CallOperationNodeAST& node) {}

void AnalysisVisitor::visit(WhileNodeAST& node) {}

void AnalysisVisitor::visit(ForNodeAST& node) {}

void AnalysisVisitor::visit(BreakNodeAST& node) {}

void AnalysisVisitor::visit(ContinueNodeAST& node) {}

void AnalysisVisitor::visit(ThrowNodeAST& node) {}

void AnalysisVisitor::visit(TryNodeAST& node) {}

void AnalysisVisitor::visit(UseNodeAST& node) {}

void AnalysisVisitor::visit(ClassNodeAST& node) {}

void AnalysisVisitor::visit(MatchNodeAST& node) {}

void AnalysisVisitor::visit(TestNodeAST& node) {}

void AnalysisVisitor::visit(AssertNodeAST& node) {}

void AnalysisVisitor::visit(RangeOperationNodeAST& node) {}
