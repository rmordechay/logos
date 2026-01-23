#pragma once
#include "exprs/LgsExpr.h"

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;
    LgsVariable* importVar = nullptr;
    bool hasNullables = false;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    Value* loadIR(LgsCgModule& cg) override;
    LgsFuncCall* asMethodCall() const;
    void assign(LgsCgModule& cg, LgsExpr* right) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsSelection() override;
};
