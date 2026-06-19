#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <string>
#include <variant>
#include <functional>
#include <unordered_map>
#include <memory>


class FunctionNodeAST;
class Value;
class Scope;


enum class SymbolType : uint8_t{
    VARIABLE,
    FUNCTION,
    CLASS,
    TEST
};


struct SymbolInfo{
    std::string name;
    std::string type_name;
    std::string parent_name;
    std::function<Value(const std::vector<Value>&)> built_in_func = nullptr;
    std::string access_modifier = "public";
    std::string defined_in_file;

    std::shared_ptr<Scope> class_scope = nullptr;
    std::shared_ptr<Scope> test_scope = nullptr;

    size_t slot_index = 0;
    FunctionNodeAST* body_ast = nullptr;
    
    SymbolType type;
    uint8_t count_args;
    uint8_t count_elem_default;

    bool is_built_in : 1 = false;
    bool is_std : 1 = false;
    bool is_ellipsis_args : 1 = false;
    bool is_const : 1 = false;
    bool is_init : 1 = false;
    bool is_has_parent : 1 = false;
    bool in_class : 1 = false;
    bool is_static : 1 = false;
    bool is_test : 1 = false;
    bool is_iter_obj : 1 = false;
};


struct Scope{
    std::unordered_map<std::string, std::shared_ptr<SymbolInfo>> symbols;
    std::weak_ptr<Scope> parent;
    size_t next_slot = 0;

    Scope(std::shared_ptr<Scope> parent_ptr);
};


class SymbolTable{
private:
    std::shared_ptr<Scope> current_scope;
    std::shared_ptr<Scope> global_scope;
    size_t max_slots_in_function = 0;
    std::string current_defined_in_file;
    
    std::vector<std::shared_ptr<Scope>> scope_stack;
    SymbolInfo* current_class = nullptr;
    SymbolInfo* current_function = nullptr;
public:
    SymbolTable(std::shared_ptr<Scope> std_lib, 
        const std::string& current_defined_in_file);

    SymbolTable(std::shared_ptr<Scope> existing_global_scope, 
        const std::string& current_defined_in_file, bool);

    std::shared_ptr<Scope> get_current_scope() const;
    std::shared_ptr<Scope> get_global_scope() const;

    void import_symbol(const std::string& name, 
        std::shared_ptr<SymbolInfo> symbol);

    void enter_scope();

    void enter_function_scope();

    void exit_scope();

    SymbolInfo* lookup(const std::string& name) const;

    SymbolInfo* lookup_local(const std::string& name) const;

    SymbolInfo* define(const std::string& name, SymbolType type);

    SymbolInfo* define_variable(const std::string& name, 
        const std::string& type_name, bool is_const = false, 
            bool is_init = false);

    SymbolInfo* define_function(const std::string& name, uint8_t count_args = 0,
        bool is_ellipsis_args = false, FunctionNodeAST* body_ast = nullptr);

    SymbolInfo* define_class(const std::string& name, 
        std::shared_ptr<Scope> class_scope = nullptr, 
            bool is_has_parent = false, const std::string& parent_name = "");

    SymbolInfo* define_test(const std::string& name, 
        std::shared_ptr<Scope> test_scope = nullptr);

    size_t get_current_slots_count() const;

    void enter_existing_scope(std::shared_ptr<Scope> existing_scope);
    void exit_existing_scope();

    void set_current_class(SymbolInfo* cls);
    SymbolInfo* get_current_class() const;

    void set_current_function(SymbolInfo* func);
    SymbolInfo* get_current_function() const;
};

#endif