#ifndef SELECTION_H
#define SELECTION_H
#include "LogosExpr.h"
#include "LogosUnaryExpr.h"

class LogosSelection final : public LogosExpr {
public:
    const vector<LogosUnaryExpr*> exprs;

    explicit LogosSelection(const vector<LogosUnaryExpr*>& exprs) : LogosExpr(nullptr), exprs(exprs) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosSelection() override;
};


#endif //SELECTION_H
