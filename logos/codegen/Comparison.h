#ifndef COMPARISON_H
#define COMPARISON_H
#include "CodeNode.h"
#include "exprs/LogosExpr.h"


class Comparison final : public CodeNode {
public:
    LogosExpr* expr;
    BasicBlock* ifThenBlock = nullptr;
    BasicBlock* ifEndBlock = nullptr;

    explicit Comparison(LogosExpr* expr) : expr(expr) {}
    void generateProlog(RuntimeScope* scope) override;
    void generateEpilog(RuntimeScope* scope) override;
    ~Comparison() override = default;
};



#endif //COMPARISON_H
