#include "../../include/semantics/visitors/definition_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/program_manager.hpp"
#include "../../include/parser/ast.hpp"
#include "../../include/parser/parser.hpp"
#include "../../include/lexer/lexer.hpp"
#include "../semantics_manager.hpp"

#include "functional"


DefinitionVisitor::DefinitionVisitor(SymbolTable& table, Managers& managers) : 
    BaseVisitorSemantics(table, managers){}

void DefinitionVisitor::visit(MakeNodeAST& node) {
    try{
        if(define_in_class){
            for(size_t i = 0; i < node.names.size(); ++i){
                SymbolInfo* symbol = table.define_variable(node.names[i], 
                    node.type_names[i], node.is_const, node.is_init());
                node.slot_indices.push_back(symbol->slot_index);
                symbol->in_class = true;
                symbol->access_modifier = current_access_modifier;
                symbol->is_static = current_is_static;
            }
        } else {
            for(size_t i = 0; i < node.names.size(); ++i){
                SymbolInfo* symbol = table.define_variable(node.names[i], 
                    node.type_names[i], node.is_const, node.is_init());
                node.slot_indices.push_back(symbol->slot_index);
            }
        }
    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR,
            error_code::SEM_1301);
    }
}

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
        SymbolInfo* symbol = table.define_function(node.name, 
            node.get_cout_parameters(), node.is_variadic_parameters(), &node);
        if(define_in_class){
            symbol->in_class = true;
            symbol->access_modifier = current_access_modifier;
            symbol->is_static = current_is_static;
        }
    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR,
            error_code::SEM_1302);
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

void DefinitionVisitor::visit(UseNodeAST& node) {
    if(node.is_build_in){
        std::shared_ptr<Scope> lib;
        try{
            lib = managers.build_in.get_standard_module(node.path_lib);
        }catch(const RuntimeError& e){
            managers.error.add(e.what(), node.location, Severity::ERROR,
                error_code::SEM_1101);
            return;
        }
        load_symbols(node, lib);
        return;
    }

    Module& mod = managers.source.modules[node.path_lib];

    if (mod.status == ModuleStatus::LOADING) {
        managers.error.add("Обнаружен циклический импорт с файлом "
            + node.path_lib, node.location, Severity::ERROR,
                error_code::SEM_1102);
        return;
    }

    if (mod.status == ModuleStatus::LOADED) {
        load_symbols(node, mod.scope);
        return;
    }

    mod.status = ModuleStatus::LOADING;

    if(!mod.ast){
        Lexer lexer(mod.lines, node.path_lib, managers);
        mod.tokens = lexer.get_tokens();
        Parser parser(mod.tokens, node.path_lib, managers);
        mod.ast = parser.parse();
    }

    if(!mod.scope){
        mod.scope = std::make_shared<Scope>(nullptr);
        auto std_lib = managers.build_in.get_standard_module("std");
        SymbolTable new_table(std_lib, node.path_lib);
        DefinitionVisitor def_vis(new_table, managers);
        mod.ast->accept(def_vis);
        mod.scope = new_table.get_global_scope();
        managers.source.active_index(mod);
    }
    mod.status = ModuleStatus::LOADED;
    load_symbols(node, mod.scope);
}

void DefinitionVisitor::visit(ClassNodeAST& node) {
    try{
        if(node.has_base_class()){
            if (node.name == node.base_class_name) {
                managers.error.add("Класс " + node.name +
                    " не может быть наследником самого себя", node.location,
                        Severity::ERROR, error_code::SEM_1201);
            }
            auto* base_info = table.lookup(node.base_class_name);
            if (!base_info || base_info->type != SymbolType::CLASS) {
                managers.error.add("Базовый класс " +
                    node.base_class_name + " не найден для " +
                        node.name, node.location, Severity::ERROR,
                            error_code::SEM_1202);
            } else if (base_info->is_built_in) {
                managers.error.add("Нельзя наследоваться от встроенного "
                    "класса " + node.base_class_name, node.location,
                        Severity::ERROR, error_code::SEM_1203);
            }
        }
        auto class_scope = get_class_scope(node);
        SymbolInfo* class_sym = table.define_class(node.name, class_scope,
            node.has_base_class(), node.base_class_name);

        bool has_own_iter = false;
        auto iter_it = class_scope->symbols.find("iter");
        if (iter_it != class_scope->symbols.end()) {
            SymbolInfo* iter_sym = iter_it->second.get();
            if (iter_sym->type != SymbolType::FUNCTION) {
                managers.error.add("iter в классе " + node.name +
                    " должен быть методом, а не полем", node.location,
                        Severity::ERROR, error_code::SEM_1204);
            } else {
                has_own_iter = true;
                if (iter_sym->count_args != 0 || iter_sym->is_ellipsis_args) {
                    managers.error.add("Метод iter() класса " + node.name +
                        " должен принимать 0 аргументов", node.location,
                            Severity::ERROR, error_code::SEM_1205);
                }
                if (iter_sym->access_modifier != "public") {
                    managers.error.add("Метод iter() класса " + node.name +
                        " должен быть public", node.location,
                            Severity::ERROR, error_code::SEM_1206);
                }
            }
        }
        bool parent_iterable = false;
        if (node.has_base_class()) {
            auto* base_sym = table.lookup(node.base_class_name);
            parent_iterable = base_sym && base_sym->is_iter_obj;
        }
        class_sym->is_iter_obj = has_own_iter || parent_iterable;

    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR,
            error_code::SEM_1303);
    }
}

void DefinitionVisitor::visit(MatchNodeAST& node) {}

