#include "../../include/semantics/visitors/optimization_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/semantics/value.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"

#include <cmath>


OptimizationVisitor::OptimizationVisitor(Managers& managers) : 
    managers(managers) {}

void OptimizationVisitor::visit(
    std::unique_ptr<ProgramNode>& node) {
    for (auto& stmt : node->statements) {
        auto opt_stmt = dispatch(std::move(stmt));
        if(opt_stmt){
            stmt = std::unique_ptr<StatementNodeAST>(
                static_cast<StatementNodeAST*>(opt_stmt.release()));
        }
    }
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<MakeNodeAST> node) {
        if(node->is_init()){
            for(auto& init : node->initializers){
                auto init_new = dispatch(std::move(init));
                init = std::unique_ptr<ExpressionNodeAST>(
                    static_cast<ExpressionNodeAST*>(init_new.release()));
            }
        }
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<LiteralNodeAST> node) {
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<IdentifierNodeAST> node) {
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<UnaryOperationNodeAST> node) {
        auto oper = dispatch(std::move(node->operand));
        node->operand = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(oper.release()));

        auto lit = dynamic_cast<LiteralNodeAST*>(node->operand.get());
        if (lit && node->op == TokenType::OP_NOT) {
            lit->value = literal_cast(lit) ? "true" : "false";
            lit->literal_type = TokenType::LIT_BOOL;
            return std::move(node->operand);
        }

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<BinaryOperationNodeAST> node) {
        auto opt_left = dispatch(std::move(node->left));
        node->left = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(opt_left.release()));

        auto opt_right = dispatch(std::move(node->right));
        node->right = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(opt_right.release()));

        auto left_lit = dynamic_cast<LiteralNodeAST*>(node->left.get());
        auto right_lit = dynamic_cast<LiteralNodeAST*>(node->right.get());

        if (left_lit && right_lit) {
            auto v = calculate(left_lit, node->op, right_lit, node->location);
            if(v) return v;
        }

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<BlockNodeAST> node) {
        for (auto& stmt : node->statements) {
            auto opt_stmt = dispatch(std::move(stmt));
            stmt = std::unique_ptr<StatementNodeAST>(
                static_cast<StatementNodeAST*>(opt_stmt.release()));
        }
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<IfElseNodeAST> node) {
        auto cond = dispatch(std::move(node->condition));
        node->condition = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(cond.release()));

        auto* cond_ptr = dynamic_cast<LiteralNodeAST*>(node->condition.get());
        if(cond_ptr){
            if(literal_cast(cond_ptr)){
                managers.error.add("Условие if constant-true, все ветки будут"
                    " удалены и подставлен блок true", node->location, 
                        Severity::NOTE);
                return std::move(node->then_branch);
            } else {
                managers.error.add("Условие if constant-false, все ветки будут"
                    " удалены и подставлен блок false", node->location, 
                        Severity::NOTE);
                auto el_br = dispatch(std::move(node->else_branch));
                node->else_branch= std::unique_ptr<StatementNodeAST>(
                    static_cast<StatementNodeAST*>(el_br.release()));
                return std::move(node->else_branch);
            }
        }

        auto th_br = dispatch(std::move(node->then_branch));
        node->then_branch = std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(th_br.release()));

        auto el_br = dispatch(std::move(node->else_branch));
        node->else_branch= std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(el_br.release()));
        
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<TernaryOperationNodeAST> node) {
        auto cond = dispatch(std::move(node->condition));
        node->condition = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(cond.release()));

        auto tr_br = dispatch(std::move(node->true_branch));
        node->true_branch = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(tr_br.release()));

        auto fl_br = dispatch(std::move(node->false_branch));
        node->false_branch = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(fl_br.release()));

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<ExpressionStatementNodeAST> node) {
        auto expr = dispatch(std::move(node->expression));
        node->expression = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(expr.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<FunctionNodeAST> node) {
        for(auto& p : node->parameters){
            if(p.default_value){
                auto def_v = dispatch(std::move(p.default_value));
                p.default_value = std::unique_ptr<ExpressionNodeAST>(
                    static_cast<ExpressionNodeAST*>(def_v.release()));
            }
        }

        if(node->when_condition){
            auto when = dispatch(std::move(node->when_condition));
            node->when_condition = std::unique_ptr<ExpressionNodeAST>(
                static_cast<ExpressionNodeAST*>(when.release()));

            auto* when_ptr = dynamic_cast<LiteralNodeAST*>(
                node->when_condition.get());
            if(when_ptr){
                if(literal_cast(when_ptr)){
                    managers.error.add("Условие when constant-true, ветка "
                        "when будет удалена", node->location, Severity::NOTE);
                    node->when_condition = nullptr;
                } else {
                    managers.error.add("Условие when constant-false, тело "
                        "функции и ветка when будут удалены", node->location, 
                            Severity::NOTE);
                    node->when_condition = nullptr;
                    node->body = std::make_unique<BlockNodeAST>(
                        node->body->location);
                    return node;
                }
            }
        }

        auto body = dispatch(std::move(node->body));
        node->body = std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(body.release()));

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<ReturnNodeAST> node) {
        auto expr = dispatch(std::move(node->value));
        node->value = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(expr.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<CallOperationNodeAST> node) {
        auto cal = dispatch(std::move(node->callee));
        node->callee = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(cal.release()));

        for(auto& arg : node->args){
            auto val = dispatch(std::move(arg));
            arg = std::unique_ptr<ExpressionNodeAST>(
                static_cast<ExpressionNodeAST*>(val.release()));
        }

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<WhileNodeAST> node) {
        auto cond = dispatch(std::move(node->condition));
        node->condition = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(cond.release()));

        auto* cond_ptr = dynamic_cast<LiteralNodeAST*>(node->condition.get());
        if(cond_ptr && !literal_cast(cond_ptr)){
            managers.error.add("Условие while constant-false тело цикла "
                "будет удалено", node->location, Severity::NOTE);
            node->body = std::make_unique<BlockNodeAST>(node->body->location);
            return node;
        }

        auto bd = dispatch(std::move(node->body));
        node->body = std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(bd.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<ForNodeAST> node) {
        auto it = dispatch(std::move(node->iterable));
        node->iterable = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(it.release()));

        auto bd = dispatch(std::move(node->body));
        node->body = std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(bd.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<BreakNodeAST> node) {
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<ContinueNodeAST> node) {
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<ThrowNodeAST> node) {
        auto expr = dispatch(std::move(node->value));
        node->value = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(expr.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<TryNodeAST> node) {
        auto try_bl = dispatch(std::move(node->try_block));
        node->try_block = std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(try_bl.release()));

        auto expr = dispatch(std::move(node->catch_expr));
        node->catch_expr = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(expr.release()));
        
        auto catch_bl = dispatch(std::move(node->catch_block));
        node->catch_block= std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(catch_bl.release()));

        auto fin_bl = dispatch(std::move(node->finally_block));
        node->finally_block= std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(fin_bl.release()));

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<UseNodeAST> node) {
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<ClassNodeAST> node) {
        for(auto& mem : node->members){
            auto m = dispatch(std::move(mem.member_node));
            mem.member_node = std::unique_ptr<StatementNodeAST>(
                static_cast<StatementNodeAST*>(m.release()));
        }
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<MatchNodeAST> node) {
        auto value = dispatch(std::move(node->value));
        node->value = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(value.release()));

        for(auto& c : node->cases){
            auto val = dispatch(std::move(c.value));
            c.value = std::unique_ptr<ExpressionNodeAST>(
                static_cast<ExpressionNodeAST*>(val.release()));

            auto bd = dispatch(std::move(c.body));
            c.body = std::unique_ptr<StatementNodeAST>(
                static_cast<StatementNodeAST*>(bd.release()));
        }

        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<TestNodeAST> node) {
        auto bd = dispatch(std::move(node->body));
        node->body = std::unique_ptr<StatementNodeAST>(
            static_cast<StatementNodeAST*>(bd.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<AssertNodeAST> node) {
        auto expr = dispatch(std::move(node->value));
        node->value = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(expr.release()));
        return node;
}

std::unique_ptr<NodeAST> OptimizationVisitor::visit(
    std::unique_ptr<RangeOperationNodeAST> node) {
        auto start = dispatch(std::move(node->start));
        node->start = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(start.release()));
        
        auto end = dispatch(std::move(node->end));
        node->end = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(end.release()));

        auto step = dispatch(std::move(node->step));
        node->step = std::unique_ptr<ExpressionNodeAST>(
            static_cast<ExpressionNodeAST*>(step.release()));
        
        return node;
}

