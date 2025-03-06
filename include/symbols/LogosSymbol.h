#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H


class LogosLoopVar;
class LogosBuiltinFunc;
class LogosVarDec;
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
    VAR_DEC,
    OBJECT,
    FIELD,
    BUILTIN_FUNC,
    FUNC_IMPL,
    METHOD_IMPL,
    SELECTION,
    LOOP_VAR,
};

struct LogosSymbol {
    LogosSymbolType type;
    union {
        LogosVarDec* varDec;
        LogosObject* object;
        LogosField* field;
        LogosLoopVar* loopVar;
        LogosBuiltinFunc* builtinFunc;
        LogosFuncImpl* funcImpl;
        LogosMethodImpl* methodImpl;
        LogosSelection* selection;
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

    LogosSymbol(const LogosSymbolType type, LogosLoopVar* loopVar) :
        type(type),
        loopVar(loopVar) {
    }

    LogosSymbol(const LogosSymbolType type, LogosSelection* selection) :
        type(type),
        selection(selection) {
    }

    LogosSymbol(const LogosSymbolType type, LogosVarDec* varDec) :
        type(type),
        varDec(varDec) {
    }
};


#endif //LOGOSSYMBOL_H
