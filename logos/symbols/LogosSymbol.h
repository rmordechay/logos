#ifndef LOGOSSYMBOL_H
#define LOGOSSYMBOL_H

class LogosField;
class LogosFunc;
class LogosObject;
class LogosVarDec;

enum LogosSymbolType {
    FIELD,
    VAR_DEC,
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
    };
    LogosSymbol() : type(static_cast<LogosSymbolType>(0)), object(nullptr) {}
    LogosSymbol(const LogosSymbolType type, LogosObject* object) : type(type), object(object) {}
    LogosSymbol(const LogosSymbolType type, LogosField* field) : type(type), field(field) {}
    LogosSymbol(const LogosSymbolType type, LogosFunc* func) : type(type), func(func) {}
    LogosSymbol(const LogosSymbolType type, LogosVarDec* varDec) : type(type), varDec(varDec) {}
};

#endif //LOGOSSYMBOL_H
