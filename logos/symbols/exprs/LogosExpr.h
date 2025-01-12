#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LogosType.h"

class LogosExpr {
public:
    const LogosType* exprType;
    explicit LogosExpr(const LogosType* exprType) : exprType(exprType) {}
    explicit LogosExpr() : exprType(nullptr) {}
    virtual ~LogosExpr() = default;
};

#endif //LOGOSEXPR_H
