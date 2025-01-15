#ifndef COMPARISON_H
#define COMPARISON_H
#include "CodeNode.h"
#include "exprs/LogosExpr.h"


class IfStmt final : public CodeNode {
public:
    LogosExpr* expr;
    vector<CodeNode*> codeNodes;

    explicit IfStmt(LogosExpr* expr) : expr(expr) {}
    void generateCode(RuntimeStackFrame* stackFrame) override;
    ~IfStmt() override = default;
};



#endif //COMPARISON_H
