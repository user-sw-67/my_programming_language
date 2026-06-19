#include "../../include/semantics/visitors/analysis_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"


AnalysisVisitor::AnalysisVisitor(SymbolTable& table, Managers& managers) : 
    BaseVisitorSemantics(table, managers) {}

void AnalysisVisitor::visit(MakeNodeAST& node) {
    bool init = node.is_init();
    
    for (size_t i = 0; i < node.names.size(); ++i){
        auto* sym_std = table.lookup(node.names[i]);
        if(sym_std && sym_std->is_std) continue;

        if(init){
            if(node.initializers[i]) node.initializers[i]->accept(*this);
        }

        if(node.type_names[i] != "auto"){
            auto* type = table.lookup(node.type_names[i]);
            if(!type || type->type != SymbolType::CLASS){
                managers.error.add("Использование необъявленного "
                    "типа данных", node.location, Severity::ERROR);
            }
        }

        // if(can_cast(node.type_names[i], node.initializers[i])){

        // }

        if(table.get_current_function() != nullptr){
            try{
                SymbolInfo* sym = table.define_variable(node.names[i], 
                    node.type_names[i], node.is_const, init);
                node.slot_indices.push_back(sym->slot_index);
            } catch(const RuntimeError& e) {
                managers.error.add(e.what(), node.location, Severity::ERROR);
                continue;
            }
        }
    }
}

void AnalysisVisitor::visit(LiteralNodeAST& node) {}

void AnalysisVisitor::visit(IdentifierNodeAST& node) {
    SymbolInfo* sym = table.lookup(node.name);

    if(!sym){
        managers.error.add("Использование необъявленного идентификатора " + 
            node.name, node.location, Severity::ERROR);
        return;
    }

    node.resolved_symbol = sym;
    node.slot_index = sym->slot_index;

    if(sym->is_built_in || sym->type == SymbolType::CLASS 
        || sym->type == SymbolType::TEST){
            node.kind = IdentifierKind::CONSTANT;
    } else if (sym->in_class) {
        if(sym->is_static){
            node.kind = IdentifierKind::GLOBAL;
        } else {
            if (current_method_is_static) {
                managers.error.add("Нельзя использовать нестатическое поле "
                    "или метод " + node.name + " в статическом контексте", 
                        node.location, Severity::ERROR);
                return;
            }
            node.kind = IdentifierKind::FIELD;
        }
    } else {
        if(table.get_current_function() != nullptr){
            node.kind = IdentifierKind::LOCAL;
        } else {
            node.kind = IdentifierKind::GLOBAL;
        }
    }
}

void AnalysisVisitor::visit(UnaryOperationNodeAST& node) {
    if(node.operand) node.operand->accept(*this);
}

void AnalysisVisitor::visit(BinaryOperationNodeAST& node) {
    if(node.left) node.left->accept(*this);

    if (node.op >= TokenType::OP_ASSIGN && 
        node.op <= TokenType::OP_INT_DIV_ASSIGN){
            auto* left_id = dynamic_cast<IdentifierNodeAST*>(node.left.get());
            auto* left_bin = dynamic_cast<BinaryOperationNodeAST*>(
                node.left.get());

            bool valid_value = (left_id != nullptr || 
                (left_bin != nullptr && (left_bin->op == TokenType::OP_DOT || 
                    left_bin->op == TokenType::OP_SAFE_NAV)));
            if(!valid_value){
                managers.error.add("Левая часть выражения не может быть целью "
                    "для присваивания", node.location, Severity::ERROR);
            }
    }

    if (node.op != TokenType::OP_DOT && node.op != TokenType::OP_SAFE_NAV) {
        if(node.right) node.right->accept(*this);
    }
}

void AnalysisVisitor::visit(BlockNodeAST& node) {
    table.enter_scope();

    for(auto& stmt : node.statements){
        if(stmt) stmt->accept(*this);
    }

    table.exit_scope();
}

void AnalysisVisitor::visit(IfElseNodeAST& node) {
    if(node.condition) node.condition->accept(*this);
    if(node.then_branch) node.then_branch->accept(*this);
    if(node.else_branch) node.else_branch->accept(*this);
}

