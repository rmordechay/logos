#ifndef SELECTION_H
#define SELECTION_H
#include "LogosExpr.h"
#include "exprs/LogosConstructor.h"
#include "object/LogosObject.h"

class LogosUnaryExpr;

class LogosSelection final : public LogosExpr {
public:
    const vector<LogosUnaryExpr*> exprs;

    explicit LogosSelection(const vector<LogosUnaryExpr*>& exprs) : LogosExpr(nullptr), exprs(exprs) {}
    Value* computeLLVMValue(CodeGenMetadata* metadata) override;
    static Value* resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr);
    LogosSymbolType getSymbolType() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
