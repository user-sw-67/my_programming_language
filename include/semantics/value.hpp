#ifndef VALUE_HPP
#define VALUE_HPP

#include <variant>
#include <string>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <vector>
#include <ostream>


class SymbolInfo;
enum class TokenType;
class Value;
class SymbolInfo;


struct Object{
    std::shared_ptr<SymbolInfo> class_definition;
    std::unordered_map<std::string, Value> fields;

    Object(std::shared_ptr<SymbolInfo> definition);

    std::string get_name() const;

    virtual ~Object() noexcept = default;
};


class ArrayObject : public Object{
public:
    std::vector<Value> elements;

    ArrayObject(std::shared_ptr<SymbolInfo> definition);
};


namespace ValueTypeList{
    using NULL_V = std::monostate;
    using INT_V = int64_t;
    using DOUBLE_V = double;
    using BOOL_V = bool;
    using STR_V = std::string;
    using OBJECT_V = std::shared_ptr<Object>;

    template<typename Tag>
    struct SymbolRef{
        SymbolInfo* info = nullptr;

        bool operator==(const SymbolRef& other) const {
            return info == other.info;
        }
    };

    struct FunctionTag{};
    struct TypeTag{};

    using FUNCTION_V = SymbolRef<FunctionTag>;
    using TYPE_V = SymbolRef<TypeTag>;
}

template<typename T>
constexpr static bool IsNull = std::is_same_v<T, ValueTypeList::NULL_V>;

template<typename T>
constexpr static bool IsDouble = std::is_same_v<T, ValueTypeList::DOUBLE_V>;

template<typename T>
constexpr static bool IsInt = std::is_same_v<T, ValueTypeList::INT_V>;

template<typename T>
constexpr static bool IsBool = std::is_same_v<T, ValueTypeList::BOOL_V>;

template<typename T>
constexpr static bool IsStr = std::is_same_v<T, ValueTypeList::STR_V>;

template<typename T>
constexpr static bool IsObject = std::is_same_v<T, ValueTypeList::OBJECT_V>;

template<typename T>
constexpr static bool IsFunction = std::is_same_v<T, ValueTypeList::FUNCTION_V>;

template<typename T>
constexpr static bool IsType = std::is_same_v<T, ValueTypeList::TYPE_V>;

template<typename T>
constexpr static bool IsArithmetic = IsInt<T> || IsDouble<T> || IsBool<T>;


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
        ValueTypeList::TYPE_V
    > data;

public:
    explicit Value();
    explicit Value(ValueTypeList::INT_V data);
    explicit Value(ValueTypeList::DOUBLE_V data);
    explicit Value(ValueTypeList::BOOL_V data);
    explicit Value(ValueTypeList::STR_V data);
    explicit Value(const ValueTypeList::OBJECT_V& data);
    explicit Value(const ValueTypeList::FUNCTION_V& data);
    explicit Value(const ValueTypeList::TYPE_V& data);

    ValueTypeList::INT_V as_int() const;
    ValueTypeList::DOUBLE_V as_double() const;
    ValueTypeList::BOOL_V as_bool() const;
    ValueTypeList::STR_V as_str() const;
    ValueTypeList::OBJECT_V as_object() const;
    ValueTypeList::FUNCTION_V as_function() const;
    ValueTypeList::TYPE_V as_type() const;

    bool is_null() const;
    bool is_int() const;
    bool is_double() const;
    bool is_bool() const;
    bool is_str() const;
    bool is_object() const;
    bool is_function() const;
    bool is_type() const;

    std::string type_to_string() const;

    static Value apply_binary(
        const Value& left, const TokenType& op, const Value& right);

    friend std::ostream& operator<<(std::ostream& os, const Value& val);
    friend std::istream& operator>>(std::istream& is, Value& val);
    friend Value operator+(const Value& v1, const Value& v2);
    friend Value operator-(const Value& v1, const Value& v2);
    friend Value operator/(const Value& v1, const Value& v2);
    friend Value operator*(const Value& v1, const Value& v2);
    friend Value operator<(const Value& v1, const Value& v2);
    friend Value operator>(const Value& v1, const Value& v2);
    friend Value operator==(const Value& v1, const Value& v2);
    friend Value operator!=(const Value& v1, const Value& v2);
    friend Value operator<=(const Value& v1, const Value& v2);
    friend Value operator>=(const Value& v1, const Value& v2);
    friend Value operator!(const Value& v1);
    friend Value operator&&(const Value& v1, const Value& v2);
    friend Value operator||(const Value& v1, const Value& v2);
};


std::ostream& operator<<(std::ostream& os, const Value& val);
std::istream& operator>>(std::istream& is, Value& val);
Value operator+(const Value& v1, const Value& v2);
Value operator-(const Value& v1, const Value& v2);
Value operator/(const Value& v1, const Value& v2);
Value operator*(const Value& v1, const Value& v2);
Value operator<(const Value& v1, const Value& v2);
Value operator>(const Value& v1, const Value& v2);
Value operator==(const Value& v1, const Value& v2);
Value operator!=(const Value& v1, const Value& v2);
Value operator<=(const Value& v1, const Value& v2);
Value operator>=(const Value& v1, const Value& v2);
Value operator!(const Value& v1);
Value operator&&(const Value& v1, const Value& v2);
Value operator||(const Value& v1, const Value& v2);


#endif