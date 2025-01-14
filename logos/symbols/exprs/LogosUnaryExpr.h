#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "types/LogosType.h"
#include "exprs/LogosExpr.h"

class LogosUnaryExpr: public LogosExpr {
public:
    explicit LogosUnaryExpr(const LogosType& type) : LogosExpr(type) {}
    ~LogosUnaryExpr() override = default;
};

#endif //LOGOSUNARYEXPR_H
