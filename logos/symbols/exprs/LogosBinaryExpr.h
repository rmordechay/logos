#ifndef LOGOSBINARYOP_H
#define LOGOSBINARYOP_H
#include "LogosExpr.h"
#include "LogosOperator.h"
#include "LogosUnaryExpr.h"

class LogosBinaryExpr final : public LogosExpr {
public:
    const LogosExpr* left;
    const LogosExpr* right;
    const LogosOperator op;

    explicit LogosBinaryExpr(const LogosExpr* left, const LogosExpr* right, const LogosOperator op) :
        left(left),
        right(right),
        op(op) {
    }
};

#endif //LOGOSBINARYOP_H
