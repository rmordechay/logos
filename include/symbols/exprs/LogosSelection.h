#ifndef SELECTION_H
#define SELECTION_H
#include "object/LogosObject.h"

class LogosUnaryExpr;

class LogosSelection final : public LogosUnaryExpr {
public:
    const vector<LogosUnaryExpr*> exprs;

    explicit LogosSelection(const vector<LogosUnaryExpr*>& exprs) : exprs(exprs) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* resolveSelection(CodeGenMetadata* metadata, const LogosVariable* variable, LogosUnaryExpr* nextExpr) const;
    Value* resolveSelection(CodeGenMetadata* metadata, LogosFuncCall* funcCall, LogosUnaryExpr* nextExpr) const;
    LogosExpr* lastExpr() const;
    string getName() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
