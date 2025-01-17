#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "StackFrame.h"
#include "funcs/LogosFunc.h"
#include "exprs/LogosExpr.h"
#include "exprs/LogosUnaryExpr.h"
#include <map>

class LogosFuncCallExpr final : public LogosUnaryExpr {
public:
    const LogosFunc& func;
    std::vector<LogosExpr*> args;

    LogosFuncCallExpr(const LogosFunc& func, const std::vector<LogosExpr*>& args) :
        LogosUnaryExpr(func.type),
        func(func),
        args(args) {
    }

    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    ~LogosFuncCallExpr() override = default;
};

#endif //LOGOSFUNCCALLEXPR_H
