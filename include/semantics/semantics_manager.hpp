#ifndef SEMANTICS_MANAGER_HPP
#define SEMANTICS_MANAGER_HPP

#include "symbol_table.hpp"

#include <string>
#include <memory>


class Managers;
class ProgramNode;


class SemanticsManager{
private:
    Managers& managers;
    std::string filename;
    std::unique_ptr<ProgramNode>& program;

    void validate_entry_point(std::shared_ptr<Scope> scope,
        const std::string& filename) const;

public:
    SemanticsManager(std::unique_ptr<ProgramNode>& program,
            const std::string& filename, Managers& managers);

    void run();

};

#endif