#ifndef SELECTION_H
#define SELECTION_H
#include "LogosExpr.h"
#include "exprs/LogosInstance.h"
#include "object/LogosObject.h"

class LogosUnaryExpr;

class LogosSelection final : public LogosUnaryExpr {
public:
    const vector<LogosUnaryExpr*> exprs;

    explicit LogosSelection(const vector<LogosUnaryExpr*>& exprs) : exprs(exprs) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    static Value* resolveSelection(CodeGenMetadata* metadata, LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr);
    void setName(string name) override;
    string getName() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