std::unique_ptr<LiteralNodeAST> OptimizationVisitor::calculate(
    LiteralNodeAST* left, TokenType op, 
        LiteralNodeAST* right, SourceLocation loc){

    auto make_int = [&](ValueTypeList::INT_V v) { 
        return std::make_unique<LiteralNodeAST>(
            std::to_string(v), TokenType::LIT_INT, loc); 
    };
    auto make_double = [&](ValueTypeList::DOUBLE_V v) { 
        return std::make_unique<LiteralNodeAST>(
            std::to_string(v), TokenType::LIT_DOUBLE, loc); 
    };
    auto make_bool = [&](ValueTypeList::BOOL_V v) { 
        return std::make_unique<LiteralNodeAST>(
            v ? "true" : "false", TokenType::LIT_BOOL, loc); 
    };
    auto make_str = [&](const ValueTypeList::STR_V& v) { 
        return std::make_unique<LiteralNodeAST>(v, TokenType::LIT_STR, loc); 
    };

    bool is_left_num = (left->literal_type == TokenType::LIT_INT || 
        left->literal_type == TokenType::LIT_DOUBLE);
    bool is_right_num = (right->literal_type == TokenType::LIT_INT || 
        right->literal_type == TokenType::LIT_DOUBLE);

    if (is_left_num && is_right_num) {
        bool is_double = (left->literal_type == TokenType::LIT_DOUBLE || 
            right->literal_type == TokenType::LIT_DOUBLE);

        if (is_double) {
            ValueTypeList::DOUBLE_V l = 
                (left->literal_type == TokenType::LIT_DOUBLE) ? 
                    std::stod(left->value) : std::stoll(left->value);
            ValueTypeList::DOUBLE_V r = 
                (right->literal_type == TokenType::LIT_DOUBLE) ? 
                    std::stod(right->value) : std::stoll(right->value);

            switch (op) {
                case TokenType::OP_PLUS: return make_double(l + r);
                case TokenType::OP_MINUS: return make_double(l - r);
                case TokenType::OP_MUL: return make_double(l * r);
                case TokenType::OP_DIV: 
                    return r != 0.0 ? make_double(l / r) : nullptr;
                case TokenType::OP_MOD: 
                    return r != 0.0 ? make_double(std::fmod(l, r)) : nullptr;
                case TokenType::OP_POW: return make_double(std::pow(l, r));
                case TokenType::OP_EQ: return make_bool(l == r);
                case TokenType::OP_NE: return make_bool(l != r);
                case TokenType::OP_LT: return make_bool(l < r);
                case TokenType::OP_GT: return make_bool(l > r);
                case TokenType::OP_LE: return make_bool(l <= r);
                case TokenType::OP_GE: return make_bool(l >= r);
                default: return nullptr;
            }
        } else {
            ValueTypeList::INT_V l = std::stoll(left->value);
            ValueTypeList::INT_V r = std::stoll(right->value);

            switch (op) {
                case TokenType::OP_PLUS: return make_int(l + r);
                case TokenType::OP_MINUS: return make_int(l - r);
                case TokenType::OP_MUL: return make_int(l * r);
                case TokenType::OP_DIV: 
                    return r != 0 ? make_int(l / r) : nullptr;
                case TokenType::OP_INT_DIV: 
                    return r != 0 ? make_int(l / r) : nullptr;
                case TokenType::OP_MOD: 
                    return r != 0 ? make_int(l % r) : nullptr;
                case TokenType::OP_POW: 
                    return make_int(static_cast<ValueTypeList::INT_V>(
                        std::pow(l, r)));
                case TokenType::OP_EQ: return make_bool(l == r);
                case TokenType::OP_NE: return make_bool(l != r);
                case TokenType::OP_LT: return make_bool(l < r);
                case TokenType::OP_GT: return make_bool(l > r);
                case TokenType::OP_LE: return make_bool(l <= r);
                case TokenType::OP_GE: return make_bool(l >= r);
                default: return nullptr;
            }
        }
    }

    if (left->literal_type == TokenType::LIT_STR && 
        right->literal_type == TokenType::LIT_STR) {
            if (op == TokenType::OP_PLUS)
                return make_str(left->value + right->value);
            if (op == TokenType::OP_EQ)
                return make_bool(left->value == right->value);
            if (op == TokenType::OP_NE)
                return make_bool(left->value != right->value);
    }

    if (left->literal_type == TokenType::LIT_BOOL && 
        right->literal_type == TokenType::LIT_BOOL) {
            ValueTypeList::BOOL_V l = (left->value == "true");
            ValueTypeList::BOOL_V r = (right->value == "true");

        switch (op) {
            case TokenType::OP_AND: return make_bool(l && r);
            case TokenType::OP_OR: return make_bool(l || r);
            case TokenType::OP_EQ: return make_bool(l == r);
            case TokenType::OP_NE: return make_bool(l != r);
            default: return nullptr;
        }
    }

    if (left->literal_type == TokenType::LIT_NULL || 
        right->literal_type == TokenType::LIT_NULL) {
        if (op == TokenType::OP_EQ) 
            return make_bool(left->literal_type == right->literal_type);
        if (op == TokenType::OP_NE) 
            return make_bool(left->literal_type != right->literal_type);
    }

    return nullptr;
}


bool OptimizationVisitor::literal_cast(LiteralNodeAST* l){
    if(l->literal_type == TokenType::LIT_BOOL){
        return l->value == "true" ? true : false; 
    } else if (l->literal_type == TokenType::LIT_INT) {
        ValueTypeList::INT_V value = std::stoll(l->value);
        return value ? true : false;
    } else if (l->literal_type == TokenType::LIT_DOUBLE) {
        ValueTypeList::DOUBLE_V value = std::stod(l->value);
        return value ? true : false;
    } else if (l->literal_type == TokenType::LIT_STR) {
        return !(l->value.empty());
    } else if (l->literal_type == TokenType::LIT_NULL) {
        return false;
    }
    return false;
}