#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

class LogosBuiltinFunc;
class LogosMethodImpl;
class LogosFuncImpl;
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
    BINARY_EXPR,
    INSTANCE,
    FUNC_CALL,
    VARIABLE,
    PARAM,
    CONSTANT,
    ARRAY,
    ARRAY_INDEX,
    FIELD,
    OBJECT,
    BUILTIN_FUNC,
    FUNC_IMPL,
    METHOD_IMPL,
    SELECTION,
};

struct LogosSymbol {
    LogosSymbolType type;

    union {
        LogosObject* object;
        LogosField* field;
        LogosBuiltinFunc* builtinFunc;
        LogosFuncImpl* funcImpl;
        LogosMethodImpl* methodImpl;
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

    LogosSymbol(const LogosSymbolType type, LogosObject* object) :
        type(type),
        object(object) {
    }

    LogosSymbol(const LogosSymbolType type, LogosField* field) :
        type(type),
        field(field) {
    }

    LogosSymbol(const LogosSymbolType type, LogosInstance* constructor) :
        type(type),
        instance(constructor) {
    }

    LogosSymbol(const LogosSymbolType type, LogosFuncCall* funcCall) :
        type(type),
        funcCall(funcCall) {
    }

    LogosSymbol(const LogosSymbolType type, LogosBuiltinFunc* builtinFunc) :
        type(type),
        builtinFunc(builtinFunc) {
    }

    LogosSymbol(const LogosSymbolType type, LogosFuncImpl* funcImpl) :
        type(type),
        funcImpl(funcImpl) {
    }

    LogosSymbol(const LogosSymbolType type, LogosMethodImpl* methodImpl) :
        type(type),
        methodImpl(methodImpl) {
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
