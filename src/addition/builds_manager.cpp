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
                    sym->name = name;
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
            sym->name = name;
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
    sym->name = name;
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
                sym->name = name;
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
        sym->name = name;
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
        throw RuntimeError("Стандартный модуль " + name + " не найден",
            error_code::RUN_2001);
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
        .add_class("Function", true)
            .end_class()
        .add_class("Type", true)
            .end_class()
        .add_class("Range", true)
            .add_method("new", 3, false, 1, "Range",
                [](std::vector<Value> values) -> Value {
                    return values.at(0);
                })
            .add_method("delete", 0, false, 0, "Null",
                [](std::vector<Value>) -> Value {
                    return Value();
                })
            .add_method("iter", 0, false, 0, "Range",
                [](std::vector<Value> values) -> Value {
                    return values.at(0);
                })
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
                        "Метод is_primitive(object) ожидает 1 аргумент",
                            error_code::RUN_2002);
                }
                Value v = values.back();
                if(v.is_bool() || v.is_double() ||
                    v.is_int() || v.is_str() || v.is_null()){
                        return Value(true);
                }
                return Value(false);
            }, true)
        .add_function("typeof", 1, false, 0, "Type",
            [this](std::vector<Value> values) -> Value {
                if(values.size() != 1){
                    throw RuntimeError("Метод typeof(object) ожидает 1 аргумент",
                        error_code::RUN_2003);
                }
                const Value& v = values.back();
                auto std_scope = modules["std"];
                auto lookup_std = [&std_scope](
                    const std::string& name) -> SymbolInfo* {
                        auto it = std_scope->symbols.find(name);
                        return it != std_scope->symbols.end() ?
                            it->second.get() : nullptr;
                };

                SymbolInfo* class_sym = nullptr;
                if(v.is_int()) class_sym = lookup_std("Int");
                else if(v.is_double()) class_sym = lookup_std("Double");
                else if(v.is_bool()) class_sym = lookup_std("Bool");
                else if(v.is_str()) class_sym = lookup_std("Str");
                else if(v.is_null()) class_sym = lookup_std("Null");
                else if(v.is_function()) class_sym = lookup_std("Function");
                else if(v.is_type()) class_sym = lookup_std("Type");
                else if(v.is_object()) class_sym = v.as_object()->
                    class_definition.get();

                if(!class_sym){
                    throw RuntimeError(
                        "Не удалось определить тип переданного объекта",
                            error_code::RUN_2004);
                }
                return Value(ValueTypeList::TYPE_V{class_sym});
            }, true)
        .add_function("primitive_cast", 2, false, 0, "auto",
            [](std::vector<Value> values) -> Value {
                if(values.size() != 2){
                    throw RuntimeError("Метод primitive_cast(type, object) "
                        "ожидает 2 аргумента", error_code::RUN_2005);
                }
                if(!values[0].is_type() || !values[0].as_type().info){
                    throw TypeError("Первый аргумент primitive_cast(type, "
                        "object) должен быть значением типа Type",
                            error_code::RUN_4001);
                }

                Value v = values[1];
                const std::string& type = values[0].as_type().info->name;

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
                        return Value(static_cast<ValueTypeList::STR_V>(
                            v.as_bool() ? "true" : "false"));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError(
                        "Тип " + type + " не является примитивным",
                            error_code::RUN_4002);

                } else if(v.is_int()) {
                    if(type == "Int"){
                        return Value(
                            static_cast<ValueTypeList::INT_V>(v.as_int()));
                    } else if (type == "Double") {
                        return Value(
                            static_cast<ValueTypeList::DOUBLE_V>(v.as_int()));
                    } else if (type == "Bool") {
                        return Value(static_cast<ValueTypeList::BOOL_V>(
                            v.as_int() != 0));
                    } else if (type == "Str") {
                        return Value(static_cast<ValueTypeList::STR_V>(
                            std::to_string(v.as_int())));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError(
                        "Тип " + type + " не является примитивным",
                            error_code::RUN_4003);

                } else if(v.is_double()) {
                    if(type == "Int"){
                        return Value(
                            static_cast<ValueTypeList::INT_V>(v.as_double()));
                    } else if (type == "Double") {
                        return Value(static_cast<ValueTypeList::DOUBLE_V>(
                            v.as_double()));
                    } else if (type == "Bool") {
                        return Value(static_cast<ValueTypeList::BOOL_V>(
                            v.as_double() != 0.0));
                    } else if (type == "Str") {
                        return Value(static_cast<ValueTypeList::STR_V>(
                            std::to_string(v.as_double())));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError(
                        "Тип " + type + " не является примитивным",
                            error_code::RUN_4004);

                } else if(v.is_str()) {
                    if(type == "Int"){
                        try {
                            return Value(static_cast<ValueTypeList::INT_V>(
                                std::stoll(v.as_str())));
                        } catch (...) {
                            throw TypeError("Каст строки \"" + v.as_str() +
                                "\" к типу Int невозможен",
                                    error_code::RUN_4005);
                        }
                    } else if (type == "Double") {
                        try {
                            return Value(static_cast<ValueTypeList::DOUBLE_V>(
                                std::stod(v.as_str())));
                        } catch (...) {
                            throw TypeError("Каст строки \"" + v.as_str() +
                                "\" к типу Double невозможен",
                                    error_code::RUN_4006);
                        }
                    } else if (type == "Bool") {
                        return Value(static_cast<ValueTypeList::BOOL_V>(
                            !v.as_str().empty()));
                    } else if (type == "Str") {
                        return Value(
                            static_cast<ValueTypeList::STR_V>(v.as_str()));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError(
                        "Тип " + type + " не является примитивным",
                            error_code::RUN_4007);

                } else if(v.is_null()) {
                    if(type == "Int"){
                        return Value(static_cast<ValueTypeList::INT_V>(0));
                    } else if (type == "Double") {
                        return Value(static_cast<ValueTypeList::DOUBLE_V>(0.0));
                    } else if (type == "Bool") {
                        return Value(static_cast<ValueTypeList::BOOL_V>(false));
                    } else if (type == "Str") {
                        return Value(
                            static_cast<ValueTypeList::STR_V>("null"));
                    } else if (type == "Null") {
                        return Value();
                    }
                    throw TypeError(
                        "Тип " + type + " не является примитивным",
                            error_code::RUN_4008);

                }
                throw TypeError("primitive_cast применим только к "
                    "примитивным значениям (Int, Double, Bool, Str, Null)",
                        error_code::RUN_4009);
            }, true);

    modules["std"]->symbols["Range"]->is_iter_obj = true;
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
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3001);
                    }
                    if(values.size() < 2){
                        throw RuntimeError(
                            "Метод push(value) ожидает 1 аргумент",
                                error_code::RUN_3002);
                    }
                    arr->elements.push_back(values[1]);
                    return Value();
                })
            .add_method("pop", 0, false, 0, "auto",
                [](std::vector<Value> values) -> Value{
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3003);
                    }
                    if(arr->elements.empty()){
                        throw RuntimeError("Объект Array пуст",
                            error_code::RUN_3004);
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
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3005);
                    }
                    if(values.size() < 2){
                        throw RuntimeError(
                            "Метод at(index) ожидает 1 аргумент",
                                error_code::RUN_3006);
                    }
                    auto index = values[1].as_int();
                    if (index < 0 || static_cast<size_t>(index) >= arr->elements.size()) {
                        throw RuntimeError("Индекс " + std::to_string(index) +
                            " вышел за пределы массива", error_code::RUN_3007);
                    }
                    return arr->elements[index];
                })
            .add_method("insert", 2, false, 0, "Null",
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3008);
                    }
                    if(values.size() < 3){
                        throw RuntimeError(
                            "Метод insert(index, value) ожидает 2 аргументa",
                                error_code::RUN_3009);
                    }

                    auto index = values[1].as_int();
                    if (index < 0) {
                        throw RuntimeError("Индекс " + std::to_string(index) +
                            " не может быть меньше нуля", error_code::RUN_3010);
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
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3011);
                    }
                    if(values.size() < 2){
                        throw RuntimeError(
                            "Метод erase(index) ожидает 1 аргумент",
                                error_code::RUN_3012);
                    }
                    if (arr->elements.empty()) {
                        throw RuntimeError(
                            "Невозможно удалить элемент: массив пуст",
                                error_code::RUN_3013);
                    }

                    auto index = values[1].as_int();
                    if (index < 0) {
                        throw RuntimeError("Индекс " + std::to_string(index) +
                            " не может быть меньше нуля", error_code::RUN_3014);
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
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3015);
                    }
                    return Value(static_cast<ValueTypeList::INT_V>(
                        arr->elements.size()));
                })
            .add_method("is_empty", 0, false, 0, "Bool",
                [](std::vector<Value> values) -> Value{
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3016);
                    }
                    return Value(static_cast<ValueTypeList::BOOL_V>(
                        arr->elements.empty()));
                })
            .add_method("clear", 0, false, 0, "Null",
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3017);
                    }
                    arr->elements.clear();
                    return Value();
                })
            .add_method("sort", 1, false, 1, "Null",
                [](std::vector<Value> values) -> Value {
                    auto arr = std::dynamic_pointer_cast<ArrayObject>(
                        values.at(0).as_object());
                    if (!arr) {
                        throw RuntimeError("Ожидался объект класса Array",
                            error_code::RUN_3018);
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
                                "predicate должен быть функцией",
                                    error_code::RUN_3019);
                        }
                        ValueTypeList::FUNCTION_V predicate =
                            values[1].as_function();
                        if(predicate.info->count_args != 2){
                            throw RuntimeError(
                                "predicate должен принимать 2 аргумента",
                                    error_code::RUN_3020);
                        }
                        std::sort(arr->elements.begin(), arr->elements.end(), 
                            [&predicate](const Value& a, const Value& b){
                                // Дописать когда появится запуск(пока сортировка по умолчанию) и добавить проверку на Bool
                                return (a < b).as_bool();
                            }
                        );
                    } else {
                        throw RuntimeError(
                            "Метод sort(predicate) ожидает 0 или 1 аргумент",
                                error_code::RUN_3021);
                    }
                    return Value();
                })
            .add_method("iter", 0, false, 0, "Array",
                [](std::vector<Value> values) -> Value {
                    return values.at(0);
                })
            .end_class();

    modules["array"]->symbols["Array"]->is_iter_obj = true;
}