#ifndef MERMAID_VISITOR
#define MERMAID_VISITOR

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>
#include <vector>

#include "visitor.hpp"
#include "ast.hpp"

class MermaidVisitor : public Visitor {
private:
    std::ostream& out;
    int node_count = 0;
    std::stack<std::string> parent_stack;

    std::string next_id() { return "node_" + std::to_string(node_count++); }

    void add_node(const std::string& id, const std::string& label, const std::string& shape = "[]", const std::string& link_label = "") {
        std::string open = shape.substr(0, shape.size() / 2);
        std::string close = shape.substr(shape.size() / 2);
        out << "  " << id << open << "\"   " << label << "   \"" << close << "\n";
        if (!parent_stack.empty()) {
            std::string text = link_label.empty() ? "далее" : link_label;
            out << "  " << parent_stack.top() << " -- \" <font color='black'><b>" << text << "</b></font> \" ----> " << id << "\n";
        }
    }

    void visit_child(NodeAST& node, const std::string& current_id, const std::string& label) {
        parent_stack.push(current_id);
        node.visit(*this);
        parent_stack.pop();
    }

    std::string op_to_str(TokenType type) {
        switch (type) {
            case TokenType::OP_SAFE_NAV: return "🛡️ БЕЗОПАСНЫЙ ДОСТУП (?.)";
            case TokenType::OP_PIPE:     return "🌊 ПОТОК (|>)";
            case TokenType::OP_ELVIS:    return "👤 ЭЛВИС (?:)";
            case TokenType::OP_RANGE:    return "📏 ДИАПАЗОН (..)";
            case TokenType::OP_PLUS:  return "➕ СЛОЖИТЬ (+) ";
            case TokenType::OP_MINUS: return "➖ ВЫЧЕСТЬ (-) ";
            case TokenType::OP_MUL:   return "✖️ УМНОЖИТЬ (*) ";
            case TokenType::OP_DIV:   return "➗ РАЗДЕЛИТЬ (/) ";
            case TokenType::OP_INT_DIV: return "🎯 ЦЕЛОЕ ДЕЛ (//) ";
            case TokenType::OP_MOD:   return "🔢 ОСТАТОК (%) ";
            case TokenType::OP_POW:   return "⚡ СТЕПЕНЬ (^) ";
            case TokenType::OP_EQ:    return "⚖️ РАВНО (==) ";
            case TokenType::OP_NE:    return "🚫 НЕ РАВНО (!=) ";
            case TokenType::OP_LT:    return "📉 МЕНЬШЕ (<) ";
            case TokenType::OP_GT:    return "📈 БОЛЬШЕ (>) ";
            case TokenType::OP_LE:    return "📉 МЕНЬШЕ-РАВНО (<=) ";
            case TokenType::OP_GE:    return "📈 БОЛЬШЕ-РАВНО (>=) ";
            case TokenType::OP_AND:   return "🧠 ЛОГИЧ. И (&) ";
            case TokenType::OP_OR:    return "🧠 ЛОГИЧ. ИЛИ (|) ";
            case TokenType::OP_NOT:   return "❗ ОТРИЦАНИЕ (!) ";
            case TokenType::OP_ASSIGN: return "⬅️ ПРИСВОИТЬ (=) ";
            default: return "⚙️ ОПЕРАЦИЯ ";
        }
    }

public:
    MermaidVisitor(std::ostream& output = std::cout) : out(output) {}

    void start() {
        out << "%%{init: { 'theme': 'base', 'themeVariables': { 'primaryColor': '#ffffff', 'primaryTextColor': '#000000', 'lineColor': '#333333' }, 'graph': {'rankSep': 120, 'nodeSep': 100}} }%%\n";
        out << "graph TD\n";
        
        out << "  classDef root_style fill:#222,color:#fff,stroke:#000,stroke-width:4px;\n";
        out << "  classDef var_style fill:#bbdefb,color:#000,stroke:#1565c0,stroke-width:2px;\n";
        out << "  classDef op_style fill:#f3e5f5,color:#000,stroke:#7b1fa2,stroke-width:2px;\n";
        out << "  classDef logic_style fill:#fff9c4,color:#000,stroke:#fbc02d,stroke-width:2px;\n";
        out << "  classDef func_style fill:#c8e6c9,color:#000,stroke:#2e7d32,stroke-width:2px;\n";
        out << "  classDef test_style fill:#ffe0b2,color:#000,stroke:#fb8c00,stroke-width:2px;\n";
        out << "  classDef assert_style fill:#ffcdd2,color:#000,stroke:#e53935,stroke-width:2px;\n";
    }

    void visit(ProgramNode& node) override {
        std::string id = next_id();
        add_node(id, "🚀 КОРЕНЬ ПРОГРАММЫ", "(( ))");
        out << "  class " << id << " root_style\n";
        for (auto& stmt : node.statements) visit_child(*stmt, id, "инструкция");
    }

