#pragma once
#include "exprs/LgsExpr.h"


class LgsTypeExpr final : public LgsExpr {
public:
    explicit LgsTypeExpr(LgsType* type): LgsExpr(type) {}
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
};
