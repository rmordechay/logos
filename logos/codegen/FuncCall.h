#ifndef FUNCCALL_H
#define FUNCCALL_H
#include "CodeNode.h"
#include "exprs/LogosFuncCallExpr.h"


class FuncCall final : public CodeNode {
public:
    LogosFuncCallExpr* funcCallExpr;

    explicit FuncCall(LogosFuncCallExpr* funcCallExpr) : funcCallExpr(funcCallExpr) {}
    void generateProlog(RuntimeScope* scope) override;
    void generateEpilog(RuntimeScope* scope) override;
    ~FuncCall() override = default;
};



#endif //FUNCCALL_H
