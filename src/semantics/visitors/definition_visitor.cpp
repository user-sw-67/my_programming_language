#include "../../include/semantics/visitors/definition_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/parser/ast.hpp"


DefinitionVisitor::DefinitionVisitor(SymbolTable& table, ErrorManager& error_manager) : 
    BaseVisitorSemantics(table, error_manager) {}

void DefinitionVisitor::visit(MakeNodeAST& node) {}

void DefinitionVisitor::visit(LiteralNodeAST& node) {}

void DefinitionVisitor::visit(IdentifierNodeAST& node) {}

void DefinitionVisitor::visit(UnaryOperationNodeAST& node) {}

void DefinitionVisitor::visit(BinaryOperationNodeAST& node) {}

void DefinitionVisitor::visit(BlockNodeAST& node) {}

void DefinitionVisitor::visit(IfElseNodeAST& node) {}

void DefinitionVisitor::visit(TernaryOperationNodeAST& node) {}

void DefinitionVisitor::visit(ExpressionStatementNodeAST& node) {}

void DefinitionVisitor::visit(FunctionNodeAST& node) {
    try{
        table.define_function(node.name, node.get_cout_parameters(), 
            node.is_variadic_parameters(), &node);
    } catch(const RuntimeError& e) {
        error_manager.add(e.what(), node.location, Severity::ERROR);
    }
}

void DefinitionVisitor::visit(ReturnNodeAST& node) {}

void DefinitionVisitor::visit(CallOperationNodeAST& node) {}

void DefinitionVisitor::visit(WhileNodeAST& node) {}

void DefinitionVisitor::visit(ForNodeAST& node) {}

void DefinitionVisitor::visit(BreakNodeAST& node) {}

void DefinitionVisitor::visit(ContinueNodeAST& node) {}

void DefinitionVisitor::visit(ThrowNodeAST& node) {}

void DefinitionVisitor::visit(TryNodeAST& node) {}

void DefinitionVisitor::visit(UseNodeAST& node) {}

void DefinitionVisitor::visit(ClassNodeAST& node) {
    try{
        auto class_scope = std::make_shared<Scope>(
            table.get_current_scope());
        table.define_class(node.name, class_scope, 
            node.has_base_class(), node.base_class_name);
        if(node.has_base_class()){
            if (node.name == node.base_class_name) {
                error_manager.add("Класс " + node.name + 
                    " не может быть наследником самого себя", node.location, 
                        Severity::ERROR);
            }
            auto* base_info = table.lookup(node.base_class_name);
            if (!base_info || base_info->type != SymbolType::CLASS) {
                error_manager.add("Базовый класс " + 
                    node.base_class_name + " не найден для " +
                        node.name, node.location, Severity::ERROR);
            }
        }
    } catch(const RuntimeError& e) {
        error_manager.add(e.what(), node.location, Severity::ERROR);
    }
}

void DefinitionVisitor::visit(MatchNodeAST& node) {}

void DefinitionVisitor::visit(TestNodeAST& node) {}

void DefinitionVisitor::visit(AssertNodeAST& node) {}

void DefinitionVisitor::visit(RangeOperationNodeAST& node) {}
