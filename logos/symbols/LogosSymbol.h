#ifndef SYMBOL_H
#define SYMBOL_H

#include "exprs/LogosExpr.h"
#include "funcs/LogosFunc.h"

#include <string>

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
    SymbolValue value;

    explicit LogosSymbol(const std::string& name, const SymbolValue& value) :
        name(name),
        value(value) {
    }

};


#endif //SYMBOL_H
