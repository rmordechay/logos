#pragma once
#include <stdint.h>
#include <string>

#include "exprs/LgsExpr.h"
#include "types/primitives/LgsUInt.h"

class LgsType;

class LgsUIntConst final : public LgsExpr {
public:
    uint64_t value;

    LgsUIntConst(LgsType* type, const uint64_t value) : LgsExpr(type), value(value) {}
    explicit LgsUIntConst(const uint64_t value) : LgsExpr(&LGS_UINT), value(value) {}
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsUIntConst() override = default;
};


