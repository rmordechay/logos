#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LogosExpr.h"
#include "LogosOperator.h"

#include <LogosMetadata.h>
#include <types/LogosType.h>

class LogosBinaryExpr final : public LogosExpr {
public:
    LogosExpr* left;
    LogosExpr* right;
    LogosOperator op;

    explicit LogosBinaryExpr(LogosType* type, LogosExpr* left, LogosExpr* right, const LogosOperator op) :
        LogosExpr(type),
        left(left),
        right(right),
        op(op) {
    }

    Value* computeIRValue(CodeGenMetadata* metadata) override;
    ~LogosBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
