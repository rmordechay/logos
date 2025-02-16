#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

class LogosSelection;
class LogosBinaryExpr;
class LogosConstant;
class LogosVariable;
class LogosFuncCall;
class LogosConstructor;
class LogosFunc;
class LogosField;
class LogosObject;

enum LogosSymbolType {
    FIELD,
    BINARY_EXPR,
    CONSTRUCTOR,
    FUNC_CALL,
    VARIABLE,
    CONSTANT,
    OBJECT,
    FUNC,
    SELECTION,
};

struct LogosSymbol {
    LogosSymbolType type;

    union {
        LogosObject* object;
        LogosField* field;
        LogosFunc* func;
        LogosConstructor* constructor;
        LogosFuncCall* funcCall;
        LogosVariable* variable;
        LogosConstant* constant;
        LogosBinaryExpr* binaryExpr;
        LogosSelection* selection;
    };

    LogosSymbol() :
        type(static_cast<LogosSymbolType>(0)),
        object(nullptr) {
    }

    LogosSymbol(LogosSymbolType type, LogosObject* object) :
        type(type),
        object(object) {
    }

    LogosSymbol(LogosSymbolType type, LogosField* field) :
        type(type),
        field(field) {
    }

    LogosSymbol(LogosSymbolType type, LogosFunc* func) :
        type(type),
        func(func) {
    }

    LogosSymbol(const LogosSymbolType type, LogosConstructor* constructor) :
        type(type),
        constructor(constructor) {
    }

    LogosSymbol(const LogosSymbolType type, LogosFuncCall* funcCall) :
        type(type),
        funcCall(funcCall) {
    }

    LogosSymbol(const LogosSymbolType type, LogosVariable* variable) :
        type(type),
        variable(variable) {
    }

    LogosSymbol(const LogosSymbolType type, LogosConstant* constant) :
        type(type),
        constant(constant) {
    }

    LogosSymbol(LogosSymbolType type, LogosSelection* selection) :
        type(type),
        selection(selection) {
    }

    LogosSymbol(LogosSymbolType type, LogosBinaryExpr* binaryExpr) :
        type(type),
        binaryExpr(binaryExpr) {
    }
};

#endif //LOGOSSYMBOL_H
