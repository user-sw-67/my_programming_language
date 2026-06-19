#ifndef ERROR_MANAGER_HPP
#define ERROR_MANAGER_HPP

#include "source_manager.hpp"


class CompilerError : public std::exception {
protected:
    std::string message;
    SourceLocation loc;
    SourceManager& source_manager;
    std::string code;

public:
    CompilerError(const std::string& msg, const SourceLocation& loc,
        SourceManager& source_manager, const std::string& code);

    virtual ~CompilerError() = default;

    virtual const char* what() const noexcept override;

    virtual int get_line() const;

    virtual int get_column() const;

    virtual const std::string& get_code() const;

    virtual std::string to_string() const;
};


class PreparationError : public CompilerError {
public:
    PreparationError(const std::string& msg, const SourceLocation& loc,
        SourceManager& source_manager, const std::string& code);
};


struct ParseError : public std::runtime_error {
    ParseError() : std::runtime_error("") {}
};

// Система статус-кодов ошибок ATOM.
// Формат: ORIGIN_DDDD — 3-буквенный префикс подсистемы, '_',
// 4 цифры (1-я цифра — категория ошибки внутри подсистемы,
// последующие — порядковый номер в этой категории).
// Полное описание каждого кода см. в docs/error_codes.md.
namespace error_code{
    const std::string CODE_NULL = "ERR_0000";

    // ---- LEX — лексер (src/lexer/lexer.cpp) ----
    // Категория 1: недопустимые символы
    const std::string LEX_1001 = "LEX_1001"; // Неизвестный знак пунктуации
    const std::string LEX_1002 = "LEX_1002"; // Неизвестный символ
    // Категория 2: незакрытые литералы/комментарии
    const std::string LEX_2001 = "LEX_2001"; // Незакрытая строка
    const std::string LEX_2002 = "LEX_2002"; // Незакрытая строка в конце файла
    const std::string LEX_2003 = "LEX_2003"; // Незакрытый блочный комментарий в конце файла
    // Категория 3: числовые литералы
    const std::string LEX_3001 = "LEX_3001"; // Ожидалась цифра после точки
    const std::string LEX_3002 = "LEX_3002"; // Незаконченная дробная часть числа в конце файла
    // Категория 4: операторы
    const std::string LEX_4001 = "LEX_4001"; // Неизвестный оператор

    // ---- PAR — парсер (src/parser/parser.cpp) ----
    // Категория 1: расположение конструкций верхнего уровня / блоки
    const std::string PAR_1001 = "PAR_1001";
    const std::string PAR_1002 = "PAR_1002";
    const std::string PAR_1003 = "PAR_1003";
    const std::string PAR_1004 = "PAR_1004";
    const std::string PAR_1005 = "PAR_1005";
    const std::string PAR_1006 = "PAR_1006";
    const std::string PAR_1007 = "PAR_1007";
    // Категория 2: выражения
    const std::string PAR_2001 = "PAR_2001";
    const std::string PAR_2002 = "PAR_2002";
    const std::string PAR_2003 = "PAR_2003";
    const std::string PAR_2004 = "PAR_2004";
    const std::string PAR_2005 = "PAR_2005";
    const std::string PAR_2006 = "PAR_2006";
    const std::string PAR_2007 = "PAR_2007";
    // Категория 3: make/переменные
    const std::string PAR_3001 = "PAR_3001";
    const std::string PAR_3002 = "PAR_3002";
    const std::string PAR_3003 = "PAR_3003";
    const std::string PAR_3004 = "PAR_3004";
    const std::string PAR_3005 = "PAR_3005";
    // Категория 4: функции и параметры
    const std::string PAR_4001 = "PAR_4001";
    const std::string PAR_4002 = "PAR_4002";
    const std::string PAR_4003 = "PAR_4003";
    const std::string PAR_4004 = "PAR_4004";
    const std::string PAR_4005 = "PAR_4005";
    const std::string PAR_4006 = "PAR_4006";
    const std::string PAR_4007 = "PAR_4007";
    const std::string PAR_4008 = "PAR_4008";
    const std::string PAR_4009 = "PAR_4009";
    const std::string PAR_4010 = "PAR_4010";
    const std::string PAR_4011 = "PAR_4011";
    const std::string PAR_4012 = "PAR_4012";
    const std::string PAR_4013 = "PAR_4013";
    // Категория 5: управляющие конструкции (if/while/do/for/return/throw/try/break/continue)
    const std::string PAR_5001 = "PAR_5001";
    const std::string PAR_5002 = "PAR_5002";
    const std::string PAR_5003 = "PAR_5003";
    const std::string PAR_5004 = "PAR_5004";
    const std::string PAR_5005 = "PAR_5005";
    const std::string PAR_5006 = "PAR_5006";
    const std::string PAR_5007 = "PAR_5007";
    const std::string PAR_5008 = "PAR_5008";
    const std::string PAR_5009 = "PAR_5009";
    const std::string PAR_5010 = "PAR_5010";
    const std::string PAR_5011 = "PAR_5011";
    const std::string PAR_5012 = "PAR_5012";
    const std::string PAR_5013 = "PAR_5013";
    const std::string PAR_5014 = "PAR_5014";
    const std::string PAR_5015 = "PAR_5015";
    const std::string PAR_5016 = "PAR_5016";
    const std::string PAR_5017 = "PAR_5017";
    // Категория 6: use/импорт
    const std::string PAR_6001 = "PAR_6001";
    const std::string PAR_6002 = "PAR_6002";
    const std::string PAR_6003 = "PAR_6003";
    const std::string PAR_6004 = "PAR_6004";
    const std::string PAR_6005 = "PAR_6005";
    const std::string PAR_6006 = "PAR_6006";
    const std::string PAR_6007 = "PAR_6007";
    const std::string PAR_6008 = "PAR_6008";
    const std::string PAR_6009 = "PAR_6009";
    // Категория 7: class
    const std::string PAR_7001 = "PAR_7001";
    const std::string PAR_7002 = "PAR_7002";
    const std::string PAR_7003 = "PAR_7003";
    const std::string PAR_7004 = "PAR_7004";
    // Категория 8: match
    const std::string PAR_8001 = "PAR_8001";
    const std::string PAR_8002 = "PAR_8002";
    const std::string PAR_8003 = "PAR_8003";
    const std::string PAR_8004 = "PAR_8004";
    const std::string PAR_8005 = "PAR_8005";
    const std::string PAR_8006 = "PAR_8006";
    const std::string PAR_8007 = "PAR_8007";
    const std::string PAR_8008 = "PAR_8008";
    const std::string PAR_8009 = "PAR_8009";
    // Категория 9: test/assert
    const std::string PAR_9001 = "PAR_9001";
    const std::string PAR_9002 = "PAR_9002";