void DefinitionVisitor::visit(TestNodeAST& node) {
    try{
        table.enter_scope();
        auto test_scope = table.get_current_scope();
        table.exit_scope();
        table.define_test(node.name, test_scope);
    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR,
            error_code::SEM_1304);
    }
}

void DefinitionVisitor::visit(AssertNodeAST& node) {}

void DefinitionVisitor::visit(RangeOperationNodeAST& node) {}

std::shared_ptr<Scope> DefinitionVisitor::get_class_scope(ClassNodeAST& node) {
    table.enter_scope();
    auto class_scope = table.get_current_scope();

    table.define_variable("this", node.name, true, true);
    if(node.has_base_class()) {
        SymbolInfo* super_sym = table.define("super", SymbolType::FUNCTION);
        super_sym->is_const = true;
        super_sym->in_class = true;
        super_sym->access_modifier = "public";
        super_sym->type_name = "Null";

        auto* base_info = table.lookup(node.base_class_name);
        if (base_info && base_info->class_scope) {
            auto it = base_info->class_scope->symbols.find("new");
            if (it != base_info->class_scope->symbols.end()) {
                SymbolInfo* base_new = it->second.get();
                super_sym->count_args = base_new->count_args;
                super_sym->count_elem_default = base_new->count_elem_default;
                super_sym->is_ellipsis_args = base_new->is_ellipsis_args;
                super_sym->is_built_in = base_new->is_built_in;
                super_sym->body_ast = base_new->body_ast;
            }
        }
    }

    define_in_class = true;

    for (auto& m : node.members){
        current_access_modifier = m.access_modifier;
        current_is_static = m.is_static;
        m.member_node->accept(*this);
    }

    define_in_class = false;

    current_access_modifier = "public";
    current_is_static = false;

    auto define_method = [this](const std::string& name){
        SymbolInfo* symbol = table.define(name, SymbolType::FUNCTION);
        symbol->is_built_in = true;
        symbol->in_class = true;
        symbol->count_args = 0;
        symbol->count_elem_default = 0;
        symbol->is_ellipsis_args = false;
        symbol->built_in_func = nullptr;
        symbol->type_name = "Null";
        return symbol;
    };

    SymbolInfo* new_ptr = table.lookup_local("new");
    if(!new_ptr){
        new_ptr = define_method("new");
    }

    SymbolInfo* del_ptr = table.lookup_local("delete");
    if(!del_ptr){
        del_ptr = define_method("delete");
    }

    if(del_ptr->type != SymbolType::FUNCTION || new_ptr->type != SymbolType::FUNCTION){
        managers.error.add("Объявлять поля с именем new или delete запрещено",
            node.location, Severity::ERROR, error_code::SEM_1207);
    }

    if(del_ptr && del_ptr->count_args != 0){
        managers.error.add("Деструктор класса " + node.name +
            " не должен иметь параметров", node.location, Severity::ERROR,
                error_code::SEM_1208);
    }

    auto valid_method = [this, &node](
        const std::string& name_method, SymbolInfo* ptr){
            if(ptr->is_static){
                managers.error.add(name_method + " класса " + node.name +
                    " не может иметь модификатор static", node.location,
                        Severity::WARNING, error_code::SEM_1209);
                ptr->is_static = false;
            }
            if(ptr->access_modifier != "public"){
                managers.error.add(name_method + " класса " + node.name +
                    " не может быть не public", node.location,
                        Severity::WARNING, error_code::SEM_1210);
                ptr->access_modifier = "public";
            }
            if(ptr->type_name != "auto" && ptr->type_name != "Null"){
                managers.error.add(name_method + " класса " + node.name +
                    " не должен объявлять тип возвращаемого значения (" +
                        ptr->type_name + ")", node.location, Severity::ERROR,
                            error_code::SEM_1211);
            }
    };
    valid_method("Конструктор", new_ptr);
    valid_method("Деструктор", del_ptr);

    table.exit_scope();
    return class_scope;
}

void DefinitionVisitor::load_symbols(UseNodeAST& node, 
    std::shared_ptr<Scope> scope){
        if(node.is_full()){
            for (const auto& [name, symbol_ptr] : scope->symbols){
                if(!node.is_build_in && symbol_ptr->is_built_in) continue;
                if(!symbol_ptr->is_built_in && 
                    node.path_lib != symbol_ptr->defined_in_file) continue;
                try{
                    table.import_symbol(name, symbol_ptr);
                }catch(const RuntimeError& e){
                    managers.error.add(e.what(),
                        node.location, Severity::ERROR, error_code::SEM_1103);
                }
            }
        }else{
            for(const auto& obj : node.objects){
                auto it = scope->symbols.find(obj.internal_name);

                if(it == scope->symbols.end() ||
                    (!node.is_build_in && it->second->is_built_in)){
                        managers.error.add("Идентификатор " +
                            obj.internal_name + " не найден в модуле " +
                                node.path_lib, obj.location, Severity::ERROR,
                                    error_code::SEM_1104);
                        continue;
                }
                if(!it->second->is_built_in &&
                    node.path_lib != it->second->defined_in_file) {
                        managers.error.add("Идентификатор " + obj.internal_name
                        + " импортирован внутри " + node.path_lib +
                        ", транзитивный импорт запрещен, для использования " +
                        obj.internal_name + " импортируйте модуль " +
                        it->second->defined_in_file, obj.location,
                            Severity::WARNING, error_code::SEM_1105);
                        continue;
                }

                std::string final_name = obj.alias.empty() ?
                    obj.internal_name : obj.alias;
                try{
                    table.import_symbol(final_name, it->second);
                }catch(const RuntimeError& e){
                    managers.error.add(e.what(),
                        node.location, Severity::ERROR, error_code::SEM_1106);
                }
            }
        }
}