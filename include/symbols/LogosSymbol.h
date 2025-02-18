#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

class LogosExpr;
class LogosArrayIndex;
class LogosArray;
class LogosSelection;
class LogosBinaryExpr;
class LogosConstant;
class LogosVariable;
class LogosFuncCall;
class LogosInstance;
class LogosFunc;
class LogosField;
class LogosObject;

enum LogosSymbolType {
    FIELD,
    BINARY_EXPR,
    INSTANCE,
    OBJECT,
    FUNC_CALL,
    VARIABLE,
    CONSTANT,
    FUNC,
    SELECTION,
    ARRAY,
    ARRAY_INDEX,
};

struct LogosSymbol {
    LogosSymbolType type;

    union {
        LogosObject* object;
        LogosField* field;
        LogosFunc* func;
        LogosInstance* instance;
        LogosFuncCall* funcCall;
        LogosVariable* variable;
        LogosConstant* constant;
        LogosBinaryExpr* binaryExpr;
        LogosSelection* selection;
        LogosArray* array;
        LogosArrayIndex* arrayIndex;
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

    LogosSymbol(const LogosSymbolType type, LogosInstance* constructor) :
        type(type),
        instance(constructor) {
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

    LogosSymbol(const LogosSymbolType type, LogosSelection* selection) :
        type(type),
        selection(selection) {
    }

    LogosSymbol(const LogosSymbolType type, LogosBinaryExpr* binaryExpr) :
        type(type),
        binaryExpr(binaryExpr) {
    }

    LogosSymbol(const LogosSymbolType type, LogosArray* array) :
        type(type),
        array(array) {
    }

    LogosSymbol(const LogosSymbolType type, LogosArrayIndex* arrayIndex) :
        type(type),
        arrayIndex(arrayIndex) {
    }

    static LogosSymbol createSymbol(LogosExpr* expr);
};


#endif //LOGOSSYMBOL_H
