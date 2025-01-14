#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LogosOperator.h"
#include "LogosSymbol.h"

class LogosBinaryExpr : public LogosExpr {
public:
    LogosExpr *left;
    LogosExpr *right;
    LogosOperator op;

    LogosBinaryExpr(const LogosType& type, LogosExpr* left, LogosExpr* right, LogosOperator op) :
        LogosExpr(type),
        left(left),
        right(right),
        op(op) {
    }

    ~LogosBinaryExpr() = default;
};

#endif //LOGOSBINARYEXPR_H
