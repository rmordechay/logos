#pragma once
#include "exprs/LgsExpr.h"

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;
    bool hasNullables = false;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* lastExpr() const;
    LgsFuncCall* asMethodCall() const;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    std::string getName() override;
    Value* hash(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    void parseAsJSON(std::stringstream& json) override;
    ~LgsSelection() override;
};
