#pragma once
#include "exprs/LgsExpr.h"

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    LgsFuncCall* asMethodCall() const;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsSelection() override;
};
