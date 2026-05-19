#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "../semantics/value.hpp"

#include <iostream>


Value printSystem(const std::vector<Value>& objects);
Value type_valueSystem(const std::vector<Value>& value);

#endif