#include "../../include/semantics/visitors/analysis_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"

#include <vector>
#include <utility>


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
                    "типа данных", node.location, Severity::ERROR,
                        error_code::SEM_2101);
            }
        }

        if(init && node.initializers[i]){
            std::string actual_type =
                infer_type_expression(node.initializers[i].get());
            if(!can_cast(node.type_names[i], actual_type)){
                managers.error.add("Невозможно присвоить значение типа " +
                    actual_type + " переменной с типом " +
                        node.type_names[i], node.location, Severity::ERROR,
                            error_code::SEM_2102);
            }
        }

        if(table.get_current_function() != nullptr){
            try{
                SymbolInfo* sym = table.define_variable(node.names[i],
                    node.type_names[i], node.is_const, init);
                node.slot_indices.push_back(sym->slot_index);
            } catch(const RuntimeError& e) {
                managers.error.add(e.what(), node.location, Severity::ERROR,
                    error_code::SEM_2501);
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
            node.name, node.location, Severity::ERROR,
                error_code::SEM_2201);
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
                        node.location, Severity::ERROR,
                            error_code::SEM_2202);
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
                    "для присваивания", node.location, Severity::ERROR,
                        error_code::SEM_2301);
            } else if (left_id && left_id->resolved_symbol &&
                left_id->resolved_symbol->is_const) {
                    managers.error.add("Нельзя переприсвоить значение "
                        "константе " + left_id->name, node.location,
                            Severity::ERROR, error_code::SEM_2302);
            } else if (left_bin && (left_bin->op == TokenType::OP_DOT ||
                left_bin->op == TokenType::OP_SAFE_NAV)) {
                    SymbolInfo* member = resolve_member_symbol(left_bin);
                    if (member && member->is_const) {
                        managers.error.add("Нельзя переприсвоить значение "
                            "константному полю " + member->name,
                                node.location, Severity::ERROR,
                                    error_code::SEM_2303);
                    }
            }
    }

    if (node.op != TokenType::OP_DOT && node.op != TokenType::OP_SAFE_NAV) {
        if(node.right) node.right->accept(*this);
    }
}

void AnalysisVisitor::visit(BlockNodeAST& node) {
    table.enter_scope();

    for(size_t i = 0; i < node.statements.size(); ++i){
        auto& stmt = node.statements[i];
        if(stmt) stmt->accept(*this);

        if(stmt && is_terminating_statement(stmt.get()) &&
            i + 1 < node.statements.size()){
                managers.error.add("Код после return/break/continue/throw "
                    "недостижим, поэтому вырезан из дерева",
                        node.statements[i + 1]->location, Severity::WARNING,
                            error_code::SEM_2401);
                node.statements.resize(i + 1);
                break;
        }
    }

    table.exit_scope();
}

void AnalysisVisitor::visit(IfElseNodeAST& node) {
    if(node.condition) node.condition->accept(*this);
    check_condition_type(node.condition.get());
    if(node.then_branch) node.then_branch->accept(*this);
    if(node.else_branch) node.else_branch->accept(*this);
}

void AnalysisVisitor::visit(TernaryOperationNodeAST& node) {
    if(node.condition) node.condition->accept(*this);
    check_condition_type(node.condition.get());
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
                    "типа данных", node.location, Severity::ERROR,
                        error_code::SEM_2103);
            }
        }

        SymbolInfo* sym = nullptr;
        try{
            sym = table.define_variable(
                arg.name, arg.type, false, true);
        } catch(const RuntimeError& e) {
            managers.error.add(e.what(), node.location, Severity::ERROR,
                error_code::SEM_2502);
            continue;
        }

        arg.slot_index = sym->slot_index;
        if(arg.default_value){
            arg.default_value->accept(*this);
            std::string default_type =
                infer_type_expression(arg.default_value.get());
            if(!can_cast(arg.type, default_type)){
                managers.error.add("Значение по умолчанию имеет тип " +
                    default_type + ", ожидался тип " + arg.type,
                        arg.location, Severity::ERROR, error_code::SEM_2104);
            }
        }
    }

    if(node.when_condition){
        node.when_condition->accept(*this);
        check_condition_type(node.when_condition.get());
    }

    if(node.body) node.body->accept(*this);

    if(node.body && node.return_type != "auto" && node.return_type != "Null"
        && !always_returns(node.body.get())){
            managers.error.add("Не все пути функции " + node.name +
                " завершаются оператором return: возможен выход без "
                "значения типа " + node.return_type, node.location,
                    Severity::ERROR, error_code::SEM_2404);
    }

    node.locals_count = table.get_current_slots_count();
    table.set_current_function(nullptr);
    table.exit_scope();
}

