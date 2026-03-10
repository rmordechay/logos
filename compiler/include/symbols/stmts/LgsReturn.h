#pragma once
#include "LgsStmt.h"
#include "LgsValue.h"

class LgsExpr;
namespace llvm {
class BasicBlock;
}

class LgsReturn final : public LgsStmt {
public:
    LgsExpr* expr = nullptr;
    BasicBlock* parentBlock = nullptr;
    LgsFunc* func = nullptr;
    std::vector<LgsIOStmt*> ioStmts;

    explicit LgsReturn(LgsExpr* expr) : expr(expr) {}
    void setDebugValue(LgsCodeGen& cg) override;
    LgsStmt* clone() const override;
    ~LgsReturn() override;
};




