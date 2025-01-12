#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

class LogosUnaryExpr : public LogosExpr {
public:
    explicit LogosUnaryExpr(LogosValue* exprType) : LogosExpr(exprType) {}
};

#endif //LOGOSUNARYEXPR_H
