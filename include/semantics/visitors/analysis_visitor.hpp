#ifndef ANALYSIS_VISITOR_HPP
#define ANALYSIS_VISITOR_HPP

#include "base.hpp"

#include <string>
#include <unordered_map>


class ExpressionNodeAST;
class StatementNodeAST;
class SymbolInfo;
struct SourceLocation;


class AnalysisVisitor : public BaseVisitorSemantics{
private:
    bool current_method_is_static = false;
    bool in_cycle = false;
    bool in_switch = false;
    bool in_test = false;

    std::unordered_map<ExpressionNodeAST*, std::string> type_cache;
    std::unordered_map<BinaryOperationNodeAST*, SymbolInfo*> member_cache;

    bool can_cast(const std::string& expected, const std::string& actual);

    std::string infer_type_expression(ExpressionNodeAST* node);
    std::string infer_binary_type(BinaryOperationNodeAST* node);
    std::string infer_member_type(BinaryOperationNodeAST* node);
    std::string infer_call_type(CallOperationNodeAST* node);
    bool try_get_range_element_type(ExpressionNodeAST* node, std::string& out);
    SymbolInfo* find_class_member(SymbolInfo* class_sym,
        const std::string& name, SymbolInfo** owner_out = nullptr);
    bool check_member_access(SymbolInfo* member, SymbolInfo* owner,
        const SourceLocation& loc);
    SymbolInfo* resolve_member_symbol(BinaryOperationNodeAST* node);
    void check_call(SymbolInfo* symbol, CallOperationNodeAST& node,
        const std::string& err);
    void check_condition_type(ExpressionNodeAST* node);
    static bool is_terminating_statement(StatementNodeAST* stmt);
    static bool always_returns(StatementNodeAST* stmt);

public:
    AnalysisVisitor(SymbolTable& table, Managers& managers);

    using BaseVisitorSemantics::visit;

    void visit(MakeNodeAST& node) override;
    void visit(LiteralNodeAST& node) override;
    void visit(IdentifierNodeAST& node) override;
    void visit(UnaryOperationNodeAST& node) override;
    void visit(BinaryOperationNodeAST& node) override;
    void visit(BlockNodeAST& node) override;
    void visit(IfElseNodeAST& node) override;
    void visit(TernaryOperationNodeAST& node) override;
    void visit(ExpressionStatementNodeAST& node) override;
    void visit(FunctionNodeAST& node) override;
    void visit(ReturnNodeAST& node) override;
    void visit(CallOperationNodeAST& node) override;
    void visit(WhileNodeAST& node) override;
    void visit(ForNodeAST& node) override;
    void visit(BreakNodeAST& node) override;
    void visit(ContinueNodeAST& node) override;
    void visit(ThrowNodeAST& node) override;
    void visit(TryNodeAST& node) override;
    void visit(UseNodeAST& node) override;
    void visit(ClassNodeAST& node) override;
    void visit(MatchNodeAST& node) override;
    void visit(TestNodeAST& node) override;
    void visit(AssertNodeAST& node) override;
    void visit(RangeOperationNodeAST& node) override;
};


#endif