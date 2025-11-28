#pragma once
#include "exprs/LgsExpr.h"


class LgsTypeExpr final : public LgsExpr {
public:
    explicit LgsTypeExpr(LgsType* type): LgsExpr(type) {}
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    std::string asText() override;
};