void AnalysisVisitor::visit(TernaryOperationNodeAST& node) {
    if(node.condition) node.condition->accept(*this);
    if(node.true_branch) node.true_branch->accept(*this);
    if(node.false_branch) node.false_branch->accept(*this);
}

void AnalysisVisitor::visit(ExpressionStatementNodeAST& node) {
    if(node.expression) node.expression->accept(*this);
}

void AnalysisVisitor::visit(FunctionNodeAST& node) {
    SymbolInfo* func_sym = table.lookup(node.name);

    if(!func_sym || func_sym->is_std) return;

    table.enter_function_scope();
    table.set_current_function(func_sym);

    for (auto& arg : node.parameters){

        if(arg.type != "auto"){
            auto* type = table.lookup(arg.type);
            if(!type || type->type != SymbolType::CLASS){
                managers.error.add("Использование необъявленного "
                    "типа данных", node.location, Severity::ERROR);
            }
        }

        SymbolInfo* sym = nullptr;
        try{
            sym = table.define_variable(
                arg.name, arg.type, false, true);
        } catch(const RuntimeError& e) {
            managers.error.add(e.what(), node.location, Severity::ERROR);
            continue;
        }

        arg.slot_index = sym->slot_index;
        if(arg.default_value) arg.default_value->accept(*this);
    }

    if(node.when_condition) node.when_condition->accept(*this);

    if(node.body) node.body->accept(*this);

    node.locals_count = table.get_current_slots_count();
    table.set_current_function(nullptr);
    table.exit_scope();
}

void AnalysisVisitor::visit(ReturnNodeAST& node) {
    if(table.get_current_function() == nullptr){
        managers.error.add("Конструкция return невозможна вне функции", 
            node.location, Severity::ERROR);
    }
    if(node.value) node.value->accept(*this);
}

void AnalysisVisitor::visit(CallOperationNodeAST& node) {
    if(node.callee) node.callee->accept(*this);

    for (auto& arg : node.args) {
        if(arg) arg->accept(*this);
    }

    auto* id_ptr = dynamic_cast<IdentifierNodeAST*>(node.callee.get());
    auto* bin_ptr = dynamic_cast<BinaryOperationNodeAST*>(node.callee.get());

    auto valid_func = [&node, this](SymbolInfo* symbol, const std::string& err){
        int size = node.args.size();
        int difference = symbol->count_args - 
            symbol->count_elem_default;
        if(symbol->is_ellipsis_args) --difference;
        if((!symbol->is_ellipsis_args && 
            (size < difference || size > symbol->count_args)) || 
                (symbol->is_ellipsis_args && size < difference)){
                    managers.error.add(err, node.location, Severity::ERROR);
        }
    };

    if(id_ptr){
        auto* symbol = table.lookup(id_ptr->name);
        if(symbol){
            if(symbol->type == SymbolType::FUNCTION){
                valid_func(symbol, "Количество передаваемых аргументов (" + 
                    std::to_string(node.args.size()) + ") в функцию " + 
                    symbol->name + " не соответствует ее сигнатуре");
            } else if (symbol->type == SymbolType::CLASS){
                auto construct = symbol->class_scope->symbols.find("new");
                if(construct != symbol->class_scope->symbols.end()){
                    valid_func(construct->second.get(),  "Количество "
                        "передаваемых аргументов (" + std::to_string(
                        node.args.size()) + ") в конструктор класса " + 
                        symbol->name + " не соответствует его сигнатуре");
                }
            } else {
                managers.error.add("Идентификатор " + symbol->name + 
                    " не может быть вызван", node.location, Severity::ERROR);
            }
        }
    } else if (bin_ptr){
        if(bin_ptr->op == TokenType::OP_DOT || 
            bin_ptr->op == TokenType::OP_SAFE_NAV){

        } else {
            
        }
    } else {

    }
}

void AnalysisVisitor::visit(WhileNodeAST& node) {
    if(node.condition) node.condition->accept(*this);
    
    bool old_in_cycle = in_cycle;
    in_cycle = true;
    if(node.body) node.body->accept(*this);
    in_cycle = old_in_cycle;
}

