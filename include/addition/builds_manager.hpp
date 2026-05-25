#ifndef BUILDS_MANAGER_HPP
#define BUILDS_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <functional>


class Scope;
class BuildInModule;
class Value;


class BuildInClass{
private:
    std::string class_name;
    std::shared_ptr<Scope> class_scope;
    BuildInModule& parent_builder;

public:
    BuildInClass(const std::string& class_name, 
        BuildInModule& parent_builder, std::shared_ptr<Scope> scope);

    BuildInClass& add_method(const std::string& name, int count_args,
        bool is_ellipsis_args, const std::string& ret_type, 
            std::function<Value(const std::vector<Value>&)> func, 
                bool is_std = false);

    BuildInClass& add_field(const std::string& name, 
        const std::string& type, bool is_const, 
            bool is_init, bool is_std = false);

    BuildInModule& end_class();
};


class BuildInModule{
private:
    std::string module_name;
    std::shared_ptr<Scope> module_scope;

public:
    BuildInModule(const std::string& module_name, std::shared_ptr<Scope> scope);

    BuildInClass add_class(const std::string& name, bool is_std = false);

    BuildInModule& add_function(const std::string& name, int count_args,
        bool is_ellipsis_args, const std::string& ret_type, 
            std::function<Value(const std::vector<Value>&)> func, 
                bool is_std = false);

    BuildInModule& add_variable(const std::string& name, 
        const std::string& type, bool is_const, bool is_std = false);
};


class BuildInManager{
private:
    std::unordered_map<std::string, std::shared_ptr<Scope>> modules;
    std::unordered_map<std::string, std::function<void()>> all_standart_modules;

    void register_std();

    void register_math();

public:
    BuildInManager();

    BuildInModule create_module(const std::string& name);

    std::shared_ptr<Scope> get_standard_module(const std::string& name);

    bool is_module_standard(const std::string& name) const;
};

#endif