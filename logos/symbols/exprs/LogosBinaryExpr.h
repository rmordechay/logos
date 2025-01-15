#ifndef LOGOSBINARYEXPR_H
#define LOGOSBINARYEXPR_H
#include "LogosExpr.h"
#include "LogosOperator.h"
#include "LogosSymbol.h"

class LogosBinaryExpr final : public LogosExpr {
public:
    LogosExpr *left;
    LogosExpr *right;
    LogosOperator op;

    LogosBinaryExpr(const LogosType& type, LogosExpr* left, LogosExpr* right, const LogosOperator op) :
        LogosExpr(type),
        left(left),
        right(right),
        op(op) {
    }

    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) override;
    ~LogosBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
