#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "../parser/ast.hpp"
#include "value.hpp"
#include "../addition/error_manager.hpp"
#include "../builds/builds.hpp"

#include <string>
#include <variant>
#include <functional>
#include <unordered_map>
#include <memory>



enum class SymbolType{
    VARIABLE,
    FUNCTION,
    CLASS,
};


struct SymbolInfo{
    std::string name;
    SymbolType type;
    bool is_built_in = false;

    std::string type_name;
    bool is_const = false;
    bool is_init = false;
    size_t slot_index = 0;

    int count_args;
    bool is_ellipsis_args = false;
    FunctionNodeAST* body_ast = nullptr;
    std::function<Value(const std::vector<Value>&)> built_in_func = nullptr;

    bool is_has_parent = false;
    std::string parent_name;
    std::shared_ptr<Scope> class_scope = nullptr;
};


struct Scope{
    std::unordered_map<std::string, std::shared_ptr<SymbolInfo>> symbols;
    std::shared_ptr<Scope> parent;
    size_t next_slot = 0;

    Scope(std::shared_ptr<Scope> parent_ptr) : parent(parent_ptr) {
        if (parent) {
            next_slot = parent->next_slot;
        }
    }
};


class SymbolTable{
private:
    std::shared_ptr<Scope> current_scope;
    std::shared_ptr<Scope> global_scope;
    size_t max_slots_in_function = 0;
    
public:
    SymbolTable() {
        current_scope = std::make_shared<Scope>(nullptr);
        global_scope = current_scope;
        max_slots_in_function = 0;
    }

    std::shared_ptr<Scope> get_current_scope() const {
        return current_scope;
    }

    bool init_builtins(const std::vector<BuiltinData>& objects) {
        if(current_scope != global_scope) {
            return false;
        }

        for (const auto& i : objects){
            std::visit([this](auto&& arg) {

                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, BuiltinVariableData>){
                    SymbolInfo* sym = define(arg.name, SymbolType::VARIABLE);
                    sym->is_built_in = true;
                    sym->type_name = arg.type_name;
                    sym->is_const = arg.is_const;
                    sym->slot_index = arg.slot_index;
                    sym->is_init = arg.is_init;

                } else if constexpr (std::is_same_v<T, BuiltinFunctionData>) {
                    SymbolInfo* sym = define(arg.name, SymbolType::FUNCTION);
                    sym->is_built_in = true;
                    sym->count_args = arg.count_args;
                    sym->is_ellipsis_args = arg.is_ellipsis_args;
                    sym->built_in_func = arg.built_in_func;

                } else if constexpr (std::is_same_v<T, BuiltinClassData>) {
                    SymbolInfo* sym = define(arg.name, SymbolType::CLASS);
                    sym->is_built_in = true;
                    sym->is_has_parent = false;
                    sym->class_scope = arg.class_scope;
                }

            }, i);
        }

        return true;
    }

    void enter_scope() {
        current_scope = std::make_shared<Scope>(current_scope);
    }

    void enter_function_scope() {
        current_scope = std::make_shared<Scope>(current_scope);
        current_scope->next_slot = 0;
        max_slots_in_function = 0;
    }

    void exit_scope() {
        if (current_scope == global_scope) {
            throw RuntimeError(
                "Невозможно выйти из глобальной области видимости");
        }
        current_scope = current_scope->parent;
    }

    SymbolInfo* lookup(const std::string& name) const {
        auto scope = current_scope;
        while (scope){
            auto it = scope->symbols.find(name);
            if(it != scope->symbols.end()){
                return (it->second).get();
            }
            scope = scope->parent;
        }
        return nullptr;
    }

    SymbolInfo* define(const std::string& name, SymbolType type) {
        if(current_scope->symbols.find(name) != current_scope->symbols.end()){
            throw RuntimeError(
                "Идентификатор уже определен в этой области видимости: " 
                    + name);
        }

        SymbolInfo symbol;
        symbol.name = name;
        symbol.type = type;
        
        if (type == SymbolType::VARIABLE) {
            symbol.slot_index = current_scope->next_slot++;
            if (current_scope->next_slot > max_slots_in_function) {
                max_slots_in_function = current_scope->next_slot;
            }
        }

        current_scope->symbols[name] = std::make_shared<SymbolInfo>(symbol);
        return current_scope->symbols[name].get();
    }

    SymbolInfo* define_variable(const std::string& name, 
        const std::string& type_name, bool is_const = false, 
            bool is_init = false) {
                SymbolInfo* symbol = define(name, SymbolType::VARIABLE);
                symbol->type_name = type_name;
                symbol->is_const = is_const;
                symbol->is_init = is_init;
                return symbol;
    }

    SymbolInfo* define_function(const std::string& name, int count_args = 0,
        bool is_ellipsis_args = false, FunctionNodeAST* body_ast = nullptr) {
            SymbolInfo* symbol = define(name, SymbolType::FUNCTION);
            symbol->count_args = count_args;
            symbol->is_ellipsis_args = is_ellipsis_args;
            symbol->body_ast = body_ast;
            return symbol;
    }

    SymbolInfo* define_class(const std::string& name, 
        std::shared_ptr<Scope> class_scope = nullptr, 
            bool is_has_parent = false, const std::string& parent_name = "") {
                SymbolInfo* symbol = define(name, SymbolType::CLASS);
                symbol->parent_name = parent_name;
                symbol->class_scope = class_scope;
                return symbol;
    }

    size_t get_current_slots_count() const {
        return max_slots_in_function;
    }
};

#endif