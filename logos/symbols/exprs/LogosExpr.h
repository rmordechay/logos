#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LogosValue.h"

class LogosExpr {
public:
    LogosValue* exprType;
    explicit LogosExpr(LogosValue* exprType) : exprType(exprType) {}
    explicit LogosExpr() : exprType(nullptr) {}
    virtual ~LogosExpr() = default;
};

#endif //LOGOSEXPR_H
