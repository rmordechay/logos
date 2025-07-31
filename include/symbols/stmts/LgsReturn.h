#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;
    BasicBlock* parentBlock = nullptr;
    AllocaInst* returnStruct = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsCodeGen* codeGen) override;
    Value* getReturnFlag(LgsCodeGen* codeGen) const;
    void setReturnFlag(LgsCodeGen* codeGen, bool returnFlag) const;
    ~LgsReturn() override;
};




