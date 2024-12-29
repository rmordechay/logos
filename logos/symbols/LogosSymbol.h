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
    const std::shared_ptr<LogosExpr> expr;
    const SymbolKind kind;

    explicit LogosSymbol(const std::string& name, const std::shared_ptr<LogosExpr>& expr, const SymbolKind kind) :
        name(name),
        expr(expr),
        kind(kind) {
    }
};


#endif //SYMBOL_H
