#ifndef SYMBOL_H
#define SYMBOL_H

#include "funcs/LogosFunc.h"

#include <string>

class LogosExpr;

enum SymbolKind {
    CONSTANT,
    LOCAL_VARIABLE,
    FUNC_CALL,
    FUNC_DEFINITION,
    PARAM,
};

union SymbolValue {
    LogosExpr *expr;
    LogosFunc *func;

    SymbolValue(): expr(nullptr) {}
    explicit SymbolValue(LogosExpr *expr): expr(expr) {}
    explicit SymbolValue(LogosFunc *func): func(func) {}
    ~SymbolValue() {}
};

class LogosSymbol {
public:
    const std::string name;
    const SymbolKind kind;
    SymbolValue value;

    explicit LogosSymbol(const std::string& name, const SymbolKind kind, const SymbolValue& value) :
        name(name),
        kind(kind),
        value(value) {
    }

    explicit LogosSymbol(const std::string& name, const SymbolKind kind) : name(name), kind(kind) {}
};


#endif //SYMBOL_H
