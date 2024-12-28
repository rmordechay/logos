#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

class LogosUnaryExpr : public LogosExpr {
public:
    LogosTypedValue &value;
    LogosOperator op;

    explicit LogosUnaryExpr(LogosTypedValue& value, LogosTypedValue* results) : LogosExpr(results), value(value), op(NOOP) {}
    explicit LogosUnaryExpr(LogosTypedValue& value, const LogosOperator op) : value(value), op(op) {}
    explicit LogosUnaryExpr(LogosTypedValue& value) : value(value), op(NOOP) {}
};

#endif //LOGOSUNARYEXPR_H
