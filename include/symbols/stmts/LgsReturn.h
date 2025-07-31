#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;
    BasicBlock* parentBlock = nullptr;
    GetElementPtrInst* returnStructPtr = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRStmt(LgsCodeGen* codeGen) override;
    void setReturnFlag(LgsCodeGen* codeGen, bool value) const;
    void setReturnValue(LgsCodeGen* codeGen, Value* value) const;
    ~LgsReturn() override;
};




