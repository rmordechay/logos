#ifndef LGSPATTERNMATCHING_H
#define LGSPATTERNMATCHING_H
#include "LgsStmt.h"
#include "LgsStmtBlock.h"

#include <exprs/unary/LgsUnaryExpr.h>

class LgsPatternMatching final : public LgsStmt {
public:
    LgsExpr* expr;
    vector<LgsExpr*> patterns;
    vector<LgsStmtBlock*> patternsStmtBlocks;
    LgsStmtBlock* elseStmtBlock = nullptr;
    BasicBlock* exitBlock = nullptr;
    BasicBlock* defaultCase = nullptr;

    explicit LgsPatternMatching(LgsExpr* expr) : expr(expr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsPatternMatching() override = default;
};

#endif //LGSPATTERNMATCHING_H
