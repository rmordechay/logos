#pragma once
#include <string>
#include <vector>

#include "exprs/LgsExpr.h"

class LgsFuncCall;

class LgsSelection final : public LgsExpr {
public:
    std::vector<LgsExpr*> exprs;

    explicit LgsSelection(const std::vector<LgsExpr*>& exprs) : exprs(exprs) {}
    LgsFuncCall* asMethodCall() const;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() const override;
    ~LgsSelection() override;
};
