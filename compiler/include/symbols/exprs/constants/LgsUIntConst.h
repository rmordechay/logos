#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsUIntConst final : public LgsExpr {
public:
    int64_t value;

    explicit LgsUIntConst(const int value) : LgsExpr(&LGS_UINT), value(value) {}
    std::string asText() override;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    ~LgsUIntConst() override = default;
};