    // ---- SEM — семантический анализ ----
    // Формат SEM_PTSS: P — номер прохода (1=DefinitionVisitor,
    // 2=AnalysisVisitor, 3=OptimizationVisitor), T — категория, SS — номер.

    // Проход 1 (DefinitionVisitor + SemanticsManager): категория 1 — use/импорт
    const std::string SEM_1101 = "SEM_1101";
    const std::string SEM_1102 = "SEM_1102";
    const std::string SEM_1103 = "SEM_1103";
    const std::string SEM_1104 = "SEM_1104";
    const std::string SEM_1105 = "SEM_1105";
    const std::string SEM_1106 = "SEM_1106";
    // Проход 1: категория 2 — классы
    const std::string SEM_1201 = "SEM_1201";
    const std::string SEM_1202 = "SEM_1202";
    const std::string SEM_1203 = "SEM_1203";
    const std::string SEM_1204 = "SEM_1204";
    const std::string SEM_1205 = "SEM_1205";
    const std::string SEM_1206 = "SEM_1206";
    const std::string SEM_1207 = "SEM_1207";
    const std::string SEM_1208 = "SEM_1208";
    const std::string SEM_1209 = "SEM_1209";
    const std::string SEM_1210 = "SEM_1210";
    const std::string SEM_1211 = "SEM_1211";
    // Проход 1: категория 3 — повторное определение идентификатора
    const std::string SEM_1301 = "SEM_1301";
    const std::string SEM_1302 = "SEM_1302";
    const std::string SEM_1303 = "SEM_1303";
    const std::string SEM_1304 = "SEM_1304";
    // Проход 1: категория 5 — точка входа (main)
    const std::string SEM_1501 = "SEM_1501";
    const std::string SEM_1502 = "SEM_1502";
    const std::string SEM_1503 = "SEM_1503";

    // Проход 2 (AnalysisVisitor): категория 1 — типы
    const std::string SEM_2101 = "SEM_2101";
    const std::string SEM_2102 = "SEM_2102";
    const std::string SEM_2103 = "SEM_2103";
    const std::string SEM_2104 = "SEM_2104";
    const std::string SEM_2105 = "SEM_2105";
    const std::string SEM_2106 = "SEM_2106";
    const std::string SEM_2107 = "SEM_2107";
    const std::string SEM_2108 = "SEM_2108";
    // Проход 2: категория 2 — идентификаторы
    const std::string SEM_2201 = "SEM_2201";
    const std::string SEM_2202 = "SEM_2202";
    const std::string SEM_2203 = "SEM_2203";
    const std::string SEM_2204 = "SEM_2204";
    const std::string SEM_2205 = "SEM_2205";
    const std::string SEM_2206 = "SEM_2206";
    // Проход 2: категория 3 — присваивание
    const std::string SEM_2301 = "SEM_2301";
    const std::string SEM_2302 = "SEM_2302";
    const std::string SEM_2303 = "SEM_2303";
    // Проход 2: категория 4 — поток управления
    const std::string SEM_2401 = "SEM_2401";
    const std::string SEM_2402 = "SEM_2402";
    const std::string SEM_2403 = "SEM_2403";
    const std::string SEM_2404 = "SEM_2404";
    const std::string SEM_2405 = "SEM_2405";
    const std::string SEM_2406 = "SEM_2406";
    const std::string SEM_2407 = "SEM_2407";
    const std::string SEM_2408 = "SEM_2408";
    // Проход 2: категория 5 — переменные функций/вызовы
    const std::string SEM_2501 = "SEM_2501";
    const std::string SEM_2502 = "SEM_2502";
    const std::string SEM_2503 = "SEM_2503";
    const std::string SEM_2504 = "SEM_2504";
    // Проход 2: категория 7 — match
    const std::string SEM_2701 = "SEM_2701";
    const std::string SEM_2702 = "SEM_2702";

