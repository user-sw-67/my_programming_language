#include "../../include/addition/builds_manager.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/semantics/value.hpp"


BuildInClass::BuildInClass(const std::string& class_name, 
    BuildInModule& parent_builder, std::shared_ptr<Scope> scope) : 
        class_name(class_name), parent_builder(parent_builder), 
            class_scope(scope){}

BuildInClass& BuildInClass::add_method(const std::string& name, int count_args,
    bool is_ellipsis_args, const std::string& ret_type, 
        std::function<Value(const std::vector<Value>&)> func, bool is_std){
            auto sym = std::make_shared<SymbolInfo>();
            sym->type = SymbolType::FUNCTION;
            sym->type_name = ret_type;
            sym->count_args = count_args;
            sym->is_ellipsis_args = is_ellipsis_args;
            sym->built_in_func = func;
            sym->is_built_in = true;
            sym->in_class = true;
            sym->is_std = is_std;
            class_scope->symbols[name] = sym;
            return *this;
}

BuildInClass& BuildInClass::add_field(const std::string& name, 
    const std::string& type, bool is_const, bool is_init, bool is_std){
        auto sym = std::make_shared<SymbolInfo>();
        sym->type = SymbolType::VARIABLE;
        sym->type_name = type;
        sym->is_const = is_const;
        sym->is_init = is_init;
        sym->is_built_in = true;
        sym->in_class = true;
        sym->is_std = is_std;
        class_scope->symbols[name] = sym;
        return *this;
}

BuildInModule& BuildInClass::end_class(){
    return parent_builder;
}

BuildInModule::BuildInModule(const std::string& module_name, 
    std::shared_ptr<Scope> scope) : 
        module_name(module_name), module_scope(scope){}

BuildInClass BuildInModule::add_class(const std::string& name, bool is_std){
    auto sym = std::make_shared<SymbolInfo>();
    sym->type = SymbolType::CLASS;
    sym->is_built_in = true;
    sym->is_std = is_std;
    sym->class_scope = std::make_shared<Scope>(module_scope);
    module_scope->symbols[name] = sym;
    return BuildInClass(name, *this, sym->class_scope);
}

BuildInModule& BuildInModule::add_function(const std::string& name, 
    int count_args, bool is_ellipsis_args, const std::string& ret_type, 
        std::function<Value(const std::vector<Value>&)> func, bool is_std){
            auto sym = std::make_shared<SymbolInfo>();
            sym->type = SymbolType::FUNCTION;
            sym->type_name = ret_type;
            sym->count_args = count_args;
            sym->is_ellipsis_args = is_ellipsis_args;
            sym->built_in_func = func;
            sym->is_built_in = true;
            sym->is_std = is_std;
            module_scope->symbols[name] = sym;
            return *this;
}

BuildInModule& BuildInModule::add_variable(const std::string& name, 
    const std::string& type, bool is_const, bool is_std){
        auto sym = std::make_shared<SymbolInfo>();
        sym->type = SymbolType::VARIABLE;
        sym->type_name = type;
        sym->is_const = is_const;
        sym->is_built_in = true;
        sym->is_init = true;
        sym->is_std = is_std;
        module_scope->symbols[name] = sym;
        return *this;
}

BuildInModule BuildInManager::create_module(const std::string& name){
    auto scope = std::make_shared<Scope>(nullptr);
    modules[name] = scope;
    return BuildInModule(name, scope);
}

std::shared_ptr<Scope> BuildInManager::get_standard_module(
    const std::string& name){
        auto it = modules.find(name);
        if (it != modules.end()) {
            return it->second;
        }
        auto it_all_mod = all_standart_modules.find(name);
        if (it_all_mod != all_standart_modules.end()) {
            it_all_mod->second();
            return modules[name];
        }
        throw RuntimeError("Стандартный модуль " + name + " не найден");
}

bool BuildInManager::is_module_standard(const std::string& name) const {
    auto it = all_standart_modules.find(name);
    if(it != all_standart_modules.end()){
        return true;
    }
    return false;
}

BuildInManager::BuildInManager(){
    register_std();
    all_standart_modules["math"] = [this](){this->register_math();};
}

void BuildInManager::register_std(){
    create_module("std")
        .add_class("Int", true)
            .end_class()
        .add_class("Double", true)
            .end_class()
        .add_class("Str", true)
            .end_class()
        .add_class("Bool", true)
            .end_class()
        .add_class("Null", true)
            .end_class()
        .add_function("type", 1, false, "Str", 
            [](std::vector<Value> value) -> Value {
                return Value(value.back().type_to_string());
            }, true)
        .add_variable("__module__", "Str", true, true);
}

void BuildInManager::register_math(){
    create_module("math")
        .add_class("Matrix")
            .end_class()
        .add_variable("PI", "Double", true);
}