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
                if(symbol->is_setter || symbol->is_getter){
                    std::string modif = symbol->is_setter ? "setter" : "getter";
                    managers.error.add("Переменная " + node.names[i] + 
                        " не может иметь модификатор " + modif, node.location, 
                            Severity::WARNING);
                }
                symbol->is_setter = false;
                symbol->is_getter = false;
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
        managers.error.add(e.what(), node.location, Severity::ERROR);
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
            symbol->is_setter = current_is_setter;
            symbol->is_getter = current_is_getter;
            symbol->is_static = current_is_static;
            if((symbol->is_setter || symbol->is_getter) && symbol->is_static){
                std::string modif = symbol->is_setter ? "setter" : "getter";
                managers.error.add("Метод " + node.name + 
                    " не может иметь модификаторы static и " + modif + 
                        " одновременно", node.location, Severity::WARNING);
                symbol->is_static = false;
            }
        }
    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR);
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
            managers.error.add(e.what(), node.location, Severity::ERROR);
            return;
        }
        load_symbols(node, lib);
        return;
    }

    Module& mod = managers.source.modules[node.path_lib];

    if (mod.status == ModuleStatus::LOADING) {
        managers.error.add("Обнаружен циклический импорт с файлом " 
            + node.path_lib, node.location, Severity::ERROR);
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
                        Severity::ERROR);
            }
            auto* base_info = table.lookup(node.base_class_name);
            if (!base_info || base_info->type != SymbolType::CLASS) {
                managers.error.add("Базовый класс " + 
                    node.base_class_name + " не найден для " +
                        node.name, node.location, Severity::ERROR);
            }
        }
        auto class_scope = get_class_scope(node);
        table.define_class(node.name, class_scope, 
            node.has_base_class(), node.base_class_name);

    } catch(const RuntimeError& e) {
        managers.error.add(e.what(), node.location, Severity::ERROR);
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
        managers.error.add(e.what(), node.location, Severity::ERROR);
    }
}

void DefinitionVisitor::visit(AssertNodeAST& node) {}

void DefinitionVisitor::visit(RangeOperationNodeAST& node) {}

std::shared_ptr<Scope> DefinitionVisitor::get_class_scope(ClassNodeAST& node) {
    table.enter_scope();
    auto class_scope = table.get_current_scope();

    table.define_variable("this", node.name, true, true);
    if(node.has_base_class()) 
        table.define_variable("super", node.base_class_name, true, true);

    define_in_class = true;

    for (auto& m : node.members){
        current_access_modifier = m.access_modifier;
        current_is_static = m.is_static;
        current_is_getter = m.is_getter;
        current_is_setter = m.is_setter;
        m.member_node->accept(*this);
    }

    define_in_class = false;

    current_access_modifier = "public";
    current_is_static = false;
    current_is_getter = false;
    current_is_setter = false;

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
        managers.error.add("Обьявлять поля с именем new или delete запрещено", 
            node.location, Severity::ERROR);
    }

    if(del_ptr && del_ptr->count_args != 0){
        managers.error.add("Деструктор класса " + node.name + 
            " не должен иметь параметров", node.location, Severity::ERROR);
    }

    auto valid_method = [this, &node](
        const std::string& name_method, SymbolInfo* ptr){
            if(ptr->is_setter || ptr->is_getter || ptr->is_static){
                std::string modif = ptr->is_setter ? "setter" : 
                    (ptr->is_getter ? "getter" : "static");
                managers.error.add(name_method + " класса " + node.name + 
                    " не может иметь модификатор " + modif, node.location, 
                        Severity::WARNING);
                ptr->is_setter = false;
                ptr->is_getter = false;
                ptr->is_static = false;
            }
            if(ptr->access_modifier != "public"){
                managers.error.add(name_method + " класса " + node.name + 
                    " не может быть не public", node.location, 
                        Severity::WARNING);
                ptr->access_modifier = "public";
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
                        node.location, Severity::ERROR);
                }
            }
        }else{
            for(const auto& obj : node.objects){
                auto it = scope->symbols.find(obj.internal_name);

                if(it == scope->symbols.end() || 
                    (!node.is_build_in && it->second->is_built_in)){
                        managers.error.add("Идентификатор " + 
                            obj.internal_name + " не найден в модуле " + 
                                node.path_lib, obj.location, Severity::ERROR);
                        continue;
                }
                if(!it->second->is_built_in && 
                    node.path_lib != it->second->defined_in_file) {
                        managers.error.add("Идентификатор " + obj.internal_name 
                        + " импортирован внутри " + node.path_lib + 
                        ", транзитивный импорт запрещен, для использования " + 
                        obj.internal_name + " импортируйте модуль " + 
                        it->second->defined_in_file, obj.location, 
                            Severity::WARNING);
                        continue;
                }
                
                std::string final_name = obj.alias.empty() ? 
                    obj.internal_name : obj.alias;
                try{
                    table.import_symbol(final_name, it->second);
                }catch(const RuntimeError& e){
                    managers.error.add(e.what(), 
                        node.location, Severity::ERROR);
                }
            }
        }
}