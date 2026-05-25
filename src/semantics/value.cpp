#include "../../include/semantics/value.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/lexer/token_list.hpp"
#include "../../include/semantics/symbol_table.hpp"


Object::Object(std::shared_ptr<SymbolInfo> definition) : 
    class_definition(definition) {}

std::string Object::get_name() const {
    return class_definition->name;
}

ArrayObject::ArrayObject(
    std::shared_ptr<SymbolInfo> definition) : Object(definition) {}

Value::Value() : data(ValueTypeList::NULL_V{}) {}

Value::Value(ValueTypeList::INT_V data) : data(data) {}

Value::Value(ValueTypeList::DOUBLE_V data) : data(data) {}

Value::Value(ValueTypeList::BOOL_V data) : data(data) {}

Value::Value(ValueTypeList::STR_V data) : data(data) {}

Value::Value(const ValueTypeList::OBJECT_V& data) : data(data) {}

Value::Value(const ValueTypeList::FUNCTION_V& data) : data(data) {}

ValueTypeList::INT_V Value::as_int() const {
    return std::get<ValueTypeList::INT_V>(data);
}

ValueTypeList::DOUBLE_V Value::as_double() const {
    return std::get<ValueTypeList::DOUBLE_V>(data);
}

ValueTypeList::BOOL_V Value::as_bool() const {
    return std::get<ValueTypeList::BOOL_V>(data);
}

ValueTypeList::STR_V Value::as_str() const {
    return std::get<ValueTypeList::STR_V>(data);
}

ValueTypeList::OBJECT_V Value::as_object() const {
    return std::get<ValueTypeList::OBJECT_V>(data);
}

ValueTypeList::FUNCTION_V Value::as_function() const {
    return std::get<ValueTypeList::FUNCTION_V>(data);
}

bool Value::is_null() const {
    return std::holds_alternative<ValueTypeList::NULL_V>(data);
}

bool Value::is_int() const {
    return std::holds_alternative<ValueTypeList::INT_V>(data);
}

bool Value::is_double() const {
    return std::holds_alternative<ValueTypeList::DOUBLE_V>(data);
}

bool Value::is_bool() const {
    return std::holds_alternative<ValueTypeList::BOOL_V>(data);
}

bool Value::is_str() const {
    return std::holds_alternative<ValueTypeList::STR_V>(data);
}

bool Value::is_object() const {
    return std::holds_alternative<ValueTypeList::OBJECT_V>(data);
}

bool Value::is_function() const {
    return std::holds_alternative<ValueTypeList::FUNCTION_V>(data);
}

std::string Value::type_to_string() const {
    return std::visit([](auto&& arg) -> std::string {
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

Value Value::apply_binary(
    const Value& left, const TokenType& op, const Value& right) {
        switch (op){
            case TokenType::OP_PLUS: return left + right;
            case TokenType::OP_MINUS: return left - right;
            case TokenType::OP_MUL: return left * right;
            case TokenType::OP_DIV: return left / right;
            default: break;
        }
    return Value();
}

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

std::istream& operator>>(std::istream& is, Value& val){
    std::string line;
    if (std::getline(is, line)) {
        val.data = ValueTypeList::STR_V{line};
    }
    return is;
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

