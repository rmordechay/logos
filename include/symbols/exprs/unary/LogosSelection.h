#ifndef SELECTION_H
#define SELECTION_H
#include "types/LogosObject.h"

class LogosUnaryExpr;
class LogosMethodCall;

class LogosSelection final : public LogosUnaryExpr {
public:
    vector<LogosUnaryExpr*> exprs;

    explicit LogosSelection(const vector<LogosUnaryExpr*>& exprs) : exprs(exprs) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* resolveType(CodeGenMetadata* metadata, LogosUnaryExpr* nextExpr, LogosType* logosType) const;
    Value* resolveSelectionVariable(CodeGenMetadata* metadata, const LogosVariable* variable, LogosUnaryExpr* nextExpr) const;
    LogosExpr* lastExpr() const;
    string getName() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