void AnalysisVisitor::visit(ForNodeAST& node) {
    bool old_in_cycle = in_cycle;
    in_cycle = true;
    table.enter_scope();
    SymbolInfo* sym = nullptr;
    try{
        sym = table.define_variable(node.name_var, "auto", false, true);
    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR);
        table.exit_scope();
        in_cycle = old_in_cycle;
        return;
    }
    node.slot_index = sym->slot_index;
    if(node.iterable) node.iterable->accept(*this);
    if(node.body) node.body->accept(*this); 
    table.exit_scope();
    in_cycle = old_in_cycle;
}

void AnalysisVisitor::visit(BreakNodeAST& node) {
    if(!in_cycle){
        managers.error.add("Конструкция break невозможна вне цикла", 
            node.location, Severity::ERROR);
    }
}

void AnalysisVisitor::visit(ContinueNodeAST& node) {
    if(!in_cycle){
        managers.error.add("Конструкция continue невозможна вне цикла", 
            node.location, Severity::ERROR);
    }
}

void AnalysisVisitor::visit(ThrowNodeAST& node) {
    if(table.get_current_function() == nullptr){
        managers.error.add("Конструкция throw невозможна вне функции", 
            node.location, Severity::ERROR);
    }
    if(node.value) node.value->accept(*this);
}

void AnalysisVisitor::visit(TryNodeAST& node) {
    if(node.try_block) node.try_block->accept(*this);
    if(node.catch_expr) node.catch_expr->accept(*this);
    if(node.catch_block) node.catch_block->accept(*this);
    if(node.finally_block) node.finally_block->accept(*this);
}

void AnalysisVisitor::visit(UseNodeAST& node) {}

void AnalysisVisitor::visit(ClassNodeAST& node) {
    SymbolInfo* class_symbol = table.lookup(node.name);

    if(!class_symbol || class_symbol->is_std) return;

    table.enter_existing_scope(class_symbol->class_scope);
    table.set_current_class(class_symbol);

    for(auto& m : node.members){
        if(!m.member_node) continue;
        current_method_is_static = m.is_static;
        m.member_node->accept(*this);
    }

    table.set_current_class(nullptr);
    table.exit_existing_scope();
}

void AnalysisVisitor::visit(MatchNodeAST& node) {
    if(node.value) node.value->accept(*this);
    table.enter_scope();

    bool is_default = false;
    for(auto& c : node.cases){
        if (!c.value) {
            if (is_default) {
                managers.error.add("Больше одной инструкции default невозможно",
                    node.location, Severity::ERROR);
            }
            is_default = true;
        } else {
            c.value->accept(*this);
        }
        if(c.body) c.body->accept(*this);
    }

    table.exit_scope();
}

void AnalysisVisitor::visit(TestNodeAST& node) {
    SymbolInfo* test_symbol = table.lookup(node.name);

    if(!test_symbol || test_symbol->is_std) return;

    table.enter_existing_scope(test_symbol->test_scope);
    in_test = true;
    if(node.body) node.body->accept(*this);
    in_test = false;
    table.exit_existing_scope();
}

void AnalysisVisitor::visit(AssertNodeAST& node) {
    if(!in_test){
        managers.error.add("Конструкция assert невозможна вне тестов", 
            node.location, Severity::ERROR);
    }
    if(node.value) node.value->accept(*this);
}

void AnalysisVisitor::visit(RangeOperationNodeAST& node) {
    if(node.start) node.start->accept(*this);
    if(node.end) node.end->accept(*this);
    if(node.step) node.step->accept(*this);
}

bool AnalysisVisitor::can_cast(
    const std::string& expected, const std::string& actual){
        if(expected == actual) return true;
        if (expected == "auto" || actual == "auto") return true;

        if (expected == "Double" && actual == "Int") return true;
        if (expected == "Int" && actual == "Double") return true;

        if (expected == "Bool" && actual == "Double") return true;
        if (expected == "Double" && actual == "Bool") return true;

        if (expected == "Bool" && actual == "Int") return true;
        if (expected == "Int" && actual == "Bool") return true;

        if (expected == "Str" && actual == "Str") return true;

        return false;
}