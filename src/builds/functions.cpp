#include "../../include/builds/functions.hpp"


Value printSystem(const std::vector<Value>& objects){
    for(const auto& v : objects) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    return Value();
}

Value type_valueSystem(const std::vector<Value>& value){
    return Value(value.back().type_to_string());
}