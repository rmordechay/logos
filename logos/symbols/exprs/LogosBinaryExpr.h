#ifndef LOGOSBINARYOP_H
#define LOGOSBINARYOP_H
#include "LogosExpr.h"
#include "LogosOperator.h"
#include "LogosUnaryExpr.h"

class LogosBinaryExpr final : public LogosExpr {
public:
    std::shared_ptr<LogosExpr> left;
    std::shared_ptr<LogosExpr> right;
    LogosOperator op;

    explicit LogosBinaryExpr(const std::shared_ptr<LogosExpr>& left, const std::shared_ptr<LogosExpr>& right, const LogosOperator op) :
        left(left), right(right), op(op) {}
};

#endif //LOGOSBINARYOP_H
