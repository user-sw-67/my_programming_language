#include "../../include/semantics/visitors/definition_visitor.hpp"
#include "../../include/semantics/symbol_table.hpp"
#include "../../include/addition/error_manager.hpp"
#include "../../include/parser/ast.hpp"
#include "../../include/parser/parser.hpp"
#include "../../include/lexer/lexer.hpp"
#include "../semantics_manager.hpp"

#include "functional"


DefinitionVisitor::DefinitionVisitor(SymbolTable& table, 
    ErrorManager& error_manager, SourceManager& source_manager) : 
        BaseVisitorSemantics(table, error_manager), 
            source_manager(source_manager) {}

void DefinitionVisitor::visit(MakeNodeAST& node) {
    try{
        if(define_in_class){
            for(size_t i = 0; i < node.names.size(); ++i){
                SymbolInfo* symbol = table.define_variable(node.names[i], 
                    node.type_names[i], node.is_const, node.is_init());
                symbol->in_class = true;
                symbol->access_modifier = current_access_modifier;
                if(symbol->is_setter || symbol->is_getter){
                    std::string modif = symbol->is_setter ? "setter" : "getter";
                    error_manager.add("Перменная " + node.names[i] + 
                        " не может иметь модификатор " + modif, node.location, 
                            Severity::WARNING);
                }
                symbol->is_setter = false;
                symbol->is_getter = false;
                symbol->is_static = current_is_static;
            }
        }
    } catch(const RuntimeError& e) {
        error_manager.add(e.what(), node.location, Severity::ERROR);
    }
}

void DefinitionVisitor::visit(LiteralNodeAST& node) {}

void DefinitionVisitor::visit(IdentifierNodeAST& node) {}

void DefinitionVisitor::visit(UnaryOperationNodeAST& node) {}

void DefinitionVisitor::visit(BinaryOperationNodeAST& node) {}

void DefinitionVisitor::visit(BlockNodeAST& node) {}

void DefinitionVisitor::visit(IfElseNodeAST& node) {}

void DefinitionVisitor::visit(TernaryOperationNodeAST& node) {}

void DefinitionVisitor::visit(ExpressionStatementNodeAST& node) {}

void DefinitionVisitor::visit(FunctionNodeAST& node) {
    try{
        SymbolInfo* symbol = table.define_function(node.name, 
            node.get_cout_parameters(), node.is_variadic_parameters(), &node);
        if(define_in_class){
            symbol->in_class = true;
            symbol->access_modifier = current_access_modifier;
            symbol->is_setter = current_is_setter;
            symbol->is_getter = current_is_getter;
            symbol->is_static = current_is_static;
            if((symbol->is_setter || symbol->is_getter) && symbol->is_static){
                std::string modif = symbol->is_setter ? "setter" : "getter";
                error_manager.add("Метод " + node.name + 
                    " не может иметь модификаторы static и " + modif + 
                        " одновременно", node.location, Severity::WARNING);
                symbol->is_static = false;
            }
        }
    } catch(const RuntimeError& e) {
        error_manager.add(e.what(), node.location, Severity::ERROR);
    }
}

void DefinitionVisitor::visit(ReturnNodeAST& node) {}

void DefinitionVisitor::visit(CallOperationNodeAST& node) {}

void DefinitionVisitor::visit(WhileNodeAST& node) {}

void DefinitionVisitor::visit(ForNodeAST& node) {}

void DefinitionVisitor::visit(BreakNodeAST& node) {}

void DefinitionVisitor::visit(ContinueNodeAST& node) {}

void DefinitionVisitor::visit(ThrowNodeAST& node) {}

void DefinitionVisitor::visit(TryNodeAST& node) {}

void DefinitionVisitor::visit(UseNodeAST& node) {
    Module& mod = source_manager.modules[node.path_lib];

    if (mod.status == ModuleStatus::LOADING) {
        error_manager.add("Обнаружен циклический импорт с файлом " 
            + node.path_lib, node.location, Severity::ERROR);
        return;
    }

    if (mod.status == ModuleStatus::LOADED) {
        load_symbols(node, mod);
        return;
    }

    mod.status = ModuleStatus::LOADING;

    if(!mod.ast){
        Lexer lexer(mod.lines, node.path_lib, error_manager, source_manager);
        std::vector<Token> tokens = lexer.get_tokens();
        Parser parser(tokens, node.path_lib, 
            error_manager, source_manager);
        mod.ast = parser.parse();
    }

    if(!mod.scope){
        mod.scope = std::make_shared<Scope>(nullptr);
        SymbolTable new_table;
        if(!new_table.init_builtins(SemanticsManager::get_builtin_data())){
            error_manager.add(
                "Не удалось инициализировать встроенный функционал", 
                    {0, 0, node.path_lib}, Severity::ERROR);
        }
        DefinitionVisitor def_vis(new_table, error_manager, source_manager);
        mod.ast->accept(def_vis);
        mod.scope = new_table.get_global_scope();
    }
    mod.status = ModuleStatus::LOADED;
    load_symbols(node, mod);
}