void AnalysisVisitor::visit(ReturnNodeAST& node) {
    SymbolInfo* func = table.get_current_function();
    if(func == nullptr){
        managers.error.add("Конструкция return невозможна вне функции",
            node.location, Severity::ERROR, error_code::SEM_2402);
    }

    if(node.value) node.value->accept(*this);

    if(func != nullptr){
        bool is_ctor_or_dtor = func->in_class &&
            (func->name == "new" || func->name == "delete");

        if(is_ctor_or_dtor){
            if(node.value){
                managers.error.add("Конструктор/деструктор " + func->name +
                    "() не должен возвращать значение", node.location,
                        Severity::ERROR, error_code::SEM_2403);
            }
        } else {
            std::string actual_type = node.value ?
                infer_type_expression(node.value.get()) : "Null";
            if(!can_cast(func->type_name, actual_type)){
                managers.error.add("Возвращаемое значение имеет тип " +
                    actual_type + ", ожидался тип " + func->type_name,
                        node.location, Severity::ERROR, error_code::SEM_2105);
            }
        }
    }
}

void AnalysisVisitor::visit(CallOperationNodeAST& node) {
    if(node.callee) node.callee->accept(*this);

    for (auto& arg : node.args) {
        if(arg) arg->accept(*this);
    }

    auto* id_ptr = dynamic_cast<IdentifierNodeAST*>(node.callee.get());
    auto* bin_ptr = dynamic_cast<BinaryOperationNodeAST*>(node.callee.get());

    if(id_ptr){
        auto* symbol = table.lookup(id_ptr->name);
        if(symbol){
            if(symbol->type == SymbolType::FUNCTION){
                check_call(symbol, node, "Количество передаваемых аргументов (" +
                    std::to_string(node.args.size()) + ") в функцию " +
                    symbol->name + " не соответствует ее сигнатуре");
            } else if (symbol->type == SymbolType::CLASS){
                auto construct = symbol->class_scope->symbols.find("new");
                if(construct != symbol->class_scope->symbols.end()){
                    check_call(construct->second.get(), node, "Количество "
                        "передаваемых аргументов (" + std::to_string(
                        node.args.size()) + ") в конструктор класса " +
                        symbol->name + " не соответствует его сигнатуре");
                }
            } else {
                managers.error.add("Идентификатор " + symbol->name +
                    " не может быть вызван", node.location, Severity::ERROR,
                        error_code::SEM_2203);
            }
        }
    } else if (bin_ptr){
        if(bin_ptr->op == TokenType::OP_DOT ||
            bin_ptr->op == TokenType::OP_SAFE_NAV){
                SymbolInfo* method = resolve_member_symbol(bin_ptr);
                if(method){
                    if(method->type == SymbolType::FUNCTION){
                        check_call(method, node, "Количество передаваемых "
                            "аргументов (" + std::to_string(node.args.size()) +
                            ") в метод " + method->name +
                            " не соответствует его сигнатуре");
                    } else {
                        managers.error.add("Идентификатор " + method->name +
                            " не может быть вызван", node.location,
                                Severity::ERROR, error_code::SEM_2204);
                    }
                }
        } else {

        }
    } else {

    }
}

void AnalysisVisitor::check_call(SymbolInfo* symbol,
    CallOperationNodeAST& node, const std::string& err){
        size_t arg_count = node.args.size();
        uint8_t min_args = symbol->count_args - symbol->count_elem_default;
        if(symbol->is_ellipsis_args && min_args > 0) --min_args;

        bool too_many = !symbol->is_ellipsis_args &&
            arg_count > static_cast<size_t>(symbol->count_args);
        bool too_few = arg_count < static_cast<size_t>(min_args);

        if(too_many || too_few){
            managers.error.add(err, node.location, Severity::ERROR,
                error_code::SEM_2504);
            return;
        }

        if(!symbol->body_ast) return;

        auto& params = symbol->body_ast->parameters;
        for(size_t i = 0; i < node.args.size() && i < params.size(); ++i){
            if(!node.args[i] || params[i].type == "auto") continue;
            std::string actual_type = infer_type_expression(node.args[i].get());
            if(!can_cast(params[i].type, actual_type)){
                managers.error.add("Аргумент " + std::to_string(i + 1) +
                    " имеет тип " + actual_type + ", ожидался тип " +
                        params[i].type, node.args[i]->location,
                            Severity::ERROR, error_code::SEM_2106);
            }
        }
}

