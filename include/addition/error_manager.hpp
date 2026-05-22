#ifndef ERROR_MANAGER_HPP
#define ERROR_MANAGER_HPP

#include "source_manager.hpp"


class CompilerError : public std::exception {
protected:
    std::string message;
    SourceLocation loc;
    SourceManager& source_manager;
    
public:
    CompilerError(const std::string& msg, const SourceLocation& loc,
        SourceManager& source_manager);
    
    virtual ~CompilerError() = default;
    
    virtual const char* what() const noexcept override;
    
    virtual int get_line() const;

    virtual int get_column() const;
    
    virtual std::string to_string() const;
};


class PreparationError : public CompilerError {
public:
    PreparationError(const std::string& msg, const SourceLocation& loc, 
        SourceManager& source_manager);
};


class LexerError : public CompilerError {
public:
    LexerError(const std::string& msg, const SourceLocation& loc,
        SourceManager& source_manager);
};


class ParserError : public CompilerError {
public:
    ParserError(const std::string& msg, const SourceLocation& loc,
        SourceManager& source_manager);
};


namespace error_code{
    const std::string CODE_NULL = "ERR_000";

    const std::string SEM_ONE_001 = "SEM_ONE_001";

    const std::string SEM_TWO_001 = "SEM_TWO_001";

    const std::string SEM_THREE_001 = "SEM_THREE_001";
}


enum class Severity {
    NOTE, 
    WARNING,
    ERROR
};


struct Error {
    Severity lvl;
    SourceLocation location;
    std::string msg;
    std::string code;
};


class ErrorManager{
private:
    size_t count_errors = 0;
    std::vector<Error> errors;

    void format_error(const Error& err, 
        const SourceManager& source_manager) const;

public:
    void add(const std::string& msg, const SourceLocation& loc, 
        const Severity& sev = Severity::ERROR, 
            const std::string& code_error = error_code::CODE_NULL);

    bool ok() const;

    void printAll(const SourceManager& source_manager) const;

};


class RuntimeError : std::exception {
private:
    std::string msg;
public:
    RuntimeError(const std::string& msg);
    
    const char* what() const noexcept override;
};


class TypeError : public RuntimeError {
public:
    TypeError(const std::string& msg);
};

#endif