void DefinitionVisitor::visit(ClassNodeAST& node) {
    try{
        if(node.has_base_class()){
            if (node.name == node.base_class_name) {
                error_manager.add("Класс " + node.name + 
                    " не может быть наследником самого себя", node.location, 
                        Severity::ERROR);
            }
            auto* base_info = table.lookup(node.base_class_name);
            if (!base_info || base_info->type != SymbolType::CLASS) {
                error_manager.add("Базовый класс " + 
                    node.base_class_name + " не найден для " +
                        node.name, node.location, Severity::ERROR);
            }
        }
        auto class_scope = get_class_scope(node);
        table.define_class(node.name, class_scope, 
            node.has_base_class(), node.base_class_name);

    } catch(const RuntimeError& e) {
        error_manager.add(e.what(), node.location, Severity::ERROR);
    }
}

void DefinitionVisitor::visit(MatchNodeAST& node) {}

void DefinitionVisitor::visit(TestNodeAST& node) {}

void DefinitionVisitor::visit(AssertNodeAST& node) {}

void DefinitionVisitor::visit(RangeOperationNodeAST& node) {}

std::shared_ptr<Scope> DefinitionVisitor::get_class_scope(ClassNodeAST& node) {
    table.enter_scope();

    auto class_scope = table.get_current_scope();
    define_in_class = true;

    for (auto& m : node.members){
        current_access_modifier = m.access_modifier;
        current_is_static = m.is_static;
        current_is_getter = m.is_getter;
        current_is_setter = m.is_setter;
        m.member_node->accept(*this);
    }

    define_in_class = false;

    current_access_modifier = "public";
    current_is_static = false;
    current_is_getter = false;
    current_is_setter = false;

    auto define_method = [this](const std::string& name){
        SymbolInfo* symbol = table.define(name, SymbolType::FUNCTION);
        symbol->is_built_in = true;
        symbol->in_class = true;
        symbol->count_args = 0;
        symbol->is_ellipsis_args = false;
        symbol->built_in_func = nullptr;
        return symbol;
    };

    SymbolInfo* new_ptr = table.lookup_local("new");
    if(!new_ptr){
        new_ptr = define_method("new");
    }

    SymbolInfo* del_ptr = table.lookup_local("delete");
    if(!del_ptr){
        del_ptr = define_method("delete");
    }
    if(del_ptr && del_ptr->count_args != 0){
        error_manager.add("Деструктор класса " + node.name + 
            " не должен иметь параметров", node.location, Severity::ERROR);
    }

    auto valid_method = [this, &node](
        const std::string& name_method, SymbolInfo* ptr){
            if(ptr->is_setter || ptr->is_getter || ptr->is_static){
                std::string modif = ptr->is_setter ? "setter" : 
                    (ptr->is_getter ? "getter" : "static");
                error_manager.add(name_method + " класса " + node.name + 
                    " не может иметь модификатор " + modif, node.location, 
                        Severity::WARNING);
                ptr->is_setter = false;
                ptr->is_getter = false;
                ptr->is_static = false;
            }
            if(ptr->access_modifier != "public"){
                error_manager.add(name_method + " класса " + node.name + 
                    " не может быть не public", node.location, 
                        Severity::WARNING);
                ptr->access_modifier = "public";
            }
    };
    valid_method("Конструктор", new_ptr);
    valid_method("Деструктор", del_ptr);

    table.exit_scope();
    return class_scope;
}

void DefinitionVisitor::load_symbols(UseNodeAST& node, Module& mod){
    try{
        if(node.is_full()){
            for (const auto& [name, symbol_ptr] : mod.scope->symbols){
                if (symbol_ptr->is_built_in) continue;
                table.import_symbol(name, symbol_ptr);
            }
        } else {
            for(const auto& obj : node.objects){
                auto it = mod.scope->symbols.find(obj.internal_name);
                if(it == mod.scope->symbols.end()){
                    error_manager.add("Идентификатор " + obj.internal_name + 
                        " не найден в модуле " + node.path_lib, 
                            obj.location, Severity::ERROR);
                    continue;
                }
                std::string final_name = obj.alias.empty() ? 
                    obj.internal_name : obj.alias;
                table.import_symbol(final_name, it->second);
            }
        }
    }catch(const RuntimeError& e) {
        error_manager.add(e.what(), node.location, Severity::ERROR);
    }
}