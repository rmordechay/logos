#ifndef SYMBOL_H
#define SYMBOL_H
#include "LogosType.h"


#include <string>

enum SymbolKind {
    FIELD,
    LOCAL_VARIABLE,
    FUNC_CALL,
    FUNC_DEFINITION,
    PARAM,
};

class LogosSymbol {
public:
    std::string name;
    SymbolKind kind;
    LogosType* logosType;

    explicit LogosSymbol(const std::string& name, const SymbolKind kind, LogosType* logosType):
        name(name),
        kind(kind),
        logosType(logosType) {
    }

    explicit LogosSymbol(const std::string& name, const SymbolKind kind) :
        LogosSymbol(name, kind, nullptr) {
    }

    explicit LogosSymbol(const SymbolKind kind, LogosType* logosType):
        LogosSymbol("", kind, logosType) {
    }

    explicit LogosSymbol(const SymbolKind kind):
        LogosSymbol("", kind, nullptr) {
    }
};


#endif //SYMBOL_H
