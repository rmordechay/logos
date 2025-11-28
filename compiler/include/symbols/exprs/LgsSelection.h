#pragma once
#include "exprs/LgsExpr.h"

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;
    LgsVariable* importVar = nullptr;
    bool hasNullables = false;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    Value* loadIR(LgsCgModule& cg) override;
    LgsExpr* lastExpr() const;
    LgsFuncCall* asMethodCall() const;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    void assign(LgsCgModule& cg, LgsExpr* expr) override;
    std::string asText() override;
    Value* hashValue(LgsCgModule& cg) override;
    bool equals(LgsExpr* other) override;
    ~LgsSelection() override;
};