    // Проход 3 (OptimizationVisitor): категория 1 — константные выражения
    const std::string SEM_3101 = "SEM_3101";
    const std::string SEM_3102 = "SEM_3102";
    const std::string SEM_3103 = "SEM_3103";
    const std::string SEM_3104 = "SEM_3104";
    const std::string SEM_3105 = "SEM_3105";

    // ---- RUN — интерпретатор/время выполнения (src/semantics/value.cpp, builds_manager.cpp) ----
    // Категория 1: бинарные/унарные операции над Value (value.cpp)
    const std::string RUN_1001 = "RUN_1001";
    const std::string RUN_1002 = "RUN_1002";
    const std::string RUN_1003 = "RUN_1003";
    const std::string RUN_1004 = "RUN_1004";
    const std::string RUN_1005 = "RUN_1005";
    const std::string RUN_1006 = "RUN_1006";
    const std::string RUN_1007 = "RUN_1007";
    const std::string RUN_1008 = "RUN_1008";
    const std::string RUN_1009 = "RUN_1009";
    const std::string RUN_1010 = "RUN_1010";
    const std::string RUN_1011 = "RUN_1011";
    const std::string RUN_1012 = "RUN_1012";
    const std::string RUN_1013 = "RUN_1013";
    const std::string RUN_1014 = "RUN_1014";
    // Категория 2: общие встроенные функции/модули (builds_manager.cpp)
    const std::string RUN_2001 = "RUN_2001";
    const std::string RUN_2002 = "RUN_2002";
    const std::string RUN_2003 = "RUN_2003";
    const std::string RUN_2004 = "RUN_2004";
    const std::string RUN_2005 = "RUN_2005";
    // Категория 3: встроенный класс Array
    const std::string RUN_3001 = "RUN_3001";
    const std::string RUN_3002 = "RUN_3002";
    const std::string RUN_3003 = "RUN_3003";
    const std::string RUN_3004 = "RUN_3004";
    const std::string RUN_3005 = "RUN_3005";
    const std::string RUN_3006 = "RUN_3006";
    const std::string RUN_3007 = "RUN_3007";
    const std::string RUN_3008 = "RUN_3008";
    const std::string RUN_3009 = "RUN_3009";
    const std::string RUN_3010 = "RUN_3010";
    const std::string RUN_3011 = "RUN_3011";
    const std::string RUN_3012 = "RUN_3012";
    const std::string RUN_3013 = "RUN_3013";
    const std::string RUN_3014 = "RUN_3014";
    const std::string RUN_3015 = "RUN_3015";
    const std::string RUN_3016 = "RUN_3016";
    const std::string RUN_3017 = "RUN_3017";
    const std::string RUN_3018 = "RUN_3018";
    const std::string RUN_3019 = "RUN_3019";
    const std::string RUN_3020 = "RUN_3020";
    const std::string RUN_3021 = "RUN_3021";
    // Категория 4: primitive_cast
    const std::string RUN_4001 = "RUN_4001";
    const std::string RUN_4002 = "RUN_4002";
    const std::string RUN_4003 = "RUN_4003";
    const std::string RUN_4004 = "RUN_4004";
    const std::string RUN_4005 = "RUN_4005";
    const std::string RUN_4006 = "RUN_4006";
    const std::string RUN_4007 = "RUN_4007";
    const std::string RUN_4008 = "RUN_4008";
    const std::string RUN_4009 = "RUN_4009";

    // ---- PRE — подготовка запуска: загрузка файлов (src/addition/source_manager.cpp) ----
    const std::string PRE_0001 = "PRE_0001"; // Файл не существует
    const std::string PRE_0002 = "PRE_0002"; // Расширение файла должно быть .atm
    const std::string PRE_0003 = "PRE_0003"; // Файл не удалось прочитать

    // ---- CFG — обработка флагов командной строки (src/addition/program_manager.cpp) ----
    const std::string CFG_0001 = "CFG_0001"; // Не указан путь после -dir/--directory
    const std::string CFG_0002 = "CFG_0002"; // Не указан флаг -dir/--directory
    const std::string CFG_0003 = "CFG_0003"; // Не указан файл с исходным кодом
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
    std::string code;
public:
    RuntimeError(const std::string& msg,
        const std::string& code = error_code::CODE_NULL);

    const char* what() const noexcept override;

    const std::string& get_code() const;
};


class TypeError : public RuntimeError {
public:
    TypeError(const std::string& msg,
        const std::string& code = error_code::CODE_NULL);
};

#endif