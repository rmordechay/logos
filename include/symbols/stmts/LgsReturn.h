#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

namespace llvm {
    class BasicBlock;
}

class LgsReturn final : public LgsStmt {
public:
    LgsExpr *expr = nullptr;
    llvm::BasicBlock* parentBlock = nullptr;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    ~LgsReturn() override;
};




