#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LogosExpr.h"
#include "LogosOperator.h"

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

    Value* computeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosBinaryExpr() override = default;
    LogosSymbolType getSymbolType() override { return BINARY_EXPR; }
};

#endif //LOGOSBINARYEXPR_H
