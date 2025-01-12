#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"
#include "LogosType.h"

class LogosUnaryExpr : public LogosExpr {
public:
    explicit LogosUnaryExpr(const LogosType* exprType) : LogosExpr(exprType) {}
};

#endif //LOGOSUNARYEXPR_H
