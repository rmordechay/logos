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
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    LogosSymbolType getSymbolType() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
