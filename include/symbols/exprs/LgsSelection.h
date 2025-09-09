#pragma once
#include "exprs/LgsExpr.h"

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* lastExpr() const;
    LgsExpr* lastExprParent() const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    std::string pname() override;
    LgsExpr* castTo(LgsType* toType) override;
    Value* hash(LgsLLVMGen& cg) override;
    json::value asJSON() override;
    ~LgsSelection() override;
};
