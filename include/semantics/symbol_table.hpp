#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include "../builds/builds.hpp"

#include <string>
#include <variant>
#include <functional>
#include <unordered_map>
#include <memory>


class FunctionNodeAST;
class Value;
class Scope;


enum class SymbolType{
    VARIABLE,
    FUNCTION,
    CLASS,
};


struct SymbolInfo{
    std::string name;
    SymbolType type;
    bool is_built_in = false;

    std::string type_name;
    bool is_const = false;
    bool is_init = false;
    size_t slot_index = 0;

    int count_args;
    bool is_ellipsis_args = false;
    FunctionNodeAST* body_ast = nullptr;
    std::function<Value(const std::vector<Value>&)> built_in_func = nullptr;

    bool is_has_parent = false;
    std::string parent_name;
    std::shared_ptr<Scope> class_scope = nullptr;

    bool in_class = false;
    std::string access_modifier = "public";
    bool is_static = false;
    bool is_getter = false;
    bool is_setter = false;
};


struct Scope{
    std::unordered_map<std::string, std::shared_ptr<SymbolInfo>> symbols;
    std::shared_ptr<Scope> parent;
    size_t next_slot = 0;

    Scope(std::shared_ptr<Scope> parent_ptr);
};


class SymbolTable{
private:
    std::shared_ptr<Scope> current_scope;
    std::shared_ptr<Scope> global_scope;
    size_t max_slots_in_function = 0;
    
public:
    SymbolTable();

    std::shared_ptr<Scope> get_current_scope() const;
    std::shared_ptr<Scope> get_global_scope() const;

    void import_symbol(const std::string& name, 
        std::shared_ptr<SymbolInfo> symbol);

    bool init_builtins(const std::vector<BuiltinData>& objects);

    void enter_scope();

    void enter_function_scope();

    void exit_scope();

    SymbolInfo* lookup(const std::string& name) const;

    SymbolInfo* lookup_local(const std::string& name) const;

    SymbolInfo* define(const std::string& name, SymbolType type);

    SymbolInfo* define_variable(const std::string& name, 
        const std::string& type_name, bool is_const = false, 
            bool is_init = false);

    SymbolInfo* define_function(const std::string& name, int count_args = 0,
        bool is_ellipsis_args = false, FunctionNodeAST* body_ast = nullptr);

    SymbolInfo* define_class(const std::string& name, 
        std::shared_ptr<Scope> class_scope = nullptr, 
            bool is_has_parent = false, const std::string& parent_name = "");

    size_t get_current_slots_count() const;
};

#endif