#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H
#include "exprs/LogosConstant.h"
#include "exprs/LogosConstructor.h"
#include "exprs/LogosFuncCall.h"
#include "exprs/LogosVariable.h"

class LogosFunc;
class LogosField;
class LogosObject;
class LogosVarDec;

enum LogosSymbolType {
    FIELD,
    VAR_DEC,
    BINARY_EXPR,
    CONSTRUCTOR,
    FUNC_CALL,
    VARIABLE,
    CONSTANT,
    OBJECT,
    FUNC,
};

struct LogosSymbol {
    LogosSymbolType type;

    union {
        LogosVarDec* varDec;
        LogosObject* object;
        LogosField* field;
        LogosFunc* func;
        LogosConstructor constructor;
        LogosFuncCall funcCall;
        LogosVariable variable;
        LogosConstant constant;
    };

    LogosSymbol() :
        type(static_cast<LogosSymbolType>(0)),
        object(nullptr) {
    }

    LogosSymbol(const LogosSymbolType type, LogosObject* object) :
        type(type),
        object(object) {
    }

    LogosSymbol(const LogosSymbolType type, LogosField* field) :
        type(type),
        field(field) {
    }

    LogosSymbol(const LogosSymbolType type, LogosFunc* func) :
        type(type),
        func(func) {
    }

    LogosSymbol(const LogosSymbolType type, LogosVarDec* varDec) :
        type(type),
        varDec(varDec) {
    }

    LogosSymbol(const LogosSymbolType type, LogosConstructor constructor) :
        type(type),
        constructor(constructor) {
    }

    LogosSymbol(const LogosSymbolType type, LogosFuncCall funcCall) :
        type(type),
        funcCall(funcCall) {
    }

    LogosSymbol(const LogosSymbolType type, LogosVariable variable) :
        type(type),
        variable(variable) {
    }

    LogosSymbol(const LogosSymbolType type, LogosConstant constant) :
        type(type),
        constant(constant) {
    }
};

#endif //LOGOSSYMBOL_H
