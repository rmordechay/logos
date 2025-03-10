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
    Value* resolveFirstSelection(CodeGenMetadata* metadata, const LogosVariable* variable);
    Value* resolveFirstSelection(CodeGenMetadata* metadata, const LogosFuncCall* funcCall);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosInstance* instance);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosMethodCall* methodCall);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosField* field);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosFuncImpl* funcImpl);
    LogosExpr* lastExpr() const;
    string getName() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
