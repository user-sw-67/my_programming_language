#ifndef VALUE_HPP
#define VALUE_HPP

#include "../addition/error_manager.hpp"
#include "../lexer/token_list.hpp"
#include "symbol_table.hpp"

#include <variant>
#include <string>
#include <type_traits>


struct Object{
    std::shared_ptr<SymbolInfo> class_definition;
    std::unordered_map<std::string, Value> fields;

    Object(std::shared_ptr<SymbolInfo> definition) : 
        class_definition(definition) {}

    std::string get_name() const {
        return class_definition->name;
    }
};


namespace ValueTypeList{
    using NULL_V = std::monostate;
    using INT_V = int64_t;
    using DOUBLE_V = double;
    using BOOL_V = bool;
    using STR_V = std::string;
    using OBJECT_V = std::shared_ptr<Object>;
    using FUNCTION_V = SymbolInfo*;
}


template<typename T>
constexpr static bool IsArithmetic = std::is_same_v<T, ValueTypeList::DOUBLE_V> 
    || std::is_same_v<T, ValueTypeList::INT_V>;


class Value{
private:
    std::variant<
        ValueTypeList::NULL_V,
        ValueTypeList::INT_V,
        ValueTypeList::DOUBLE_V,
        ValueTypeList::BOOL_V,
        ValueTypeList::STR_V,
        ValueTypeList::OBJECT_V,
        ValueTypeList::FUNCTION_V,
    > data;

public:
    explicit Value() : data(ValueTypeList::NULL_V()) {}
    explicit Value(ValueTypeList::INT_V data) : data(data) {}
    explicit Value(ValueTypeList::DOUBLE_V data) : data(data) {}
    explicit Value(ValueTypeList::BOOL_V data) : data(data) {}
    explicit Value(ValueTypeList::STR_V data) : data(data) {}
    explicit Value(const ValueTypeList::OBJECT_V& data) : data(data) {}
    explicit Value(const ValueTypeList::FUNCTION_V& data) : data(data) {}

    ValueTypeList::INT_V as_int() const {
        return std::get<ValueTypeList::INT_V>(data);
    }

    ValueTypeList::DOUBLE_V as_double() const {
        return std::get<ValueTypeList::DOUBLE_V>(data);
    }

    ValueTypeList::BOOL_V as_bool() const {
        return std::get<ValueTypeList::BOOL_V>(data);
    }

    ValueTypeList::STR_V as_str() const {
        return std::get<ValueTypeList::STR_V>(data);
    }

    ValueTypeList::OBJECT_V as_object() const {
        return std::get<ValueTypeList::OBJECT_V>(data);
    }

    ValueTypeList::FUNCTION_V as_function() const {
        return std::get<ValueTypeList::FUNCTION_V>(data);
    }

    bool is_null() const {
        return std::holds_alternative<ValueTypeList::NULL_V>(data);
    }

    bool is_int() const {
        return std::holds_alternative<ValueTypeList::INT_V>(data);
    }

    bool is_double() const {
        return std::holds_alternative<ValueTypeList::DOUBLE_V>(data);
    }

    bool is_bool() const {
        return std::holds_alternative<ValueTypeList::BOOL_V>(data);
    }

    bool is_str() const {
        return std::holds_alternative<ValueTypeList::STR_V>(data);
    }

    bool is_object() const {
        return std::holds_alternative<ValueTypeList::OBJECT_V>(data);
    }

    bool is_function() const {
        return std::holds_alternative<ValueTypeList::FUNCTION_V>(data);
    }

    std::string type_to_string() const {
        return std::visit([](auto&& arg)-> std::string {
            using T = std::decay_t<decltype(arg)>;
        
            if constexpr (std::is_same_v<T, ValueTypeList::NULL_V>) {
                return "Null";
            } else if constexpr (std::is_same_v<T, ValueTypeList::INT_V>) {
                return "Int";
            } else if constexpr (std::is_same_v<T, ValueTypeList::DOUBLE_V>) {
                return "Double";
            } else if constexpr (std::is_same_v<T, ValueTypeList::BOOL_V>) {
                return "Bool";
            } else if constexpr (std::is_same_v<T, ValueTypeList::OBJECT_V>) {
                return "Object(" + arg->get_name() + ")";
            } else if constexpr (std::is_same_v<T, ValueTypeList::STR_V>) {
                return "Str";
            } else if constexpr (std::is_same_v<T, ValueTypeList::FUNCTION_V>) {
                if (arg) return "Function(" + arg->name + ")";
                else return "Function(invalid)";
            }

        }, data);
    }