    void visit(BlockNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "📂 БЛОК КОДА { }", "[ ]");
        for (auto& stmt : node.statements) visit_child(*stmt, id, "строка");
    }

    void visit(ExpressionStatementNodeAST& node) override {
        if (node.expression) node.expression->visit(*this);
    }

    void visit(MakeNodeAST& node) override {
        std::string id = next_id();
        add_node(id, node.is_const ? "🔒 КОНСТАНТЫ (make)" : "📝 ПЕРЕМЕННЫЕ (make)", "{{ }}");
        out << "  class " << id << " var_style\n";
        parent_stack.push(id);
        for (size_t i = 0; i < node.names.size(); ++i) {
            std::string var_id = next_id();
            add_node(var_id, "ИМЯ: " + node.names[i] + "\nТип: " + node.type_names[i], "([ ])", "память");
            if (i < node.initializers.size()) {
                visit_child(*node.initializers[i], var_id, "значение");
            }
        }
        parent_stack.pop();
    }

    void visit(FunctionNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "🔨 ФУНКЦИЯ: " + node.name + "\nВернет: " + node.return_type, "(( ))");
        out << "  class " << id << " func_style\n";
        parent_stack.push(id);
        for (auto& param : node.parameters) {
            std::string p_id = next_id();
            std::string label = "АРГ: " + param.name + (param.is_variadic ? "..." : "") + " (" + param.type + ")";
            add_node(p_id, label, "([ ])", "сигнатура");
            if (param.default_value) visit_child(*param.default_value, p_id, "дефолт");
        }
        if (node.when_condition) visit_child(*node.when_condition, id, "условие_when");
        if (node.body) visit_child(*node.body, id, "код_внутри");
        parent_stack.pop();
    }

    void visit(ReturnNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "↩️ ВЕРНУТЬ (return)", "[/ /]");
        if (node.value) visit_child(*node.value, id, "результат");
    }

    void visit(IfElseNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "❓ ЕСЛИ (if)", "{ }");
        out << "  class " << id << " logic_style\n";
        visit_child(*node.condition, id, "условие");
        visit_child(*node.then_branch, id, "ветка_ТО");
        if (node.else_branch) visit_child(*node.else_branch, id, "ветка_ИНАЧЕ");
    }

    void visit(BinaryOperationNodeAST& node) override {
        std::string id = next_id();
        add_node(id, op_to_str(node.op), "[ ]");
        out << "  class " << id << " op_style\n";
        visit_child(*node.left, id, "лев");
        visit_child(*node.right, id, "прав");
    }

    void visit(UnaryOperationNodeAST& node) override {
        std::string id = next_id();
        add_node(id, op_to_str(node.op), "([ ])");
        out << "  class " << id << " op_style\n";
        visit_child(*node.operand, id, "аргумент");
    }

    void visit(TernaryOperationNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "⚖️ ТЕРНАРКА (?:)", "{ }");
        out << "  class " << id << " logic_style\n";
        visit_child(*node.condition, id, "если");
        visit_child(*node.true_branch, id, "то");
        visit_child(*node.false_branch, id, "иначе");
    }

    void visit(CallOperationNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "🚀 ВЫЗОВ: " + node.name + "()", "([ ])");
        out << "  class " << id << " func_style\n";
        for (auto& arg : node.args) visit_child(*arg, id, "арг");
    }

    void visit(LiteralNodeAST& node) override {
        add_node(next_id(), "💎 " + node.value, "[]");
    }

    void visit(IdentifierNodeAST& node) override {
        add_node(next_id(), "🔍 " + node.name, "([ ])");
    }

    void visit(WhileNodeAST& node) override {
        std::string id = next_id();
        std::string label = node.is_do_while ? "🔄 ЦИКЛ: do-while" : "🔄 ЦИКЛ: while";
        add_node(id, label, "{{ }}");
        out << "  class " << id << " logic_style\n";
        visit_child(*node.condition, id, "условие");
        if (node.body) visit_child(*node.body, id, "тело_цикла");
    }

    void visit(RangeOperationNodeAST& node) override {
        std::string id = next_id();
        std::string label = node.step ? "📏 ДИАПАЗОН (.. step)" : "📏 ДИАПАЗОН (..)";
        add_node(id, label, "{{ }}");
        out << "  class " << id << " op_style\n";
        if (node.start) {
            visit_child(*node.start, id, "от");
        }
        if (node.end) {
            visit_child(*node.end, id, "до");
        }
        if (node.step) {
            visit_child(*node.step, id, "шаг");
        }
    }

    void visit(ForNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "♻️ ЦИКЛ: for (" + node.name_var + ")", "{{ }}");
        out << "  class " << id << " logic_style\n";
        if (node.iterable) {
            visit_child(*node.iterable, id, "внутри");
        }
        if (node.body) {
            visit_child(*node.body, id, "тело_цикла");
        }
    }

    void visit(BreakNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "🛑 ПРЕРВАТЬ (break)", "[[ ]]");
    }

    void visit(ContinueNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "⏭️ ПРОДОЛЖИТЬ (continue)", "[[ ]]");
    }

    void visit(TryNodeAST& node) override {
        std::string try_id = next_id();
        add_node(try_id, "🛡️ ПОПРОБОВАТЬ (try)", "[ ]");
        if (node.try_block) {
            visit_child(*node.try_block, try_id, "попытка");
        }
        if (node.catch_block) {
            std::string catch_id = next_id();
            parent_stack.push(try_id);
            add_node(catch_id, "⚠️ ПОЙМАТЬ (catch)", "{ }", "ошибка");
            parent_stack.pop();

            if (node.catch_expr) visit_child(*node.catch_expr, catch_id, "аргумент");
            visit_child(*node.catch_block, catch_id, "обработка");
        }
        if (node.finally_block) {
            visit_child(*node.finally_block, try_id, "в любом случае");
        }
    }

    void visit(ThrowNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "💥 БРОСИТЬ (throw)", "[/ /]");
        if (node.value) {
            visit_child(*node.value, id, "объект_ошибки");
        }
    }

    void visit(UseNodeAST& node) override {
        std::string id = next_id();
        std::string clean_path = node.path_lib;
        clean_path.erase(std::remove(clean_path.begin(), clean_path.end(), '\"'), clean_path.end());
        std::string label = "📦 IMPORT: " + clean_path;
        if (!node.as_name.empty()) label += " as " + node.as_name;
        out << "  " << id << "[\"" << label << "\"]\n";
        out << "  class " << id << " func_style\n"; 
        for (const auto& obj : node.objects) {
            std::string obj_id = next_id();
            std::string obj_label = "🔹 " + obj.internal_name;
            if (!obj.alias.empty()) obj_label += " ➜ " + obj.alias;
            out << "  " << obj_id << "([\"" << obj_label << "\"])\n";
            out << "  " << id << " -- \" <font color='black'><b>объект</b></font> \" ----> " << obj_id << "\n";
        }
    }

    void visit(ClassNodeAST& node) override {
        std::string id = next_id();
        std::string label = "🏛️ КЛАСС: " + node.name;
        if (!node.base_class_name.empty()) {
            label += "\n(наследует " + node.base_class_name + ")";
        }
        add_node(id, label, "[[ ]]");
        out << "  class " << id << " root_style\n"; 
        parent_stack.push(id);
        for (auto& member : node.members) {
            std::string m_id = next_id();
            std::string m_label = "";
            if (member.access_modifier == "private") m_label += " private ";
            else if (member.access_modifier == "protected") m_label += " protected ";
            else m_label += " public ";
            if (member.is_static) m_label += "[static] ";
            auto* func = dynamic_cast<FunctionNodeAST*>(member.member_node.get());
            if (func) {
                m_label += "МЕТОД: " + func->name;
                if (member.is_getter) m_label += " «get»";
                if (member.is_setter) m_label += " «set»";
                add_node(m_id, m_label, "(( ))", "член_класса");
                out << "  class " << m_id << " func_style\n";
                visit_child(*func, m_id, "реализация");
            } 
            else {
                m_label += "ПОЛЕ";
                add_node(m_id, m_label, "([ ])", "член_класса");
                out << "  class " << m_id << " var_style\n";
                visit_child(*member.member_node, m_id, "определение");
            }
        }
        
        parent_stack.pop();
    }

    void visit(MatchNodeAST& node) override {
        std::string match_id = next_id();
        add_node(match_id, "🎯 MATCH", "{ }");
        out << "  class " << match_id << " logic_style\n";
        if (node.value) {
            visit_child(*node.value, match_id, "значение");
        }
        parent_stack.push(match_id);
        for (size_t i = 0; i < node.cases.size(); ++i) {
            auto& c = node.cases[i];
            std::string case_id = next_id();
            bool is_default = (c.value == nullptr);
            std::string label = is_default ? "⚙️ DEFAULT" : "📦 CASE #" + std::to_string(i + 1);
            add_node(case_id, label, is_default ? "[ ]" : "([ ])", "вариант");
            if (c.value) {
                visit_child(*c.value, case_id, "условие");
            }
            if (c.body) {
                visit_child(*c.body, case_id, "выполнить");
            }
        }
        parent_stack.pop();
    }

    void visit(TestNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "🧪 ТЕСТ: " + node.name, "{{ }}");
        out << "  class " << id << " test_style\n";
        if (node.body) {
            visit_child(*node.body, id, "проверка");
        }
    }

    void visit(AssertNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "✅ ASSERT", "[/ /]");
        out << "  class " << id << " assert_style\n";

        if (node.value) {
            visit_child(*node.value, id, "условие");
        }
    }

};

#endif