void AnalysisVisitor::visit(WhileNodeAST& node) {
    if(node.condition) node.condition->accept(*this);
    check_condition_type(node.condition.get());

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
        managers.error.add(e.what(), node.location, Severity::ERROR,
            error_code::SEM_2503);
        table.exit_scope();
        in_cycle = old_in_cycle;
        return;
    }
    node.slot_index = sym->slot_index;
    if(node.iterable) node.iterable->accept(*this);

    if(node.iterable){
        std::string iter_type = infer_type_expression(node.iterable.get());
        if(iter_type != "auto"){
            auto* class_sym = table.lookup(iter_type);
            bool iterable = class_sym && class_sym->type == SymbolType::CLASS
                && class_sym->is_iter_obj;
            if(!iterable){
                managers.error.add("Тип " + iter_type + " не является "
                    "итерируемым: класс должен иметь метод iter()",
                        node.location, Severity::ERROR, error_code::SEM_2108);
            }
        }
    }

    if(node.body) node.body->accept(*this);
    table.exit_scope();
    in_cycle = old_in_cycle;
}

void AnalysisVisitor::visit(BreakNodeAST& node) {
    if(!in_cycle){
        managers.error.add("Конструкция break невозможна вне цикла",
            node.location, Severity::ERROR, error_code::SEM_2405);
    }
}

void AnalysisVisitor::visit(ContinueNodeAST& node) {
    if(!in_cycle){
        managers.error.add("Конструкция continue невозможна вне цикла",
            node.location, Severity::ERROR, error_code::SEM_2406);
    }
}

