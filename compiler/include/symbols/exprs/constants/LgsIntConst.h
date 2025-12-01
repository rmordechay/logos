#pragma once
#include "exprs/LgsExpr.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include <iostream>

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const int64_t value) : LgsExpr(type), value(value) {
        isMutable = false;
    }
    explicit LgsIntConst(const int64_t value) : LgsExpr(&LGS_INT), value(value) {
        isMutable = false;
    }
    Value* loadIR(LgsCgModule& cg) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void hashNode(size_t& oldHash) override;
    Value* hashValue(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
};
