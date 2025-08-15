#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"
#include <llvm/IRReader/IRReader.h>

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;
    BasicBlock* parentBlock = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    ~LgsReturn() override;
};




