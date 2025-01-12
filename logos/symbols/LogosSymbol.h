#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

class LogosExpr;

enum SymbolKind {
    CONSTANT,
    LOCAL_VARIABLE,
    FUNC_CALL,
    FUNC_DEFINITION,
    PARAM,
};

class LogosSymbol {
public:
    const std::string name;
    const SymbolKind kind;
    union SymbolValue {
        LogosExpr *expr;
        SymbolValue() {}
        ~SymbolValue() {}
    } value;

    explicit LogosSymbol(const std::string& name, const SymbolKind kind, const SymbolValue& value) :
        name(name),
        kind(kind),
        value(value) {
    }
    explicit LogosSymbol(const std::string& name, const SymbolKind kind) : name(name), kind(kind) {}
};


#endif //SYMBOL_H
