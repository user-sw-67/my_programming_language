#include "../../include/addition/builds_manager.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/semantics/value.hpp"

#include "iostream"


BuildInClass::BuildInClass(const std::string& class_name, 
    BuildInModule& parent_builder, std::shared_ptr<Scope> scope) : 
        class_name(class_name), class_scope(scope), 
            parent_builder(parent_builder) {}

BuildInClass& BuildInClass::add_method(const std::string& name, 
    uint8_t count_args, bool is_ellipsis_args, uint8_t count_elem_default, 
        const std::string& ret_type, 
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
                    sym->count_elem_default = count_elem_default;
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
    uint8_t count_args, bool is_ellipsis_args, uint8_t count_elem_default, 
        const std::string& ret_type, 
            std::function<Value(const std::vector<Value>&)> func, bool is_std){
                auto sym = std::make_shared<SymbolInfo>();
                sym->type = SymbolType::FUNCTION;
                sym->type_name = ret_type;
                sym->count_args = count_args;
                sym->is_ellipsis_args = is_ellipsis_args;
                sym->built_in_func = func;
                sym->is_built_in = true;
                sym->is_std = is_std;
                sym->count_elem_default = count_elem_default;
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
    std::shared_ptr<Scope> std_lib = nullptr;
    if(name != "std"){
        std_lib = get_standard_module("std");
    }
    auto scope = std::make_shared<Scope>(std_lib);
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
        .add_function("type", 1, false, 0, "Str", 
            [](std::vector<Value> values) -> Value {
                return Value(values.back().type_to_string());
            }, true)
        .add_variable("__module__", "Str", true, true)
        .add_function("is_primitive", 1, false, 0, "Bool", 
            [](std::vector<Value> values) -> Value {
                if(values.size() < 1 || values.size() > 1){
                    throw RuntimeError(
                        "Метод is_primitive(object) ожидает 1 аргумент");
                }
                Value v = values.back();
                if(v.is_bool() || v.is_double() || 
                    v.is_int() || v.is_str() || v.is_null()){
                        return Value(true);
                }
                return Value(false);
            }, true)
        .add_function("primitive_cast", 2, false, 0, "auto", 
            [](std::vector<Value> values) -> Value {
                if(values.size() < 2 || values.size() > 2){
                    throw RuntimeError("Метод primitive_cast(type_name, object)"
                        " ожидает 2 аргумента");
                }
                Value v = values[1];
                std::string type = values[0].as_str();
                if(v.is_bool()){
                    if(type == "Int"){
                        return Value(
                            static_cast<ValueTypeList::INT_V>(v.as_bool()));
                    } else if (type == "Double") {
                        return Value(
                            static_cast<ValueTypeList::DOUBLE_V>(v.as_bool()));
                    } else if (type == "Bool") {
                        return Value(
                            static_cast<ValueTypeList::BOOL_V>(v.as_bool()));
                    } else if (type == "Str") {
                        throw TypeError(
                            "Каст обьекта типа Bool к типу Str невозможен");
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError("Переданный тип не является примитивным");

                } else if(v.is_int()) {
                    if(type == "Int"){
                        return Value(
                            static_cast<ValueTypeList::INT_V>(v.as_int()));
                    } else if (type == "Double") {
                        return Value(
                            static_cast<ValueTypeList::DOUBLE_V>(v.as_int()));
                    } else if (type == "Bool") {
                        return Value(
                            static_cast<ValueTypeList::BOOL_V>(v.as_int()));
                    } else if (type == "Str") {
                        throw Value(static_cast<ValueTypeList::STR_V>(
                            std::to_string(v.as_int())));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError("Переданный тип не является примитивным");

                } else if(v.is_double()) {
                    if(type == "Int"){
                        return Value(
                            static_cast<ValueTypeList::INT_V>(v.as_double()));
                    } else if (type == "Double") {
                        return Value(static_cast<ValueTypeList::DOUBLE_V>(
                            v.as_double()));
                    } else if (type == "Bool") {
                        return Value(
                            static_cast<ValueTypeList::BOOL_V>(v.as_double()));
                    } else if (type == "Str") {
                        throw Value(static_cast<ValueTypeList::STR_V>(
                            std::to_string(v.as_double())));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError("Переданный тип не является примитивным");

                } else if(v.is_str()) {
                    if(type == "Int"){
                        try {
                            return Value(static_cast<ValueTypeList::INT_V>(
                                std::stoi(v.as_str())));
                        } catch (...) {
                            throw TypeError("Каст данного обьекта типа Str к "
                                "типу Int невозможен");
                        }
                    } else if (type == "Double") {
                        try {
                            return Value(static_cast<ValueTypeList::DOUBLE_V>(
                                std::stod(v.as_str())));
                        } catch (...) {
                            throw TypeError("Каст данного обьекта типа Str к "
                                "типу Double невозможен");
                        }
                    } else if (type == "Bool") {
                        return Value(static_cast<ValueTypeList::BOOL_V>(
                            !v.as_str().empty()));
                    } else if (type == "Str") {
                        throw Value(
                            static_cast<ValueTypeList::STR_V>(v.as_str()));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError("Переданный тип не является примитивным");

                } else if(v.is_null()) {
                    if(type == "Int"){
                        return Value(static_cast<ValueTypeList::INT_V>(0));
                    } else if (type == "Double") {
                        return Value(static_cast<ValueTypeList::DOUBLE_V>(0.0));
                    } else if (type == "Bool") {
                        return Value(static_cast<ValueTypeList::BOOL_V>(false));
                    } else if (type == "Str") {
                        throw Value(static_cast<ValueTypeList::STR_V>(""));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError("Переданный тип не является примитивным");

                }
                throw TypeError("Объект не примитивного типа");
            }, true);
}

void BuildInManager::register_io(){
    create_module("io")
        .add_function("print", 0, true, 0, "Null", 
            [](std::vector<Value> values) -> Value {
                if(!values.empty()){
                    for(const auto& v : values){
                        std::cout << v << " ";
                    }
                }
                std::cout << std::endl;
                return Value();
            })
        .add_function("input", 1, false, 1, "Str", 
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
            .add_method("new", 0, false, 0, "Array", 
                [this](std::vector<Value>) -> Value {
                    auto class_def = modules["array"]->symbols["Array"];
                    auto array = std::make_shared<ArrayObject>(class_def);
                    return Value(array);
                })
            .add_method("delete", 0, false, 0, "Null", 
                [](std::vector<Value>) -> Value {
                    return Value();
                })
            .add_method("push", 1, false, 0, "Null", 
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
            .add_method("pop", 0, false, 0, "auto", 
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
            .add_method("at", 1, false, 0, "auto", 
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
                    if (index < 0 || static_cast<size_t>(index) >= arr->elements.size()) {
                        throw RuntimeError("Индекс " + std::to_string(index) + 
                            " вышел за пределы массива");
                    }
                    return arr->elements[index];
                })
            .add_method("insert", 2, false, 0, "Null", 
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
                    } else if (static_cast<size_t>(index) > size) {
                        index %= size;
                    }

                    auto it = arr->elements.begin() + index;
                    arr->elements.insert(it, values[2]);
                    return Value();
                })
            .add_method("erase", 1, false, 0, "auto", 
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    if(values.size() < 2){
                        throw RuntimeError(
                            "Метод erase(index) ожидает 1 аргумент");
                    }
                    if (arr->elements.empty()) {
                        throw RuntimeError(
                            "Невозможно удалить элемент: массив пуст");
                    }

                    auto index = values[1].as_int();
                    if (index < 0) {
                        throw RuntimeError("Индекс " + std::to_string(index) + 
                            " не может быть меньше нуля");
                    }
                    size_t size = arr->elements.size();
                    if (static_cast<size_t>(index) >= size) {
                        index %= size;
                    }

                    auto it = arr->elements.begin() + index;
                    auto val = *it;
                    arr->elements.erase(it);
                    return val;
                })
            .add_method("size", 0, false, 0, "Int", 
                [](std::vector<Value> values) -> Value{
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    return Value(static_cast<ValueTypeList::INT_V>(
                        arr->elements.size()));
                })
            .add_method("is_empty", 0, false, 0, "Bool", 
                [](std::vector<Value> values) -> Value{
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    return Value(static_cast<ValueTypeList::BOOL_V>(
                        arr->elements.empty()));
                })
            .add_method("clear", 0, false, 0, "Null", 
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    arr->elements.clear();
                    return Value();
                })
            .add_method("sort", 1, false, 1, "Null", 
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array");
                    }
                    if (values.size() == 1) {
                        std::sort(arr->elements.begin(), arr->elements.end(), 
                            [](const Value& a, const Value& b) {
                                return (a < b).as_bool();
                            }
                        );
                    } else if (values.size() == 2) {
                        if(!values[1].is_function()){
                            throw RuntimeError(
                                "predicate должен быть функцией");
                        }
                        ValueTypeList::FUNCTION_V predicate = 
                            values[1].as_function();
                        if(predicate->count_args != 2){
                            throw RuntimeError(
                                "predicate должен принимать 2 аргумента");
                        }
                        std::sort(arr->elements.begin(), arr->elements.end(), 
                            [&predicate](const Value& a, const Value& b){
                                // Дописать когда появится запуск(пока сортировка по умолчанию) и добавить проверку на Bool
                                return (a < b).as_bool();
                            }
                        );
                    } else {
                        throw RuntimeError(
                            "Метод sort(predicate) ожидает 0 или 1 аргумент");
                    }
                    return Value();
                })
            .end_class();
}