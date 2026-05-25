#include "../../include/addition/builds_manager.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/semantics/value.hpp"

#include "iostream"

BuildInClass::BuildInClass(const std::string& class_name, 
    BuildInModule& parent_builder, std::shared_ptr<Scope> scope) : 
        class_name(class_name), parent_builder(parent_builder), 
            class_scope(scope){}

BuildInClass& BuildInClass::add_method(const std::string& name, uint8_t count_args,
    bool is_ellipsis_args, const std::string& ret_type, 
        std::function<Value(const std::vector<Value>&)> func, 
            const std::string& modif, bool is_std){
                auto sym = std::make_shared<SymbolInfo>();
                sym->type = SymbolType::FUNCTION;
                sym->type_name = ret_type;
                sym->count_args = count_args;
                sym->is_ellipsis_args = is_ellipsis_args;
                sym->built_in_func = func;
                sym->is_built_in = true;
                sym->in_class = true;
                sym->is_std = is_std;
                sym->access_modifier = modif;
                class_scope->symbols[name] = sym;
                return *this;
}

BuildInClass& BuildInClass::add_field(const std::string& name, 
    const std::string& type, bool is_const, bool is_init, 
        const std::string& modif,bool is_std){
            auto sym = std::make_shared<SymbolInfo>();
            sym->type = SymbolType::VARIABLE;
            sym->type_name = type;
            sym->is_const = is_const;
            sym->is_init = is_init;
            sym->is_built_in = true;
            sym->in_class = true;
            sym->is_std = is_std;
            sym->access_modifier = modif;
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
    uint8_t count_args, bool is_ellipsis_args, const std::string& ret_type, 
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

BuildInManager::BuildInManager(ErrorManager& error_manager) : 
    error_manager(error_manager){
        register_std();
        all_standart_modules["io"] = [this](){this->register_io();};
        all_standart_modules["math"] = [this](){this->register_math();};
        all_standart_modules["array"] = [this](){this->register_array();};
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

void BuildInManager::register_io(){
    create_module("io")
        .add_function("print", 0, true, "Null", 
            [](std::vector<Value> values) -> Value {
                for(const auto& v : values){
                    std::cout << v << " ";
                }
                return Value();
            })
        .add_function("input", 1, false, "Str", 
            [](std::vector<Value> values) -> Value {
                if(!values.empty()){
                    std::cout << values.back();
                }
                Value x;
                std::cin >> x;
                return x;
            });
}

void BuildInManager::register_math(){
    create_module("math")
        .add_class("Matrix")
            .end_class()
        .add_variable("PI", "Double", true);
}

void BuildInManager::register_array(){
    create_module("array")
        .add_class("Array")
            .add_method("new", 0, false, "Array", 
                [this](std::vector<Value>) -> Value {
                    auto class_def = modules["array"]->symbols["Array"];
                    auto array = std::make_shared<ArrayObject>(class_def);
                    return Value(array);
                })
            .add_method("delete", 0, false, "Null", 
                [](std::vector<Value>) -> Value {
                    return Value();
                })
            .add_method("push", 1, false, "Null", 
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    if(values.size() < 2){
                        throw RuntimeError(
                            "Метод push(value) ожидает 1 аргумент");
                    }
                    arr->elements.push_back(values[1]);
                    return Value();
                })
            .add_method("pop", 0, false, "auto", 
                [](std::vector<Value> values) -> Value{
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    if(arr->elements.empty()){
                        throw RuntimeError("Объект Array пуст");
                    }
                    auto val = arr->elements.back();
                    arr->elements.pop_back();
                    return val;
                })
            .add_method("at", 1, false, "auto", 
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    if(values.size() < 2){
                        throw RuntimeError(
                            "Метод at(index) ожидает 1 аргумент");
                    }
                    auto index = values[1].as_int();
                    if (index < 0 || index >= arr->elements.size()) {
                        throw RuntimeError("Индекс " + std::to_string(index) + 
                            " вышел за пределы массива");
                    }
                    return arr->elements[index];
                })
            .add_method("insert", 2, false, "Null", 
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    if(values.size() < 3){
                        throw RuntimeError(
                            "Метод insert(index, value) ожидает 2 аргументa");
                    }

                    auto index = values[1].as_int();
                    if (index < 0) {
                        throw RuntimeError("Индекс " + std::to_string(index) + 
                            " не может быть меньше нуля");
                    }
                    size_t size = arr->elements.size();
                    if (size == 0) {
                        index = 0; 
                    } else if (index > size) {
                        index %= size;
                    }

                    auto it = arr->elements.begin() + index;
                    arr->elements.insert(it, values[2]);
                    return Value();
                })
            .end_class();
}