#ifndef SELECTION_H
#define SELECTION_H
#include "object/LogosObject.h"

class LogosUnaryExpr;
class LogosMethodCall;

class LogosSelection final : public LogosUnaryExpr {
public:
    LogosUnaryExpr* firstExpr;
    const vector<LogosUnaryExpr*> innerExprs;

    LogosSelection(LogosUnaryExpr* firstExpr, const vector<LogosUnaryExpr*>& innerExprs) : firstExpr(firstExpr), innerExprs(innerExprs) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int nextIndex, LogosInstance* instance);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int nextIndex, LogosMethodCall* methodCall);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int nextIndex, LogosField* field);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int nextIndex, LogosFuncImpl* funcImpl);
    Value* resolveFirstSelection(CodeGenMetadata* metadata, const LogosVariable* variable);
    Value* resolveFirstSelection(CodeGenMetadata* metadata, const LogosFuncCall* funcCall);
    LogosExpr* lastExpr() const;
    string getName() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
