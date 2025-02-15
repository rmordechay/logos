#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"
#include "types/LogosType.h"

class LogosFuncCall;
class LogosVariable;
class LogosConstant;
class LogosConstructor;

class LogosExpr: virtual public CodeGeneration {
public:
    mutable LogosType* type = nullptr;

    explicit LogosExpr(LogosType* type) : type(type) {}
    virtual LogosSymbolType getSymbolType() = 0;
    virtual LogosSymbol getSymbol();
    virtual LogosFuncCall* asFuncCall() { return nullptr; }
    virtual LogosVariable* asVariable() { return nullptr; }
    virtual LogosConstant* asConstant() { return nullptr; }
    virtual LogosConstructor* asConstructor() { return nullptr; }
    ~LogosExpr() override = default;
};

inline LogosSymbol LogosExpr::getSymbol() {
    const auto type = getSymbolType();
    switch (type) {
    case CONSTRUCTOR:
        return LogosSymbol(type, asConstructor());
    case FUNC_CALL:
        return LogosSymbol(type, asFuncCall());
    case VARIABLE:
        return LogosSymbol(type, asVariable());
    case CONSTANT:
        return LogosSymbol(type, asConstructor());
    default:
        return LogosSymbol();
    }
}

#endif //LOGOSEXPR_H

