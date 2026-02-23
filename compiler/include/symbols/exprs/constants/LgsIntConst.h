#pragma once
#include <string>

#include "exprs/LgsExpr.h"
#include "types/primitives/LgsInt.h"

class LgsType;

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const int64_t value) : LgsExpr(type), value(value) {
        isMutable = false;
    }
    LgsExpr* cast(LgsType* toType, bool explicitly) override;
    LgsIntConst* clone() override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCodeGen& cg) override;
};
