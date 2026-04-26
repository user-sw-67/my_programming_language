#ifndef MERMAID_VISITOR
#define MERMAID_VISITOR

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
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
    }

    // --- СТРУКТУРНЫЕ УЗЛЫ ---

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
        // Чтобы не плодить лишние узлы, сразу идем к выражению
        if (node.expression) node.expression->visit(*this);
    }

    // --- ПЕРЕМЕННЫЕ И ФУНКЦИИ ---

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
        // Параметры
        for (auto& param : node.parameters) {
            std::string p_id = next_id();
            std::string label = "АРГ: " + param.name + (param.is_variadic ? "..." : "") + " (" + param.type + ")";
            add_node(p_id, label, "([ ])", "сигнатура");
            if (param.default_value) visit_child(*param.default_value, p_id, "дефолт");
        }
        // Условие when
        if (node.when_condition) visit_child(*node.when_condition, id, "условие_when");
        // Тело
        if (node.body) visit_child(*node.body, id, "код_внутри");
        parent_stack.pop();
    }

    void visit(ReturnNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "↩️ ВЕРНУТЬ (return)", "[/ /]");
        if (node.value) visit_child(*node.value, id, "результат");
    }

    // --- ЛОГИКА ---

    void visit(IfElseNodeAST& node) override {
        std::string id = next_id();
        add_node(id, "❓ ЕСЛИ (if)", "{ }");
        out << "  class " << id << " logic_style\n";
        visit_child(*node.condition, id, "условие");
        visit_child(*node.then_branch, id, "ветка_ТО");
        if (node.else_branch) visit_child(*node.else_branch, id, "ветка_ИНАЧЕ");
    }

    // --- ВЫРАЖЕНИЯ И ОПЕРАЦИИ ---

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

    // --- ЛИТЕРАЛЫ И ИДЕНТИФИКАТОРЫ ---

    void visit(LiteralNodeAST& node) override {
        add_node(next_id(), "💎 " + node.value, "[]");
    }

    void visit(IdentifierNodeAST& node) override {
        add_node(next_id(), "🔍 " + node.name, "([ ])");
    }
};

#endif