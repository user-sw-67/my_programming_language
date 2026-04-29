#ifndef ERROR_MANAGER
#define ERROR_MANAGER

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "../ast.hpp"

enum class Severity {
    NOTE, 
    WARNING,
    ERROR
};


struct Error{
    Severity lvl;
    SourceLocation location;
    std::string msg;
    std::string code;
};


class ErrorManager{
private:
    size_t count_errors = 0;
    std::vector<Error> errors;

    void format_error(const Error& err, const std::string& source) const {
        std::cout << static_cast<int>(err.lvl) << "  " << 
            err.msg << " в " << err.location.line 
                << ":" << err.location.column << " " << err.code;
    }

public:
    void add(const std::string& msg, 
        SourceLocation loc, Severity sev = Severity::ERROR) {
            errors.push_back({sev, loc, msg, "ERR_007"});
            if (sev == Severity::ERROR) ++count_errors;
    }

    bool ok() const {
        return count_errors == 0;
    }

    void printAll(const std::string& source_code) const {
        for(const auto& err : errors) {
            format_error(err, source_code);
        }
    }
};

#endif