    static Value apply_binary(
        const Value& left, const TokenType& op, const Value& right) {
            switch (op){
                case TokenType::OP_PLUS: return left + right;
                case TokenType::OP_MINUS: return left - right;
                case TokenType::OP_MUL: return left * right;
                case TokenType::OP_DIV: return left / right;
                default:
                    break;
            }
        return;
    }

    friend std::ostream& operator<<(std::ostream& os, const Value& val);
    friend Value operator+(const Value& v1, const Value& v2);
    friend Value operator-(const Value& v1, const Value& v2);
    friend Value operator/(const Value& v1, const Value& v2);
    friend Value operator*(const Value& v1, const Value& v2);
};


std::ostream& operator<<(std::ostream& os, const Value& val) {
    std::visit([&os](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        
        if constexpr (std::is_same_v<T, ValueTypeList::NULL_V>) {
            os << "null";
        } else if constexpr (std::is_same_v<T, ValueTypeList::INT_V>) {
            os << arg;
        } else if constexpr (std::is_same_v<T, ValueTypeList::DOUBLE_V>) {
            os << arg;
        } else if constexpr (std::is_same_v<T, ValueTypeList::BOOL_V>) {
            os << (arg ? "true" : "false");
        } else if constexpr (std::is_same_v<T, ValueTypeList::STR_V>) {
            os << arg;
        } else if constexpr (std::is_same_v<T, ValueTypeList::OBJECT_V>) {
            os << "object(" + arg->get_name() + ")" ;
        } else if constexpr (std::is_same_v<T, ValueTypeList::FUNCTION_V>) {
            if (arg) os << "function(" << arg->name << ")";
            else os << "function(invalid)";
        } else {
            os << "unknown";
        }

    }, val.data);
    return os;
}

Value operator+(const Value& v1, const Value& v2) {
    return std::visit([&v1, &v2](auto&& a, auto&& b) -> Value {
        using T1 = std::decay_t<decltype(a)>;
        using T2 = std::decay_t<decltype(b)>;

        if constexpr (IsArithmetic<T1> && IsArithmetic<T2>) {
                return Value(a + b);

        } else if constexpr (std::is_same_v<T1, ValueTypeList::STR_V> && 
            std::is_same_v<T2, ValueTypeList::STR_V>) {
                return Value(a + b);

        } else {
            throw TypeError("Операция сложения запрещена над " + 
                    v1.type_to_string() + " и " + v2.type_to_string());
        }

    }, v1.data, v2.data);
}

Value operator-(const Value& v1, const Value& v2) {
    return std::visit([&v1, &v2](auto&& a, auto&& b) -> Value {
        using T1 = std::decay_t<decltype(a)>;
        using T2 = std::decay_t<decltype(b)>;

        if constexpr (IsArithmetic<T1> && IsArithmetic<T2>) {
                return Value(a - b);

        } else {
            throw TypeError("Операция вычитания запрещена над " + 
                    v1.type_to_string() + " и " + v2.type_to_string());
        }

    }, v1.data, v2.data);
}

Value operator/(const Value& v1, const Value& v2) {
    return std::visit([&v1, &v2](auto&& a, auto&& b) -> Value {
        using T1 = std::decay_t<decltype(a)>;
        using T2 = std::decay_t<decltype(b)>;

        if constexpr (IsArithmetic<T1> && IsArithmetic<T2>) {
                if (b == 0) throw TypeError("Деление на ноль запрещено");
                return Value(static_cast<ValueTypeList::DOUBLE_V>(a) / 
                    static_cast<ValueTypeList::DOUBLE_V>(b));

        } else {
            throw TypeError("Операция деления запрещена над " + 
                    v1.type_to_string() + " и " + v2.type_to_string());
        }

    }, v1.data, v2.data);
}

Value operator*(const Value& v1, const Value& v2) {
    return std::visit([&v1, &v2](auto&& a, auto&& b) -> Value {
        using T1 = std::decay_t<decltype(a)>;
        using T2 = std::decay_t<decltype(b)>;

        if constexpr (IsArithmetic<T1> && IsArithmetic<T2>) {
            return Value(a * b);

        } else {
            throw TypeError("Операция умножения запрещена над " + 
                    v1.type_to_string() + " и " + v2.type_to_string());
        }

    }, v1.data, v2.data);
}


#endif