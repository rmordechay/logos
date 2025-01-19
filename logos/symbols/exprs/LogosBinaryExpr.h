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


    explicit LogosBinaryExpr(const LogosType* type, LogosExpr* left, LogosExpr* right, const LogosOperator op)
        : LogosExpr(type), left(left), right(right), op(op) {}

    Value* getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) override;
    ~LogosBinaryExpr() override = default;
};

#endif //LOGOSBINARYEXPR_H
