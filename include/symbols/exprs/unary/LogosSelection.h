#ifndef SELECTION_H
#define SELECTION_H
#include "types/LogosObject.h"

class LogosUnaryExpr;
class LogosMethodCall;

class LogosSelection final : public LogosUnaryExpr {
public:
    LogosUnaryExpr* firstExpr;
    const vector<LogosUnaryExpr*> innerExprs;
    vector<LogosUnaryExpr*> exprs;

    LogosSelection(LogosUnaryExpr* firstExpr, const vector<LogosUnaryExpr*>& innerExprs) : firstExpr(firstExpr), innerExprs(innerExprs) {
        exprs.emplace_back(firstExpr);
        exprs.insert(exprs.end(), innerExprs.begin(), innerExprs.end());
        std::cout << "" << '\n';
    }

    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* resolveFirstSelection(CodeGenMetadata* metadata, const LogosVariable* variable);
    Value* resolveFirstSelection(CodeGenMetadata* metadata, const LogosFuncCall* funcCall);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosInstance* instance);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosMethodCall* methodCall);
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosField* field) const;
    Value* resolveInnerSelection(CodeGenMetadata* metadata, int i, LogosFuncImpl* funcImpl);
    LogosExpr* lastExpr() const;
    string getName() override;
    ~LogosSelection() override;
};

#endif //SELECTION_H
