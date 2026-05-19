#ifndef DEFINITION_VISITOR_HPP
#define DEFINITION_VISITOR_HPP

#include "base.hpp"


class DefinitionVisitor : public BaseVisitorSemantics{
public:
    DefinitionVisitor(SymbolTable& table, ErrorManager& error_manager) : 
        BaseVisitorSemantics(table, error_manager) {}

    void visit(MakeNodeAST& node) override {}
    void visit(LiteralNodeAST& node) override {}
    void visit(IdentifierNodeAST& node) override {}
    void visit(UnaryOperationNodeAST& node) override {}
    void visit(BinaryOperationNodeAST& node) override {}
    void visit(BlockNodeAST& node) override {}
    void visit(IfElseNodeAST& node) override {}
    void visit(TernaryOperationNodeAST& node) override {}
    void visit(ExpressionStatementNodeAST& node) override {}

    void visit(FunctionNodeAST& node) override {
        try{
            table.define_function(node.name, node.get_cout_parameters(), 
                node.is_variadic_parameters(), &node);
        } catch(const RuntimeError& e) {
            error_manager.add(e.what(), node.location, Severity::ERROR);
        }
    }

    void visit(ReturnNodeAST& node) override {}
    void visit(CallOperationNodeAST& node) override {}
    void visit(WhileNodeAST& node) override {}
    void visit(ForNodeAST& node) override {}
    void visit(BreakNodeAST& node) override {}
    void visit(ContinueNodeAST& node) override {}
    void visit(ThrowNodeAST& node) override {}
    void visit(TryNodeAST& node) override {}
    void visit(UseNodeAST& node) override {}

    void visit(ClassNodeAST& node) override {
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

    void visit(MatchNodeAST& node) override {}
    void visit(TestNodeAST& node) override {}
    void visit(AssertNodeAST& node) override {}
    void visit(RangeOperationNodeAST& node) override {}
};

#endif