void AnalysisVisitor::visit(ThrowNodeAST& node) {
    if(table.get_current_function() == nullptr){
        managers.error.add("Конструкция throw невозможна вне функции",
            node.location, Severity::ERROR, error_code::SEM_2407);
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
    std::string value_type = infer_type_expression(node.value.get());

    table.enter_scope();

    std::vector<std::pair<TokenType, std::string>> seen_literals;
    for(auto& c : node.cases){
        if (c.value) {
            c.value->accept(*this);

            std::string case_type = infer_type_expression(c.value.get());
            if (value_type != "auto" && case_type != "auto" &&
                !can_cast(value_type, case_type) &&
                !can_cast(case_type, value_type)) {
                    managers.error.add("Тип значения case (" + case_type +
                        ") несовместим с типом сопоставляемого выражения (" +
                        value_type + ")", c.location, Severity::ERROR,
                            error_code::SEM_2701);
            }

            if (auto* lit = dynamic_cast<LiteralNodeAST*>(c.value.get())) {
                bool duplicate = false;
                for (auto& seen : seen_literals) {
                    if (seen.first == lit->literal_type &&
                        seen.second == lit->value) {
                            duplicate = true;
                            break;
                    }
                }
                if (duplicate) {
                    managers.error.add("Повторяющееся значение в case: " +
                        lit->value, c.location, Severity::ERROR,
                            error_code::SEM_2702);
                } else {
                    seen_literals.emplace_back(lit->literal_type, lit->value);
                }
            }
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
            node.location, Severity::ERROR, error_code::SEM_2408);
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

        if (expected == "Null") return true;

        if (actual == "Null") {
            if (expected == "Int" || expected == "Double" ||
                expected == "Bool" || expected == "Str") return false;
            auto* expected_sym = table.lookup(expected);
            return expected_sym && expected_sym->type == SymbolType::CLASS;
        }


        return false;
}

bool AnalysisVisitor::is_terminating_statement(StatementNodeAST* stmt) {
    return dynamic_cast<ReturnNodeAST*>(stmt) ||
        dynamic_cast<BreakNodeAST*>(stmt) ||
        dynamic_cast<ContinueNodeAST*>(stmt) ||
        dynamic_cast<ThrowNodeAST*>(stmt);
}

bool AnalysisVisitor::always_returns(StatementNodeAST* stmt) {
    if (!stmt) return false;

    if (dynamic_cast<ReturnNodeAST*>(stmt) || dynamic_cast<ThrowNodeAST*>(stmt)) {
        return true;
    }

    if (auto* block = dynamic_cast<BlockNodeAST*>(stmt)) {
        for (auto& s : block->statements) {
            if (always_returns(s.get())) return true;
        }
        return false;
    }

    if (auto* if_else = dynamic_cast<IfElseNodeAST*>(stmt)) {
        return if_else->else_branch &&
            always_returns(if_else->then_branch.get()) &&
            always_returns(if_else->else_branch.get());
    }

    if (auto* try_stmt = dynamic_cast<TryNodeAST*>(stmt)) {
        if (always_returns(try_stmt->finally_block.get())) return true;
        bool try_ok = always_returns(try_stmt->try_block.get());
        bool catch_ok = !try_stmt->catch_block ||
            always_returns(try_stmt->catch_block.get());
        return try_ok && catch_ok;
    }

    if (auto* match_stmt = dynamic_cast<MatchNodeAST*>(stmt)) {
        bool has_default = false;
        for (auto& c : match_stmt->cases) {
            if (!c.value) has_default = true;
            if (!always_returns(c.body.get())) return false;
        }
        return has_default;
    }

    return false;
}

void AnalysisVisitor::check_condition_type(ExpressionNodeAST* node) {
    if (!node) return;

    std::string cond_type = infer_type_expression(node);
    if (!can_cast("Bool", cond_type)) {
        managers.error.add("Условие должно иметь тип Bool (или приводимый к Bool), а получено " +
            cond_type, node->location, Severity::ERROR, error_code::SEM_2107);
    }
}

SymbolInfo* AnalysisVisitor::find_class_member(SymbolInfo* class_sym,
    const std::string& name, SymbolInfo** owner_out){
        while (class_sym && class_sym->class_scope) {
            auto it = class_sym->class_scope->symbols.find(name);
            if (it != class_sym->class_scope->symbols.end()) {
                if (owner_out) *owner_out = class_sym;
                return it->second.get();
            }
            if (!class_sym->is_has_parent) break;
            class_sym = table.lookup(class_sym->parent_name);
        }
        return nullptr;
}

bool AnalysisVisitor::check_member_access(SymbolInfo* member,
    SymbolInfo* owner, const SourceLocation& loc) {
        if (!member || !owner || member->access_modifier == "public") {
            return true;
        }

        SymbolInfo* current_class = table.get_current_class();

        if (member->access_modifier == "private") {
            if (current_class == owner) return true;
            managers.error.add("Доступ к private-члену " + member->name +
                " класса " + owner->name + " запрещён снаружи класса",
                    loc, Severity::ERROR, error_code::SEM_2205);
            return false;
        }

        if (member->access_modifier == "protected") {
            SymbolInfo* ancestor = current_class;
            while (ancestor) {
                if (ancestor == owner) return true;
                if (!ancestor->is_has_parent) break;
                ancestor = table.lookup(ancestor->parent_name);
            }
            managers.error.add("Доступ к protected-члену " + member->name +
                " класса " + owner->name + " запрещён снаружи класса и его "
                "наследников", loc, Severity::ERROR, error_code::SEM_2206);
            return false;
        }

        return true;
}

SymbolInfo* AnalysisVisitor::resolve_member_symbol(
    BinaryOperationNodeAST* node) {
        std::string left_type = infer_type_expression(node->left.get());
        if (left_type == "auto") return nullptr;

        auto* class_sym = table.lookup(left_type);
        if (!class_sym || class_sym->type != SymbolType::CLASS) return nullptr;

        auto* right_id = dynamic_cast<IdentifierNodeAST*>(node->right.get());
        if (!right_id) return nullptr;

        SymbolInfo* owner = nullptr;
        SymbolInfo* member = find_class_member(class_sym, right_id->name, &owner);
        if (!member) return nullptr;

        if (!check_member_access(member, owner, node->location)) return nullptr;

        return member;
}

std::string AnalysisVisitor::infer_member_type(BinaryOperationNodeAST* node) {
    SymbolInfo* member = resolve_member_symbol(node);
    if (!member) return "auto";

    if (member->type == SymbolType::FUNCTION) return "Function";
    return member->type_name;
}

std::string AnalysisVisitor::infer_binary_type(BinaryOperationNodeAST* node) {
    if (node->op == TokenType::OP_DOT || node->op == TokenType::OP_SAFE_NAV) {
        return infer_member_type(node);
    }

    if (node->op >= TokenType::OP_ASSIGN &&
        node->op <= TokenType::OP_INT_DIV_ASSIGN) {
            return infer_type_expression(node->left.get());
    }

    if ((node->op >= TokenType::OP_EQ && node->op <= TokenType::OP_GE) ||
        node->op == TokenType::OP_AND || node->op == TokenType::OP_OR) {
            return "Bool";
    }

    std::string left_type = infer_type_expression(node->left.get());
    std::string right_type = infer_type_expression(node->right.get());

    if (left_type == "auto" || right_type == "auto") return "auto";

    if (node->op == TokenType::OP_PLUS &&
        (left_type == "Str" || right_type == "Str")) {
            return left_type == right_type ? "Str" : "auto";
    }

    if (left_type == "Double" || right_type == "Double") return "Double";
    if (left_type == "Int" || right_type == "Int") return "Int";
    if (left_type == "Bool" && right_type == "Bool") return "Int";

    return "auto";
}

std::string AnalysisVisitor::infer_call_type(CallOperationNodeAST* node) {
    auto* id_ptr = dynamic_cast<IdentifierNodeAST*>(node->callee.get());
    if (id_ptr) {
        auto* sym = table.lookup(id_ptr->name);
        if (!sym) return "auto";
        if (sym->type == SymbolType::CLASS) return sym->name;
        if (sym->type == SymbolType::FUNCTION) return sym->type_name;
        return "auto";
    }

    auto* bin_ptr = dynamic_cast<BinaryOperationNodeAST*>(node->callee.get());
    if (bin_ptr && (bin_ptr->op == TokenType::OP_DOT ||
        bin_ptr->op == TokenType::OP_SAFE_NAV)) {
            SymbolInfo* member = resolve_member_symbol(bin_ptr);
            if (member && member->type == SymbolType::FUNCTION) {
                return member->type_name;
            }
            return "auto";
    }

    return "auto";
}

std::string AnalysisVisitor::infer_type_expression(ExpressionNodeAST* node) {
    if (!node) return "auto";

    auto cached = type_cache.find(node);
    if (cached != type_cache.end()) return cached->second;

    std::string result = "auto";

    if (auto* lit = dynamic_cast<LiteralNodeAST*>(node)) {
        switch (lit->literal_type) {
            case TokenType::LIT_INT: result = "Int"; break;
            case TokenType::LIT_DOUBLE: result = "Double"; break;
            case TokenType::LIT_STR: result = "Str"; break;
            case TokenType::LIT_BOOL: result = "Bool"; break;
            case TokenType::LIT_NULL: result = "Null"; break;
            default: result = "auto"; break;
        }
    } else if (auto* id = dynamic_cast<IdentifierNodeAST*>(node)) {
        auto* sym = table.lookup(id->name);
        if (sym) {
            if (sym->type == SymbolType::FUNCTION) result = "Function";
            else if (sym->type == SymbolType::CLASS) result = "Type";
            else if (sym->type == SymbolType::VARIABLE) result = sym->type_name;
            else result = "auto";
        }
    } else if (auto* un = dynamic_cast<UnaryOperationNodeAST*>(node)) {
        result = (un->op == TokenType::OP_NOT) ?
            "Bool" : infer_type_expression(un->operand.get());
    } else if (auto* bin = dynamic_cast<BinaryOperationNodeAST*>(node)) {
        result = infer_binary_type(bin);
    } else if (auto* tern = dynamic_cast<TernaryOperationNodeAST*>(node)) {
        std::string true_type = infer_type_expression(tern->true_branch.get());
        std::string false_type = infer_type_expression(tern->false_branch.get());
        result = (true_type == false_type) ? true_type : "auto";
    } else if (auto* call = dynamic_cast<CallOperationNodeAST*>(node)) {
        result = infer_call_type(call);
    } else if (dynamic_cast<RangeOperationNodeAST*>(node)) {
        result = "Range";
    }

    type_cache[node] = result;
    return result;
}