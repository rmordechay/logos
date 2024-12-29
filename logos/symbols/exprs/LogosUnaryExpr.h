#ifndef LOGOSUNARYEXPR_H
#define LOGOSUNARYEXPR_H
#include "LogosExpr.h"

class LogosUnaryExpr : public LogosExpr {
public:
    LogosOperator op;

    explicit LogosUnaryExpr(const std::shared_ptr<LogosTypedValue> &value, const LogosOperator op) : LogosExpr(value), op(op) {}
    explicit LogosUnaryExpr(const std::shared_ptr<LogosTypedValue> &value) : LogosUnaryExpr(value, NOOP) {}
    ~LogosUnaryExpr() = default;
};

#endif //LOGOSUNARYEXPR_H
