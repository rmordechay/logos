#pragma once
#include "exprs/LgsExpr.h"

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* lastExpr() const;
    LgsFuncCall* asMethodCall() const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    std::string pname() override;
    Value* hash(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    json::value asJSON() override;
    ~LgsSelection() override;
};
