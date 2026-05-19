#ifndef BUILDS_HPP
#define BUILDS_HPP

#include "../semantics/value.hpp"
#include "functions.hpp"

#include <variant>
#include <string>
#include <memory>
#include <functional>
#include <iostream>


class Scope;


struct BuiltinFunctionData {
    std::string name;
    int count_args;
    bool is_ellipsis_args = false;
    std::function<Value(const std::vector<Value>&)> built_in_func = nullptr;
};

struct BuiltinVariableData {
    std::string name;
    std::string type_name;
    bool is_const = true;
    bool is_init = true;
    size_t slot_index = 0;
};

struct BuiltinClassData {
    std::string name;
    std::shared_ptr<Scope> class_scope = nullptr;
};


using BuiltinData = std::variant<
    BuiltinFunctionData, BuiltinVariableData, BuiltinClassData>;

namespace builtin_data{

    namespace functions{

        auto print = printSystem;
        auto is_type = type_valueSystem;

    }

    namespace classes{
        
    }

    namespace variables{

    }

}


#endif