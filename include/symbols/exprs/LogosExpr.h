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
    virtual LogosFuncCall* asFuncCall() { return nullptr; }
    virtual LogosVariable* asVariable() { return nullptr; }
    virtual LogosConstant* asConstant() { return nullptr; }
    virtual LogosConstructor* asConstructor() { return nullptr; }
    ~LogosExpr() override = default;
};


#endif //LOGOSEXPR_H

