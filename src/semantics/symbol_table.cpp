#include "../../include/semantics/symbol_table.hpp"
#include "../../include/parser/ast.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/builds/builds.hpp"


Scope::Scope(std::shared_ptr<Scope> parent_ptr) : parent(parent_ptr) {
    if (parent) {
        next_slot = parent->next_slot;
    }
}
    
SymbolTable::SymbolTable() {
    current_scope = std::make_shared<Scope>(nullptr);
    global_scope = current_scope;
    max_slots_in_function = 0;
}

std::shared_ptr<Scope> SymbolTable::get_current_scope() const {
    return current_scope;
}

bool SymbolTable::init_builtins(const std::vector<BuiltinData>& objects) {
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

void SymbolTable::enter_scope() {
    current_scope = std::make_shared<Scope>(current_scope);
}

void SymbolTable::enter_function_scope() {
    current_scope = std::make_shared<Scope>(current_scope);
    current_scope->next_slot = 0;
    max_slots_in_function = 0;
}

void SymbolTable::exit_scope() {
    if (current_scope == global_scope) {
        throw RuntimeError(
            "Невозможно выйти из глобальной области видимости");
    }
    current_scope = current_scope->parent;
}

SymbolInfo* SymbolTable::lookup(const std::string& name) const {
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

SymbolInfo* SymbolTable::lookup_local(const std::string& name) const {
    auto it = current_scope->symbols.find(name);
    if(it != current_scope->symbols.end()) return (it->second).get();
    return nullptr;
}


SymbolInfo* SymbolTable::define(const std::string& name, SymbolType type) {
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

SymbolInfo* SymbolTable::define_variable(const std::string& name, 
    const std::string& type_name, bool is_const, bool is_init) {
        SymbolInfo* symbol = define(name, SymbolType::VARIABLE);
        symbol->type_name = type_name;
        symbol->is_const = is_const;
        symbol->is_init = is_init;
        return symbol;
}

SymbolInfo* SymbolTable::define_function(const std::string& name, 
    int count_args, bool is_ellipsis_args, FunctionNodeAST* body_ast) {
        SymbolInfo* symbol = define(name, SymbolType::FUNCTION);
        symbol->count_args = count_args;
        symbol->is_ellipsis_args = is_ellipsis_args;
        symbol->body_ast = body_ast;
        return symbol;
}

SymbolInfo* SymbolTable::define_class(const std::string& name, 
    std::shared_ptr<Scope> class_scope, bool is_has_parent, 
        const std::string& parent_name) {
            SymbolInfo* symbol = define(name, SymbolType::CLASS);
            symbol->parent_name = parent_name;
            symbol->class_scope = class_scope;
            return symbol;
}

size_t SymbolTable::get_current_slots_count() const {
    return max_slots_in_function;
}
