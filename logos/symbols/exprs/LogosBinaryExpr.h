#ifndef LOGOSBINARYOP_H
#define LOGOSBINARYOP_H
#include "LogosExpr.h"
#include "LogosOperator.h"
#include "LogosSymbol.h"

class LogosBinaryExpr : public LogosExpr {
public:
    LogosTypedValue& left;
    LogosTypedValue& right;
    LogosOperator op;

    explicit LogosBinaryExpr(LogosTypedValue& left, LogosTypedValue& right, const LogosOperator op) :
        left(left), right(right), op(op) {}
};

#endif //LOGOSBINARYOP_H
