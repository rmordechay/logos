#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsUIntConst final : public LgsExpr {
public:
    uint64_t value;

    LgsUIntConst(LgsType* type, const uint64_t value) : LgsExpr(type), value(value) {
        isMutable = false;
    }
    explicit LgsUIntConst(const uint64_t value) : LgsExpr(&LGS_UINT), value(value) {
        isMutable = false;
    }
    std::string asText() override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsUIntConst() override = default;
};


